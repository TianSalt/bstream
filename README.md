# bstream.h

`bstream.h` is a C++ header file that provides an implementation of a binary stream class called `Bstream`. This class allows you to read and write individual bits to a binary file.

**Note:** This code has been tested on little-endian systems only. It may not work correctly on big-endian systems, and further testing is required to ensure compatibility.

## Quick Start

To use `Bstream`, simply include the bstream.h header file in your C++ source code.

```c++
#include "bstream.h"
```

You can then create an instance of the `Bstream` class and use it to read from or write to a file.

```c++
Bstream bs("myfile.bin", Bstream::READ_WRITE);
bs.write(1);
bs.write(0);
bs.write(1);
```

In the above example, we create an instance of `Bstream` and open a file called myfile.bin in write mode. We then write three bits to the file using the write method and close the file using the close method.

We can then read the data from the file using the `Bstream` class.

```c++
bool bit1 = bs.read();
bool bit2 = bs.read();
bool bit3 = bs.read();
bs.close();
```

In the above example, we create an instance of `Bstream` and open the same file in read mode. We then read the data from the file using the read method and store it in `bit1`, `bit2`, and `bit3` variables. We then close the file using the `close()` method.

## Methods

The `Bstream` class provides the following methods:

- `void open(string file_name, ios_base::openmode mode = READ_WRITE)`
  Opens the specified file in the specified open mode.
- `void write(bool binary)`
  Writes a single bit to the file. The bit is specified as a boolean value.
- `bool read()`
  Reads a single bit from the file and returns it as a boolean value.
- `void close()`
  Flushes the write buffer (i.e. fills all unwritten bits in the last byte with zero) and closes the file.
- `bool eof()`
  Returns true if the end of the file has been reached, otherwise false.

## Open Modes

The Bstream class provides four open modes:

- `Bstream::READ` - Open the file for reading.
- `Bstream::WRITE` - Open the file for writing. Any existing data in the file is truncated.
- `Bstream::APPEND` - Open the file for writing. Data is appended to the end of the file.
- `Bstream::READ_WRITE` - Open the file for both reading and writing.

You can specify the open mode when creating an instance of the Bstream class.

```c++
Bstream bs("myfile.bin", Bstream::READ_WRITE);
```

This is equivalent to:

```c++
Bstream bs;
bs.open("myfile.bin", Bstream::READ_WRITE);
```

You can DIY your own open modes, for example:

```c++
using namespace std;
static const ios_base::openmode READ_APPEND = ios_base::in | ios_base::app | ios_base::binary;
```
