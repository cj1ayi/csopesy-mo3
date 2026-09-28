## Group Members
- Billones, Francis
- Nacasabog, Joshua
- Santiago, Juan Ramon
- Tan, Roberta

## Instructions to Run

| Environment        | Build | Supported |
|--------------------|-------|-----------|
| Command Prompt     | g++   | ✅        |
| PowerShell         | g++   | ✅        |
| Visual Studio 2026 | CMake | ✅        |
| macOS / Linux      | g++   | ✅        |

### Windows
1. Compile: `g++ -std=c++20 -Wall -Wextra -Werror src/*.cpp -o csopesy_mo3.exe -I include`
2. Run: `.\csopesy_mo3.exe`

### macOS / Linux
1. Compile: `g++ -std=c++20 -Wall -Wextra -Werror -pthread src/*.cpp -o csopesy_mo3 -I include`
2. Run: `./csopesy_mo3`

### Alternative (CMake)
1. `cmake -S . -B build`
2. `cmake --build build`
3. `.\build\csopesy_mo3.exe` (Windows) or `./build/csopesy_mo3` (macOS / Linux)

## Entry File
`main.cpp` (contains the main function)
