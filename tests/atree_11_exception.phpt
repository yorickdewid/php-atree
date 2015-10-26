--TEST--
Atree::put tests
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$db = new Atree;
try {
    $db->put("k1", "v1");
    $db->put("k1", "v2");
} catch (Exception $e) {
    echo 'Caught put exception: ',  $e->getMessage(), "\n";
}

var_dump($db->put("k3", "v3"));
var_dump($db->put("k4", "v4"));
var_dump($db->put("k5", "v5"));

try {
    $db->get("g1");
} catch (Exception $e) {
    echo 'Caught get exception: ',  $e->getMessage(), "\n";
}

echo $db->size()."\n";
echo "Done\n";
?>
--EXPECTF--
Caught put exception: Unable to insert key
bool(true)
bool(true)
bool(true)
Caught get exception: No value found for key: g1
4
Done
