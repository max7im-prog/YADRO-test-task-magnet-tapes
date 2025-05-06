# YADRO Magnet Tape Sorter

This project implements an **external merge sort** to sort large data stored on virtual magnetic tapes. It mimics the behavior of physical tape drives by introducing configurable delays for read, write, move, and rewind operations.

---

## 📁 Project Structure

```
.
├── build/                  # CMake build artifacts (created after building)
├── src/                   # Main source files
│   ├── main.cpp           # Entry point
│   ├── sorter.cpp/.h      # Sorter logic
│   ├── tape.cpp/.h        # Tape abstraction and I/O delays
├── test/
│   └── testcases/         # Input test case files
├── external/googleTests/  # Google Test submodule
├── CMakeLists.txt         # Build configuration
└── README.md              # This file
```

---

## 🛠 Build Instructions

### 🔧 Requirements

- CMake ≥ 3.10
- C++17-compatible compiler (e.g., `g++`, `clang++`)
- Git (for cloning submodules)

### 🧱 Build Steps

```bash
# Clone repository with submodules
git clone --recurse-submodules https://github.com/max7im-prog/YADRO-test-task-magnet-tapes
cd YADRO-test-task-magnet-tapes

# Create build directory and navigate into it
mkdir -p build && cd build

# Generate build files with CMake
cmake -DCMAKE_BUILD_TYPE=Release ..

# Build the project
cmake --build .
```

Executables will be located in the `build/` directory:

- `YADRO-test-task` – main application
- `tests_runner` – Google Test executable

---

## 🚀 Usage

```bash
./YADRO-test-task <input_txt_file> <output_txt_file> <config_file>
```

Example:

```bash
./YADRO-test-task ../test/testcases/input.txt ./output.txt ../test/testcases/config.txt
```

Intermediate tape files will be stored in `./build/tmp/`.

---

## 📂 Input and Configuration Files

### ✅ Input File Format

Each line should contain a single signed 32-bit integer:

```
5
3
8
1
2
```

### ⚙️ Configuration File Format

```
memorySize=1024
readDelay=5
writeDelay=5
moveDelay=10
rewindDelay=20
```

- `memorySize`: memory buffer size in **bytes**
- All delays are in **milliseconds**

---

## ✅ Running Tests

Tests are written using Google Test and can be run as follows:

```bash
./tests_runner
```

To add more test cases, place them under `test/testcases/` and update `test_basic.cpp`.

---

## 📝 Notes

- Sorting is done using an external merge sort with tape-based I/O simulation.
- The sorter splits input into memory-sized chunks, sorts each chunk in memory, and writes them to temporary tapes.
- Temporary files are stored in `./build/tmp/`. Delete or clear this folder between runs if needed.

---

## 📄 License

MIT License – use freely for educational and professional purposes.
