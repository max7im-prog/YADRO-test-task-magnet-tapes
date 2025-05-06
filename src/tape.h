#include <fstream>

class Tape{
private:
    std::fstream tape;
    int length;
public:
    Tape(std::string fileName);
    ~Tape();
    
    bool move(int offset);

    int32_t read();
    bool write(int32_t value);

    static Tape generateTape(const std::string &fileName, int size);
    
};