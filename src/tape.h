#ifndef TAPE_H
#define TAPE_H

#include <fstream>
#include <chrono>

struct TapeConfig{
    std::chrono::milliseconds readDelay;
    std::chrono::milliseconds writeDelay;
    std::chrono::milliseconds moveDelay;
    std::chrono::milliseconds rewindDelay;
};

class Tape{
private:
    std::fstream tape;
    int length;

    const std::chrono::milliseconds readDelay;
    const std::chrono::milliseconds writeDelay;
    const std::chrono::milliseconds moveDelay;
    const std::chrono::milliseconds rewindDelay;
public:
    Tape(const Tape&) = delete;            // Disable copying
    Tape& operator=(const Tape&) = delete;
    Tape(Tape&& other) noexcept;           // Enable moving
    Tape& operator=(Tape&& other) noexcept;

    Tape(std::string fileName, TapeConfig config);
    ~Tape();
    bool move(int offset);
    int32_t read();
    bool write(int32_t value);
    bool rewind();
    static Tape generateTape(const std::string &fileName, int size, TapeConfig config);
    static Tape tapeFromTXT(const std::string &txtFile, const std::string &tapeFile, TapeConfig config);
    static void writeTapeToTXT(Tape& tape, const std::string &txtFile);

    int getLength();
    
};
#endif //TAPE_H