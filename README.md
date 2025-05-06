# YADRO Magnet Tape Sorter

This project implements an **external merge sort algorithm** for sorting large datasets stored on virtual magnetic tapes. It is designed to handle data sizes that exceed available memory, using temporary tapes to facilitate sorting.

## 📁 Project Structure

```
.
├── src/                # Source code (.cpp/.h files)
├── test/               # Tests
├── CMakeLists.txt      # CMake configuration
└── README.md           # This file
```

## 🛠 Build Instructions

### Requirements
- CMake (version 3.10+ recommended)
- C++17 compatible compiler (e.g. `g++` or `clang++`)

### Build Steps

```bash
# Clone and enter the project
git clone https://github.com/max7im-prog/YADRO-test-task-magnet-tapes
cd YADRO-test-task-magnet-tapes

# Create and enter the build directory
mkdir -p build && cd build

# Generate build files
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Compile
cmake --build .
```

The executable will be created as:
```
build/YADRO-test-task
```

## 🚀 Usage

### Run the program:

```bash
./YADRO-test-task <input_txt_file> <output_txt_file>
```

Example:

```bash
./YADRO-test-task ../test/testcases/case1.txt ./output.txt
```

The program uses a temporary directory at `./build/tmp` to store intermediate tape files.

## 🧪 Test Case Format

Each input `.txt` file should contain one integer per line. For example:

```
5
3
8
1
2
```

## 📝 Notes

- The `Sorter` class uses a configurable memory buffer to perform partial sorts.
- Intermediate sorted chunks are written to temporary tapes and then merged into the output tape.
- Make sure to clean the `tmp/` directory before each run if needed.

## 📄 License

MIT License (or specify your own)
