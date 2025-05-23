#include "tape.h"
#include <filesystem>
#include <vector>
#include <list>
#include <fstream>
#include <thread>

Tape::Tape(Tape &&other) noexcept
    : tape(std::move(other.tape)),
      length(other.length),
      readDelay(other.readDelay),
      writeDelay(other.writeDelay),
      moveDelay(other.moveDelay),
      rewindDelay(other.rewindDelay) {}

Tape &Tape::operator=(Tape &&other) noexcept
{
    if (this != &other)
    {
        tape = std::move(other.tape);
        length = other.length;
    }
    return *this;
}

// Opens a tape from a tape file
Tape::Tape(std::string fileName, TapeConfig config) : readDelay(config.readDelay),
                                                      writeDelay(config.writeDelay),
                                                      moveDelay(config.moveDelay),
                                                      rewindDelay(config.rewindDelay)
{
    if (!std::filesystem::exists(fileName))
    {
        throw std::invalid_argument("file " + fileName + " does not exist");
    }
    this->tape.open(fileName, std::ios::in | std::ios::out | std::ios::binary);
    if (!this->tape.is_open())
    {
        throw std::ios_base::failure("Failed to open file: " + fileName);
    }

    // Find file length
    tape.seekg(0, std::ios::end);
    this->length = tape.tellg() / sizeof(int32_t);

    // Seek back to the beginning
    tape.seekg(0, std::ios::beg);
    tape.seekp(0, std::ios::beg);
}

Tape::~Tape()
{
    this->tape.close();
}

// Moves the head of the tape by offset * sizeof(int32_t)
// Returns true if successfully moved the head, false otherwise
bool Tape::move(int offset)
{
    std::this_thread::sleep_for(moveDelay);
    std::streamoff pos = static_cast<std::streamoff>(this->tape.tellg());
    std::streamoff delta = static_cast<std::streamoff>(offset) * sizeof(int32_t);
    std::streamoff newPos = pos + delta;

    if (newPos < 0 || newPos >= this->length * sizeof(int32_t))
    {
        return false;
    }

    this->tape.seekg(newPos);
    this->tape.seekp(newPos);

    return true;
}

// Reads a value from a current position of a tape
// Throws std::ios_base::failure on failure
int32_t Tape::read()
{
    std::this_thread::sleep_for(readDelay);
    int32_t value = 0;
    std::streampos currentPos = this->tape.tellg();

    this->tape.read(reinterpret_cast<char *>(&value), sizeof(int32_t));

    if (!this->tape)
    {
        this->tape.seekg(currentPos);
        throw std::ios_base::failure("Failed to read from tape");
    }

    this->tape.seekg(currentPos);

    return value;
}

// Writes a value into a current position of a tape
// Returns true if wrote successfully, false otherwise
bool Tape::write(int32_t value)
{
    std::this_thread::sleep_for(writeDelay);
    auto currentPos = this->tape.tellp();

    this->tape.write(reinterpret_cast<char *>(&value), sizeof(int32_t));

    if (!this->tape)
    {
        this->tape.seekp(currentPos);
        this->tape.seekg(currentPos);
        return false;
    }

    this->tape.seekp(currentPos);
    this->tape.seekg(currentPos);

    return true;
}

// Moves the head back to the start of the tape
bool Tape::rewind()
{
    if (this->tape.tellg() != 0)
    {
        std::this_thread::sleep_for(rewindDelay);
        this->tape.seekg(0);
        this->tape.seekp(0);
    }
    return true;
}

// Generates a tape of a certain size by creating a file and filling it with "0", returns a new Tape object
// Throws on failure
Tape Tape::generateTape(const std::string &fileName, int size, TapeConfig config)
{
    std::ofstream file(fileName, std::ios::binary | std::ios::out | std::ios::trunc);

    if (!file)
    {
        throw std::ios_base::failure("Failed to create file " + fileName);
    }

    file.seekp((size - 1) * sizeof(int32_t));
    file.write("\0", 1);

    // Fill the file with zeros using a more efficient approach (write in bulk)
    file.seekp(0);
    int32_t zero = 0;
    const int bufferSize = 1024;
    char buffer[bufferSize];

    std::fill(std::begin(buffer), std::end(buffer), 0);

    int remainingSize = size;
    while (remainingSize > 0)
    {
        int chunkSize = std::min(remainingSize, bufferSize);
        file.write(buffer, chunkSize * sizeof(int32_t));
        remainingSize -= chunkSize;
    }

    file.close();

    return Tape(fileName, config);
}

// Throws on failure
Tape Tape::tapeFromTXT(const std::string &txtFile, const std::string &tapeFile, TapeConfig config)
{
    std::ifstream file(txtFile);
    if (!file)
    {
        throw std::ios_base::failure("failed to open " + txtFile);
    }

    Tape ret = Tape::generateTape(tapeFile, 0, config);
    std::string line;
    int32_t val;
    int size = 0;

    while (std::getline(file, line))
    {
        try
        {
            val = std::stoi(line);
        }
        catch (...)
        {
            throw std::invalid_argument("Invalid integer in line: " + line);
        }
        ret.tape.write(reinterpret_cast<char *>(&val), sizeof(int32_t));
        size++;
    }

    ret.length = size;
    ret.tape.seekg(0);
    ret.tape.seekp(0);

    return ret;
}

void Tape::writeTapeToTXT(Tape &tape, const std::string &txtFile)
{
    std::ofstream file(txtFile, std::ios::trunc);
    if (!file)
    {
        throw std::ios_base::failure("failed to open output file: " + txtFile);
    }

    tape.rewind();
    do
    {
        file << std::to_string(tape.read()) << std::endl;
    } while (tape.move(1));

    tape.rewind();
}

int Tape::getLength()
{
    return this->length;
}


