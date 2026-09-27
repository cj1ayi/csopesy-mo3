## Group Members
- Billones, Francis
- Nacasabog, Joshua
- Santiago, Juan Ramon
- Tan, Roberta

## Instructions to Run

Windows only.

| Environment        | Build | Supported |
|--------------------|-------|-----------|
| Command Prompt     | g++   | ✅        |
| PowerShell         | g++   | ✅        |
| Visual Studio 2026 | CMake | ✅        |

### Windows
1. Compile: `g++ src/*.cpp -o csopesy_mo3.exe -I include`
2. Run: `.\csopesy_mo3.exe`

### Alternative (CMake)
1. `cmake -S . -B build`
2. `cmake --build build`
3. `.\build\csopesy_mo3.exe`

## Entry File
`main.cpp` (contains the main function)
