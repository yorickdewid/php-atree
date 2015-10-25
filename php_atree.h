#ifndef PHP_ATREE_H
#define PHP_ATREE_H 1

#ifdef ZTS
#include "TSRM.h"
#endif

#define PHP_ATREE_VERSION "0.9"
#define PHP_ATREE_EXTNAME "php-atree"

PHP_FUNCTION(atree_init);

extern zend_module_entry atree_module_entry;
#define phpext_atree_ptr &atree_module_entry

#endif
