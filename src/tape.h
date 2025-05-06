#ifndef TAPE_H
#define TAPE_H

#include <fstream>

class Tape{
private:
    std::fstream tape;
    int length;
public:
    Tape(const Tape&) = delete;            // Disable copying
    Tape& operator=(const Tape&) = delete;
    Tape(Tape&& other) noexcept;           // Enable moving
    Tape& operator=(Tape&& other) noexcept;

    Tape(std::string fileName);
    ~Tape();
    bool move(int offset);
    int32_t read();
    bool write(int32_t value);
    bool rewind();
    static Tape generateTape(const std::string &fileName, int size);
    static Tape tapeFromTXT(const std::string &txtFile, const std::string &tapeFile);

    int getLength();
    
};
#endif //TAPE_H