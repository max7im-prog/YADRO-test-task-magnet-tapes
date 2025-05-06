#include "sorter.h"
#include <filesystem>
#include <iostream>
#include "tape.h"

// Throws if failed to create a working directory
Sorter::Sorter(std::string workingDir, int memorySize = 1024) : workingDir(workingDir),
                                                                memorySize(memorySize)
{
    if (!std::filesystem::exists(workingDir))
    {
        if (!std::filesystem::create_directory(workingDir))
        {
            throw std::runtime_error("Failed to create a directory " + workingDir);
        }
    }
}

// Sorts a tape inputTape into outputTape
// Throws on failure
void Sorter::sort(Tape& inputTape, Tape& outputTape)
{
    
}
