--TEST--
Atree::get tests
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$db = new Atree;
var_dump($db->put("k1", "v1"));
var_dump($db->get("k1"));
echo "Done\n";
?>
--EXPECTF--
bool(true)
string(2) "v1"
Done
