--TEST--
Atree::get tests
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$db = new Atree;
var_dump($db->put("k1", "k1"));
var_dump($db->put("k2", "v2"));
var_dump($db->put("k3", "v3"));
var_dump($db->put("k4", "v4"));
var_dump($db->put("k5", "v5"));
echo $db->get("k1")."\n";
echo $db->get("k1")."\n";
echo $db->get("k2")."\n";
echo $db->get("k2")."\n";
echo $db->get("k3")."\n";
echo $db->get("k2")."\n";
echo $db->get("k2")."\n";
echo $db->get("k1")."\n";
echo $db->get("k4")."\n";
echo "Done\n";
?>
--EXPECTF--
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
k1
k1
v2
v2
v3
v2
v2
k1
v4
Done
