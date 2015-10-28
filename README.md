# php-atree
Fast memory tree storage structure for PHP

Atree is an in-memory search tree optimized for fast data retrieval. The search tree is based on a radix tree but avoids the
wasted space of internal nodes.

Atree allows PHP developers to quickly store data in memory regardless of their datatype or size.

## Building

Follow the usual PHP extension instructions
```sh
phpize
./configure --enable-atree
make
make test
```

# Installing

Copy the extension from modules/atree.* to your php extension directory. Then load the extension from the `php.ini` config file.
```
extension=atree.so
# in case of Windows
extension=atree.dll
``` 

Will load the extension from the `extension_dir` directive.

## example

```php
$db = new atree();
$db->put("key", "value");
$db->put("key2", array("foo","bar"));
echo $db->get("key2");
```

For more examples see the [example.php](example.php)

## License

BSD 3-cause
