#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_atree.h"
#include "SAPI.h"

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
ZEND_BEGIN_ARG_INFO(arginfo_atree_void, 0)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ proto String Atree::version()
   Returns theversion as a string constant. */
PHP_METHOD(atree, version)
{
        if (zend_parse_parameters_none() == FAILURE) {
                return;
        }

        ZVAL_STRING(return_value, PHP_ATREE_VERSION, 1);

        return;
}
/* }}} */

/* {{{ php_atree_class_methods */
static zend_function_entry php_atree_class_methods[] = {
	PHP_ME(atree, version, arginfo_atree_void, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
/* }}} */

static zend_object_value php_atree_object_new(zend_class_entry *class_type TSRMLS_DC) /* {{{ */
{
	zend_object_value retval;
	php_atree_db_object *intern;

	/* Allocate memory for it */
	intern = emalloc(sizeof(php_atree_db_object));
	memset(intern, 0, sizeof(php_atree_db_object));
	intern->exception = 0;

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	object_properties_init(&intern->zo, class_type);

	retval.handlers = (zend_object_handlers *) &atree_object_handlers;

	return retval;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
*/
PHP_MINIT_FUNCTION(atree)
{
	zend_class_entry ce;

	memcpy(&atree_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	/* Register Atree 3 Class */
	INIT_CLASS_ENTRY(ce, "Atree", php_atree_class_methods);
	ce.create_object = php_atree_object_new;
	atree_object_handlers.clone_obj = NULL;
	php_atree_sc_entry = zend_register_internal_class(&ce TSRMLS_CC);

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
