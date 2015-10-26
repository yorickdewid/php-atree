#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_atree.h"
#include "zend_exceptions.h"

#include "atree.h"

/* Structure for Adaptive Tree object. */
typedef struct _php_atree_db_object  {
	zend_object zo;
	int initialised;
	art_tree *t;

	zend_bool exception;
} php_atree_db_object;

/* Handlers */
static zend_object_handlers atree_object_handlers;

/* Class entries */
zend_class_entry *php_atree_sc_entry;

/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO(arginfo_atree_put, 0)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, buf)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_atree_opr, 0)
        ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_atree_void, 0)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ Error Handler
*/
static void php_atree_error(php_atree_db_object *obj, char *format, ...)
{
	va_list arg;
	char *message;
	TSRMLS_FETCH();

	va_start(arg, format); 
	vspprintf(&message, 0, format, arg);
	va_end(arg);

	if (obj && obj->exception) {
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), message, 0 TSRMLS_CC);
	} else {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "%s", message);
	}

	if (message) {
		efree(message);
	}
}
/* }}} */

/* {{{ proto void Atree::init()
   Initializes a new ART tree. */
PHP_METHOD(atree, init)
{
	zval *object = getThis();

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_NULL();
	}

	art_tree *t = (art_tree *)emalloc(sizeof(art_tree));

	if (art_tree_init(t) != 0) {
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), "Unable to open tree", 0 TSRMLS_CC);
		RETURN_NULL();
	}

	php_atree_db_object *obj = (php_atree_db_object *)zend_object_store_get_object(object TSRMLS_CC);

        if (obj->initialised) {
                zend_throw_exception(zend_exception_get_default(TSRMLS_C), "Already initialised Atree Object", 0 TSRMLS_CC);
                RETURN_NULL();
        }

	obj->t = t;
	obj->initialised = 1;
}
/* }}} */

PHP_METHOD(atree, put)
{
	char *key, *buf;
	int key_len, buf_len;

	php_atree_db_object *obj = (php_atree_db_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	if (!obj) {
		php_atree_error(obj, "The object has not been correctly initialised");
		RETURN_FALSE;
	}

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &key, &key_len, &buf, &buf_len)) {
		RETURN_NULL();
	}

	if (art_insert(obj->t, (unsigned char *)key, key_len, (void *)buf) != NULL) {
		php_atree_error(obj, "Unable to insert key");
		RETURN_FALSE;
	}

	RETURN_TRUE;
}

PHP_METHOD(atree, get)
{
	char *key;
	int key_len;

	php_atree_db_object *obj = (php_atree_db_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

        if (!obj) {
                php_atree_error(obj, "The object has not been correctly initialised");
                RETURN_FALSE;
        }

        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &key, &key_len)) {
                RETURN_NULL();
        }

	void *val = art_search(obj->t, (unsigned char *)key, key_len);
	if (val == NULL) {
		php_atree_error(obj, "No value found for key: %s", key);
		RETURN_NULL();
	}

	RETVAL_STRING(val, 1);
}

PHP_METHOD(atree, delete)
{
        char *key;
        int key_len;

        php_atree_db_object *obj = (php_atree_db_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

        if (!obj) {
                php_atree_error(obj, "The object has not been correctly initialised");
                RETURN_FALSE;
        }

        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &key, &key_len)) {
                RETURN_NULL();
        }

        void *val = art_delete(obj->t, (unsigned char *)key, key_len);
        if (val == NULL) {
                php_atree_error(obj, "No value found for key: %s", key);
		RETURN_NULL();
        }

	RETVAL_STRING(val, 1);
}

int all_cb_array(void *data, const unsigned char* key, uint32_t key_len, void *val) {
	zval *arr = data;

	add_assoc_stringl_ex(arr, (char *)key, key_len+1, (char *)val, strlen(val), 1);
	return 0;
}

PHP_METHOD(atree, all)
{
        php_atree_db_object *obj = (php_atree_db_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

        if (!obj) {
                php_atree_error(obj, "The object has not been correctly initialised");
                RETURN_FALSE;
        }

        if (zend_parse_parameters_none() == FAILURE) {
                RETURN_NULL();
        }

	array_init(return_value);

	if (art_iter(obj->t, all_cb_array, return_value) != 0) {
		php_atree_error(obj, "Cannot iterate tree");
		RETURN_FALSE;
	}
}

PHP_METHOD(atree, prefix)
{
        char *key;
        int key_len;

        php_atree_db_object *obj = (php_atree_db_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

        if (!obj) {
                php_atree_error(obj, "The object has not been correctly initialised");
                RETURN_FALSE;
        }


        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &key, &key_len)) {
                RETURN_NULL();
        }

        array_init(return_value);

	if (art_iter_prefix(obj->t, (unsigned char *)key, key_len, all_cb_array, return_value) != 0) {
                php_atree_error(obj, "Cannot iterate tree");
                RETURN_FALSE;
        }
}

PHP_METHOD(atree, size)
{
        php_atree_db_object *obj = (php_atree_db_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

        if (!obj) {
                php_atree_error(obj, "The object has not been correctly initialised");
                RETURN_FALSE;
        }

        if (zend_parse_parameters_none() == FAILURE) {
                RETURN_NULL();
        }

	RETURN_LONG(obj->t->size);
}

/* {{{ proto String Atree::version()
   Returns theversion as a string constant. */
PHP_METHOD(atree, version)
{
        if (zend_parse_parameters_none() == FAILURE) {
                return;
        }

	RETVAL_STRING(PHP_ATREE_VERSION, 1);
}
/* }}} */

/* {{{ php_atree_class_methods */
static zend_function_entry php_atree_class_methods[] = {
	PHP_ME(atree, init, arginfo_atree_void, ZEND_ACC_PUBLIC)
	PHP_ME(atree, put, arginfo_atree_put, ZEND_ACC_PUBLIC)
	PHP_ME(atree, get, arginfo_atree_opr, ZEND_ACC_PUBLIC)
	PHP_ME(atree, delete, arginfo_atree_opr, ZEND_ACC_PUBLIC)
	PHP_ME(atree, all, arginfo_atree_void, ZEND_ACC_PUBLIC)
	PHP_ME(atree, prefix, arginfo_atree_opr, ZEND_ACC_PUBLIC)
	PHP_ME(atree, size, arginfo_atree_void, ZEND_ACC_PUBLIC)
	PHP_ME(atree, version, arginfo_atree_void, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	/* Aliases */
	PHP_MALIAS(atree, __construct, init, arginfo_atree_void, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_FE_END
};
/* }}} */

void atree_free_storage(void *object TSRMLS_DC)
{
	php_atree_db_object *obj = (php_atree_db_object *)object;

	if (!obj) {
		return;
	}

	art_tree_destroy(obj->t);

	efree(obj->t);

	zend_object_std_dtor(&obj->zo TSRMLS_CC);
	efree(obj);
}

static zend_object_value atree_create_handler(zend_class_entry *type TSRMLS_DC)
{
	zval *tmp;
	zend_object_value retval;

	php_atree_db_object *obj = (php_atree_db_object *)emalloc(sizeof(php_atree_db_object));
	memset(obj, 0, sizeof(php_atree_db_object));
	obj->exception = 1;
	obj->initialised = 0;
	obj->zo.ce = type;

	zend_object_std_init(&obj->zo, type TSRMLS_CC);
	object_properties_init(&obj->zo, type);

	retval.handle = zend_objects_store_put(obj, NULL, atree_free_storage, NULL TSRMLS_CC);
	retval.handlers = &atree_object_handlers;

	return retval;
}

/* {{{ PHP_MINIT_FUNCTION
*/
PHP_MINIT_FUNCTION(atree)
{
	zend_class_entry ce;

	memcpy(&atree_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	/* Register Atree 3 Class */
	INIT_CLASS_ENTRY(ce, "Atree", php_atree_class_methods);
	php_atree_sc_entry = zend_register_internal_class(&ce TSRMLS_CC);
	php_atree_sc_entry->create_object = atree_create_handler;

	memcpy(&atree_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	atree_object_handlers.clone_obj = NULL;

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
*/
PHP_MINFO_FUNCTION(atree)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "Adaptive Tree suppport", "enabled");
	php_info_print_table_row(2, "Atree module version", PHP_ATREE_VERSION);
	php_info_print_table_row(2, "Tree algorithm", "LibART");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ atree_module_entry
*/
zend_module_entry atree_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_ATREE_EXTNAME,
    NULL,
    PHP_MINIT(atree),
    NULL,
    NULL,
    NULL,
    PHP_MINFO(atree),
    PHP_ATREE_VERSION,
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_ATREE
ZEND_GET_MODULE(atree)
#endif
