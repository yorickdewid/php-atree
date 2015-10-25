#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_atree.h"

const zend_function_entry atree_functions[] = {
    PHP_FE(atree_init, NULL)
    PHP_FE_END
};

zend_module_entry atree_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_ATREE_EXTNAME,
    atree_functions,
    //PHP_MINIT(hello),
    NULL,
    //PHP_MSHUTDOWN(hello),
    //PHP_RINIT(hello),
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_ATREE_VERSION,
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_ATREE
ZEND_GET_MODULE(atree)
#endif

PHP_FUNCTION(atree_init)
{
    RETURN_STRING("Gutte", 1);
}
