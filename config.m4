dnl
dnl $Id$ 
dnl

PHP_ARG_ENABLE(atree, whether to enable Adaptive Tree support,
[  --enable-atree   Enable Adaptive Tree support])
if test "$PHP_ATREE" = "yes"; then
  CFLAGS="$CFLAGS -std=c99"
  AC_DEFINE(HAVE_ATREE, 1, [Whether you have Adaptive Tree])
  PHP_NEW_EXTENSION(atree, php_tree.c atree.c, $ext_shared)
fi
