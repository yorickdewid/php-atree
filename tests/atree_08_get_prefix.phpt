--TEST--
Atree::prefix tests
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
var_dump($db->put("user.key.color", "blue"));
var_dump($db->put("user.key.size", 17));
var_dump($db->put("user.key.salary", "$ 34,45"));
var_dump($db->put("user.name", "john doe"));
print_r($db->prefix("user.key"));
print_r($db->prefix("user"));
var_dump($db->size());
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
Array
(
    [user.key.color] => blue
    [user.key.salary] => $ 34,45
    [user.key.size] => 17
)
Array
(
    [user.key.color] => blue
    [user.key.salary] => $ 34,45
    [user.key.size] => 17
    [user.name] => john doe
)
int(9)
Done
