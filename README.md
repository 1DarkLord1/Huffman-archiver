# Huffman-archiver
### Archiver based on Huffman algorithm.

#### Command line parameters:

    -c: archive mod
    -u: unarchive mod
    -f, --file <input file path>
    -o, --output <output file path>

#### Program output: 
The size of the source data, the size of the processed (archived or unarchived) data, the size of the additional data (in bytes).

#### Examples:
```
$ ./huffman -c -f qwerty.txt -o compressed.bin
    15678
    6172
    482
```
```
$ ./huffman -u -f compressed.bin -o new_qwerty.txt
   6172
   15678
   482
```
   
#### Building of the main program:
 ```
 make huff
 ```

#### Building of the tests:
```
make test
```

#### Clean:
```
make clean
```
