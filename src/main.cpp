#include <iostream>
#include <filesystem>
#include <algorithm>
#include "tape.h"
#include "sorter.h"

const std::string workindDir = "./tmp";

void configFromFile(int &memorySize, TapeConfig &config, std::string filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        throw std::runtime_error("Failed to open config file: " + filename);
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string key, valueStr;
        if (std::getline(iss, key, '=') && std::getline(iss, valueStr))
        {
            int value = std::stoi(valueStr);
            if (key == "memorySize")
                memorySize = std::max(value, 10);
            else if (key == "readDelay")
                config.readDelay = std::chrono::milliseconds(value);
            else if (key == "writeDelay")
                config.writeDelay = std::chrono::milliseconds(value);
            else if (key == "moveDelay")
                config.moveDelay = std::chrono::milliseconds(value);
            else if (key == "rewindDelay")
                config.rewindDelay = std::chrono::milliseconds(value);
        }
    }
}

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        std::cerr << "run with <program name> <input file> <output file> <configuration file>" << std::endl;
        return -1;
    }

    std::string inFileName = argv[1];
    std::string outFileName = argv[2];
    std::string configFileName = argv[3];

    TapeConfig config;
    int memorySize;
    configFromFile(memorySize,config, configFileName);

    if (!std::filesystem::exists(workindDir))
    {
        if (!std::filesystem::create_directory(workindDir))
            ;
    }

    Tape inTape = Tape::tapeFromTXT(inFileName, workindDir + "/input", config);
    Tape outTape = Tape::generateTape(workindDir + "/output", inTape.getLength(),config);

    auto start = std::chrono::high_resolution_clock::now();
    Sorter sorter(workindDir + "/sorter", memorySize, config);
    sorter.sort(inTape, outTape);

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);

    Tape::writeTapeToTXT(outTape,outFileName);
    std::cout <<"Complete, took " <<duration.count() <<" milliseconds to sort" <<std::endl;
}
