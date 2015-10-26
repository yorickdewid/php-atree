--TEST--
Atree::delete tests
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$db = new Atree;
var_dump($db->put("k1", "v1"));
var_dump($db->put("k2", "v2"));
var_dump($db->put("k3", "v3"));
var_dump($db->put("k4", "v4"));
var_dump($db->get("k1"));
var_dump($db->delete("k3"));
echo $db->size() . "\n";
echo "Done\n";
?>
--EXPECTF--
bool(true)
bool(true)
bool(true)
bool(true)
string(2) "v1"
string(2) "v3"
3
Done
