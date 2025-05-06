#ifndef SORTER_H
#define SORTER_H

#include "tape.h"

// Class that overseas the directory with temporary tapes and performs sorting operations
class Sorter{
private:
    const std::string workingDir; // Directory for temporary tape files
    const int memorySize;
public:
    Sorter(std::string workingDir, int memorySize);
    void sort(Tape& inputTape, Tape& outputTape);
};

#endif //SORTER_H