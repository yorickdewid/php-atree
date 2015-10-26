--TEST--
Atree::version tests
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

echo Atree::version()."\n";
echo "Done\n";
?>
--EXPECTF--
%s
Done
