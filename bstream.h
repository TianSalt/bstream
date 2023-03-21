#ifndef BSTREAM_H_INCLUDED
#define BSTREAM_H_INCLUDED
#include <fstream>

using namespace std;

class Bstream {
private:
    fstream fs;
    unsigned char write_buffer;
    unsigned char read_buffer;
    int write_cur = 0;
    int read_cur = 0;
public:
    static const ios_base::openmode READ = ifstream::in | ifstream::binary;
    static const ios_base::openmode WRITE = ifstream::out | ifstream::binary;
    static const ios_base::openmode APPEND = ifstream::app | ifstream::binary;
    static const ios_base::openmode READ_WRITE = ifstream::in | ifstream::out | ifstream::binary;
    void open(string file_name, ios_base::openmode mode = READ_WRITE)
    { fs.open(file_name, mode); }

    Bstream(string file_name, ios_base::openmode mode = READ_WRITE)
    { open(file_name, mode); }
    
    Bstream() = default;

    void write(bool binary);

    bool read();

    void close()
    {
        while (write_cur)
            write(0);
        read_cur = 0;
        fs.close();
    }

    bool eof()
    { return fs.eof(); }

    ~Bstream()
    { close(); }
};

void Bstream::write(bool binary)
{
    write_buffer >>= 1;
    write_buffer |= binary << 7;
    if (++write_cur == 8) {
        fs.put(write_buffer);
        write_cur = 0;
    }
}

bool Bstream::read()
{
    if (!read_cur)
        read_buffer = fs.get();
    bool binary = read_buffer & 1;
    read_buffer >>= 1;
    if (++read_cur == 8)
        read_cur = 0;
    return binary;
}

#endif // BSTREAM_H_INCLUDED