<?php

/* Create new tree */
$db = new Atree;

/* Car object */
class Car {
    private $make;
    private $age;

    function __construct($make, $age) {
        $this->make = $make;
        $this->age = $age;
    }

    function toString() {
        return "Car " . $this->make . " is " . $this->age . " years old";
    }
}

/* Create instances */
$chevy = new Car("Chevy", 2);
$ford = new Car("Ford", 5);

/* Insert objects */
$db->put("car.garage.chevy", $chevy);
$db->put("car.garage.ford", $ford);

/* Insert other types in the same prefix */
$db->put("car.all_ensured", true);
$db->put("car.fuelprice", array('disel' => 1, 'gas' => 4));

/* Other types */
$db->put("myname", "John Doe");
$db->put("list::Jane", "Smith");
$db->put("list::Hank", "Johnson");
$db->put("list::Joe", "Williams");
$db->put("list::Dave", "Jones");
$db->put("list::Mary", "James");
$db->put("list::John", "Davids");
$db->put("list::Thomas", "Phillips");
$db->put("list::Sofia", "Ángel");

/* Current tree size */
echo "Elements in tree " . $db->size() . "\n";

/* Echo myname */
echo "Hello, " . $db->get("myname") . "\n";

/* Show cars in garage */
foreach($db->prefix("car.garage") as $car) {
    echo $car->toString() . "\n";
}

/* Delete an user */
$db->delete("list::Mary");

/* Show users beginning with an 'J' */
foreach($db->prefix("list::J") as $user => $name) {
    echo "User " . explode("::", $user)[1] . " " . $name . " is active\n";
}

/* And wer're done with this tree */
$db->clear();

$db->put("php version", array(5, 7));
$db->put("license", "PHP");

print_r($db->all());
