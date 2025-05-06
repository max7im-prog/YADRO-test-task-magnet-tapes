#ifndef SORTER_H
#define SORTER_H

#include "tape.h"
#include <vector>

// Class that overseas the directory with temporary tapes and performs sorting operations
class Sorter{
private:
    const std::string workingDir; // Directory for temporary tape files
    const int memorySize; // Size in bytes
    std::vector<int32_t> memory;
    std::vector<Tape> tapes;

    void mergeSortedTapes(std::vector<Tape> &tapes, Tape& outputTape);
public:
    Sorter(std::string workingDir, int memorySize);
    void sort(Tape& inputTape, Tape& outputTape);
};

#endif //SORTER_H