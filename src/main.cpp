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

    std::string inFile = argv[1];
    std::string outFile = argv[2];

    if (!std::filesystem::exists(workindDir))
    {
        if (!std::filesystem::create_directory(workindDir))
            ;
    }

    Tape inTape = Tape::tapeFromTXT(inFile, workindDir + "/input");
    Tape outTape = Tape::generateTape(workindDir + "/output", inTape.getLength());

    Sorter sorter(workindDir + "/sorter", 16);
    sorter.sort(inTape, outTape);

    std::cout << "input:" << std::endl;
    do
    {
        std::cout << inTape.read() << " ";
    } while (inTape.move(1));
    inTape.rewind();
    std::cout << std::endl;
    std::cout << "output:" << std::endl;
    do
    {
        std::cout << outTape.read() << " ";
    } while (outTape.move(1));
    outTape.rewind();
    std::cout << std::endl;
}
