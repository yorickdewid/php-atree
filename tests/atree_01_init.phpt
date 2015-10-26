--TEST--
Atree::init tests
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$db = new Atree;
var_dump($db);
echo "Done\n";
?>
--EXPECTF--
object(Atree)#%d (0) {
}
Done
