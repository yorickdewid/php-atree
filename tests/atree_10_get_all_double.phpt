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
print_r($db->all());
print_r($db->all());
print_r($db->all());
echo "Done\n";
?>
--EXPECTF--
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
Array
(
    [k1] => k1
    [k2] => v2
    [k3] => v3
    [k4] => v4
    [k5] => v5
)
Array
(
    [k1] => k1
    [k2] => v2
    [k3] => v3
    [k4] => v4
    [k5] => v5
)
Array
(
    [k1] => k1
    [k2] => v2
    [k3] => v3
    [k4] => v4
    [k5] => v5
)
Done
