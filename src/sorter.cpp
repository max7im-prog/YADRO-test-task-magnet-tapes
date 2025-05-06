#include "sorter.h"
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <limits>

#include "tape.h"

void Sorter::mergeSortedTapes(std::vector<Tape> &tapes, Tape &outputTape)
{
    // Rewind all tapes
    for (int i = 0; i < tapes.size(); i++)
    {
        tapes[i].rewind();
    }
    outputTape.rewind();

    std::vector<int32_t> elements(tapes.size());
    std::vector<bool> isActive(tapes.size(), true);

    for (int i = 0; i < tapes.size(); i++)
    {
        isActive[i] = true;
    }
    for (int i = 0; i < tapes.size(); i++)
    {
        elements[i] = tapes[i].read();
    }

    int numActive = tapes.size();
    while (numActive != 0)
    {
        // Finding minimum
        int min = std::numeric_limits<int32_t>::max();
        int minIdx = -1;
        for (int i = 0; i < tapes.size(); i++)
        {
            if (isActive[i] && elements[i] < min)
            {
                min = elements[i];
                minIdx = i;
            }
        }

        // Writing minimum to output tape
        outputTape.write(min);
        outputTape.move(1);

        // Reading next value from input tape where the minimum has been found
        if (!tapes[minIdx].move(1))
        {
            isActive[minIdx] = false;
            numActive--;
        }
        else
        {
            elements[minIdx] = tapes[minIdx].read();
        }
    };
}

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
    this->memory.resize(memorySize / sizeof(int32_t));
    this->tapes.clear();
}

// Sorts a tape inputTape into outputTape
// Performs external merge sort
// Creates multiple temp tapes in a ./tmp directory
// Throws on failure
void Sorter::sort(Tape &inputTape, Tape &outputTape)
{
    this->tapes.clear();
    for (int tapeNum = 0, complete = false; !complete; tapeNum++)
    {
        int elementsRead = 0;

        // Read from tape to memory
        while (elementsRead < this->memory.size())
        {
            memory[elementsRead++] = inputTape.read();
            if (!inputTape.move(1))
            {
                complete = true;
                break;
            }
        }

        // Sort data in memory
        std::sort(this->memory.begin(), this->memory.begin() + elementsRead);

        // Create a new tape and write sorted data into it
        std::string newTapeName = this->workingDir + "/temp" + std::to_string(tapeNum);
        Tape newTape = Tape::generateTape(newTapeName, elementsRead);

        int pos = 0;
        do
        {
            newTape.write(this->memory[pos]);
            pos++;
        } while (newTape.move(1));
        newTape.rewind();
        this->tapes.push_back(std::move(newTape));
    }

    // Merge constructed tapes
    this->mergeSortedTapes(this->tapes,outputTape);

    inputTape.rewind();
    outputTape.rewind();
}
