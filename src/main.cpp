#include <iostream>
#include "tape.h"
#include "sorter.h"

int main(int argc, char** argv){
    if(argc <3){
        std::cerr << "run with <program name> <input file> <output file>" << std::endl;
        return -1;
    }

    std::string inFile = argv[1];
    std::string outFile = argv[2];

    Sorter sorter("./tmp/sorter",1024);
    Tape inTape = Tape::tapeFromTXT(inFile,"./tmp/input");
    Tape outTape = Tape::generateTape("./tmp/output",inTape.getLength());
    sorter.sort(inTape, outTape);

    std::cout <<"input:" << std::endl;
    do{
        std::cout << inTape.read() << " ";
    }while(inTape.move(1));
    std::cout <<std::endl;
    std::cout <<"output:" << std::endl;
    do{
        std::cout << outTape.read() <<" ";
    }while(outTape.move(1));
    std::cout <<std::endl;
}
