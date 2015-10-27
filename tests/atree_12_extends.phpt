--TEST--
Atree::extends tests
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php
class child extends atree {
    function __construct () { }
}

try {
    $a = new child();
    $a->put('foo', 'bar');
} catch (Exception $e) {
    echo 'Caught instance exception: ',  $e->getMessage(), "\n";
}

class btree extends atree {
    function __construct() {
        parent::__construct();
    }
}
$db = new btree();
var_dump($db->put('foo', 'bar'));
echo "Done\n";
?>
--EXPECTF--
Caught instance exception: The object has not been correctly initialised
bool(true)
Done
