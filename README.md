# Bstream Class
The `Bstream` class is a binary stream class that allows you to read and write individual bits to a binary file.

## Getting Started
To use the `Bstream` class, you'll need to include the `Bstream.h` header file in your project.

```c++
#include "Bstream.h"
```
## Creating an Object
To use the `Bstream` class, you'll need to create an object of the class.

```c++
Bstream bstream;
```
You can also specify the filename and mode for the file in the constructor.

```c++
Bstream bstream("filename.bin", Bstream::WRITE);
```
## Opening a File
To open a file for reading and writing, you can use the `open()` method.

```c++
bstream.open("filename.bin", Bstream::READ_WRITE);
```
## Reading and Writing Bits
To read a bit from the file, you can use the `read()` method. It returns a boolean value that specifies the bit read. If the bit read is 1, it returns `true`; if it is 0, it returns `false`.

```c++
bool bit = bstream.read();
```
To write a bit to the file, you can use the `write()` method. It takes a boolean value that specifies the bit to be written. If the value is `true`, a 1 is written to the file; if it is `false`, a 0 is written.

```c++
bstream.write(true);
```
## Closing the File
To close the file, you can use the `close()` method.

```c++
bstream.close();
```
## Example
Here's an example of how you could use the Bstream class to read and write bits to a binary file.

```c++
#include "Bstream.h"

int main() {
    // create an object of the Bstream class
    Bstream bstream("filename.bin", Bstream::WRITE);

    // write some bits to the file
    bstream.write(true);
    bstream.write(false);
    bstream.write(true);
    bstream.write(false);

    // close the file
    bstream.close();

    // reopen the file for reading
    bstream.open("filename.bin", Bstream::READ);

    // read the bits from the file
    bool bit1 = bstream.read();
    bool bit2 = bstream.read();
    bool bit3 = bstream.read();
    bool bit4 = bstream.read();

    // close the file
    bstream.close();

    // print the bits to the console
    std::cout << bit1 << " " << bit2 << " " << bit3 << " " << bit4 << std::endl;

    return 0;
}
```
This code will output 1 0 1 0 to the console, indicating that the bits 1010 were successfully written and read from the file.