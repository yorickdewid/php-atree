--TEST--
Atree::put tests
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$db = new Atree;
var_dump($db->put("test", "test2"));
var_dump($db->put("k2", "v2"));
echo "Done\n";
?>
--EXPECTF--
bool(true)
bool(true)
Done
