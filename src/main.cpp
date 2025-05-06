#include <iostream>
#include <filesystem>
#include "tape.h"
#include "sorter.h"

const std::string workindDir = "./tmp";

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cerr << "run with <program name> <input file> <output file>" << std::endl;
        return -1;
    }

    std::string inFileName = argv[1];
    std::string outFileName = argv[2];

    if (!std::filesystem::exists(workindDir))
    {
        if (!std::filesystem::create_directory(workindDir))
            ;
    }

    Tape inTape = Tape::tapeFromTXT(inFileName, workindDir + "/input");
    Tape outTape = Tape::generateTape(workindDir + "/output", inTape.getLength());

    Sorter sorter(workindDir + "/sorter", 16);
    sorter.sort(inTape, outTape);
    
    Tape::writeTapeToTXT(outTape,outFileName);
}
