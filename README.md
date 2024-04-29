# Pong written in C++

Classic Pong game written in C++. It features a simple and responsive interface, allowing two players to compete against each other.

![Pong Game Preview](assets/image/pong_preview.png)

## Technologies
This project is built using several technologies:

- **C++**: The primary programming language used for game logic and graphics rendering.
- **MinGW/MSVC**: Windows compilers used to compile project.
- **Vcpkg**: C++ library manager used to simplify external library implementation.
- **CMake**: Used for automating the build process.
- **SDL2**: A cross-platform development library designed to provide low-level access to graphics hardware. Used for rendering graphics and handling input in the game.
- **Git**: Version control and source code management.

## Features
- Two-player mode
- Keyboard controls for both players
- Scoring system
- Ball speed increases after each successful hit
- Pause and resume functionality

## Prerequisites
- MinGW/MSVC
- CMake (version 3.0 or higher)
- Windows

## How to Run
1. Download the latest release from the [releases page](https://github.com/Danielaca18/Pong/releases).
2. Extract the contents of the ZIP file.
3. Navigate to the extracted directory in your terminal or command prompt.
4. Run the executable file `pong.exe`

 ## Controls
- General:
    - Space: Resume game
- Player 1:
    - W: Mode paddle up
    - S: Move paddle down
- Player 2:
    - Up Arrow: Move paddle up
    - Down Arrow: Move paddle down

## How to Compile and Debug
1. Clone this repository or download the source code as a ZIP file.
2. Navigate to the project directory in your terminal or command prompt.
3. Run the following command:
```bash
build.bat debug
```
4. At this point, you should see a new directory called `build/debug` in the project directory, containing the generated project files.
5. Open the generated project files in your preferred IDE (e.g., Visual Studio, Code::Blocks, etc.).
6. Attach the debugger to the pong.exe and start debugging the application.


## License
This project is licensed under the GPL v3.0 License - see the `LICENSE` file for details.
