#ifndef PHP_ATREE_H
#define PHP_ATREE_H 1

#ifdef ZTS
#include "TSRM.h"
#endif

#define PHP_ATREE_VERSION "1.0-dev"
#define PHP_ATREE_EXTNAME "atree"

extern zend_module_entry atree_module_entry;
#define phpext_atree_ptr &atree_module_entry

#endif
