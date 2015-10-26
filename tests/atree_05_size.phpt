--TEST--
Atree::clear tests
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$db = new Atree;
var_dump($db->put("k1", "v1"));
var_dump($db->put("k2", "v2"));
var_dump($db->put("k3", "v3"));
var_dump($db->put("k4", "v4"));
var_dump($db->put("k5", "v5"));
var_dump($db->put("k6", "v6"));
var_dump($db->put("k7", "v7"));
var_dump($db->put("k8", "v8"));
var_dump($db->put("k9", "v9"));
var_dump($db->clear());
var_dump($db->put("k_1", "v_1"));
echo $db->size() . "\n";
echo "Done\n";
?>
--EXPECTF--
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
1
Done
