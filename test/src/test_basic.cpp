
#include <gtest/gtest.h>
#include "tape.h"
#include "sorter.h"
#include <chrono>
#include <fstream>
#include <vector>
#include <thread>

using namespace std::chrono;

// Helper function to create a dummy tape file with given values
void createDummyTapeFile(const std::string& fileName, const std::vector<int32_t>& values) {
    std::ofstream file(fileName, std::ios::binary);
    for (const int32_t& value : values) {
        file.write(reinterpret_cast<const char*>(&value), sizeof(int32_t));
    }
}

// Helper function to read values from a tape file
std::vector<int32_t> readValuesFromFile(const std::string& fileName) {
    std::ifstream file(fileName, std::ios::binary);
    std::vector<int32_t> values;
    int32_t value;
    while (file.read(reinterpret_cast<char*>(&value), sizeof(int32_t))) {
        values.push_back(value);
    }
    return values;
}

TEST(TapeTest, ReadWriteMoveRewindTest) {
    // TapeConfig with small delays for testing
    TapeConfig config{
        std::chrono::milliseconds(50), // readDelay
        std::chrono::milliseconds(50), // writeDelay
        std::chrono::milliseconds(50), // moveDelay
        std::chrono::milliseconds(50)  // rewindDelay
    };

    // Create a dummy tape file with values
    std::string tapeFile = "test_tape.dat";
    std::vector<int32_t> testData = {10, 20, 30, 40, 50};
    createDummyTapeFile(tapeFile, testData);

    // Create Tape object with config
    Tape tape(tapeFile, config);

    // Test rewind and read functionality
    tape.rewind();
    for (size_t i = 0; i < testData.size(); ++i) {
        EXPECT_EQ(tape.read(), testData[i]);
        tape.move(1); // Move by 1
    }

    // Test rewind again
    tape.rewind();
    for (size_t i = 0; i < testData.size(); ++i) {
        EXPECT_EQ(tape.read(), testData[i]);
        tape.move(1); // Move by 1
    }
}

TEST(TapeTest, WriteTest) {
    // TapeConfig with small delays for testing
    TapeConfig config{
        std::chrono::milliseconds(50),
        std::chrono::milliseconds(50),
        std::chrono::milliseconds(50),
        std::chrono::milliseconds(50)
    };

    // Create a new tape file
    std::string tapeFile = "./test_write_tape";
    Tape tape = Tape::generateTape(tapeFile,100,config);

    // Write values to the tape
    tape.rewind();
    tape.write(100);
    tape.move(1);
    tape.write(200);

    // Verify written values
    tape.rewind();
    EXPECT_EQ(tape.read(), 100);
    tape.move(1);
    EXPECT_EQ(tape.read(), 200);
}

TEST(TapeTest, MoveTest) {
    // TapeConfig with small delays for testing
    TapeConfig config{
        std::chrono::milliseconds(50),
        std::chrono::milliseconds(50),
        std::chrono::milliseconds(50),
        std::chrono::milliseconds(50)
    };

    // Create a dummy tape file with values
    std::string tapeFile = "test_move_tape.dat";
    std::vector<int32_t> testData = {1, 2, 3, 4, 5};
    createDummyTapeFile(tapeFile, testData);

    // Create Tape object from the dummy file
    Tape tape(tapeFile, config);

    // Test the move function
    tape.rewind();
    for (size_t i = 0; i < testData.size(); ++i) {
        EXPECT_EQ(tape.read(), testData[i]);
        if (i < testData.size() - 1) {
            tape.move(1);
        }
    }

    // Test rewind
    tape.rewind();
    EXPECT_EQ(tape.read(), testData[0]);
}


