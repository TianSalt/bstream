#ifndef BSTREAM_H_INCLUDED
#define BSTREAM_H_INCLUDED

#include <fstream>
#include <stdexcept> // Required for runtime_error
#include <climits>

class Bstream
{
private:
    std::fstream fs; // File stream object
    unsigned char write_buffer; // Buffer used for writing binary data
    unsigned char read_buffer; // Buffer used for reading binary data
    int write_cur = 0; // Current position in the write buffer
    int read_cur = 0; // Current position in the read buffer

public:
    // Constants for specifying file mode
    static const std::ios_base::openmode READ = std::ios_base::in | std::ios_base::binary;
    static const std::ios_base::openmode WRITE = std::ios_base::out | std::ios_base::binary;
    static const std::ios_base::openmode APPEND = std::ios_base::app | std::ios_base::binary;
    static const std::ios_base::openmode READ_WRITE = std::ios_base::in | std::ios_base::out | std::ios_base::binary;
    
    // Opens the file with the specified file name and mode
    void open(std::string file_name, std::ios_base::openmode mode = READ_WRITE);

    // Constructor that opens the file with the specified file name and mode
    Bstream(std::string file_name, std::ios_base::openmode mode = READ_WRITE)
    {
        open(file_name, mode);
    }

    // Default constructor
    Bstream() = default;

    // Writes the specified binary value to the file
    void write(bool binary);

    // Reads a binary value from the file
    bool read();

    // Closes the file
    void close();

    // Returns true if the end of the file has been reached
    bool eof()
    {
        return fs.eof();
    }

    // Destructor that calls the close() function
    ~Bstream()
    {
        close();
    }
};

void Bstream::open(std::string file_name, std::ios_base::openmode mode) {
    fs.open(file_name, mode);

    // Throws an exception if the file failed to open
    if (!fs.is_open())
        throw std::runtime_error("Failed to open file");
}

void Bstream::close()
{
    // Writes any remaining bits in the write buffer to the file
    while (write_cur)
        write(0);

    read_cur = 0; // Resets the read buffer position
    fs.close(); // Closes the file
}

void Bstream::write(bool binary)
{
    // Shift the write buffer to the right by 1, making space for the new bit
    write_buffer >>= 1;

    // Set the most significant bit of the write buffer to the value of the boolean
    // (0 if false, 1 if true)
    write_buffer |= binary << (CHAR_BIT - 1);

    // Increment the write cursor to keep track of the number of bits in the buffer
    if (++write_cur == CHAR_BIT) {
        // If the buffer is full, write its contents to the file
        if (!fs.write(reinterpret_cast<const char*>(&write_buffer), 1)) {
            throw std::runtime_error("Failed to write data to file");
        }
        // Reset the write cursor and buffer
        write_cur = 0;
    }
}


bool Bstream::read()
{
    // If the current byte has been fully read, read the next byte from the file.
    if (read_cur == 0) {
        if (!fs.read(reinterpret_cast<char*>(&read_buffer), 1)) {
            throw std::runtime_error("Failed to read data from file");
        }
    }

    // Extract the least significant bit of the current byte and shift the byte right by 1 bit.
    bool binary = read_buffer & 1;
    read_buffer >>= 1;

    // Increment the current bit position within the byte, and reset to 0 if we have read all 8 bits.
    if (++read_cur == CHAR_BIT)
        read_cur = 0;

    // Return the bit value.
    return binary;
}


#endif // BSTREAM_H_INCLUDED