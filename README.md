# TaskList - C++ Command Line Task Manager

A modern C++ command-line task management application demonstrating Object-Oriented Programming principles and best practices.

## Overview

TaskList is a command-line task manager that allows users to create, manage, and track tasks efficiently. The project serves as a practical example of implementing clean architecture and modern C++ features.

## Features

- Create tasks with titles and descriptions
- Mark tasks as complete
- Delete individual tasks
- Clear completed tasks
- Persistent storage using JSON
- Activity logging
- Clean command-line interface

## Technical Details

- Modern C++ (C++17)
- CMake build system
- JSON storage using nlohmann/json
- OOP principles (inheritance, polymorphism, encapsulation)
- RAII for resource management
- Singleton pattern for logging
- Smart pointers for memory safety

## Prerequisites

- C++17 compatible compiler (GCC, Clang, MSVC)
- CMake (>= 3.10)
- nlohmann/json library (install via package manager)

### Installing Dependencies

#### Ubuntu/Debian

```bash
sudo apt install cmake nlohmann-json3-dev
```

#### Arch Linux

```bash
sudo pacman -S cmake nlohmann-json
```

#### macOS

```bash
brew install cmake nlohmann-json
```

## Building the Project

```bash
# Clone the repository
git clone https://github.com/xOphiuchus/TaskList.git
cd TaskList

# Create build directory
mkdir build && cd build

# Generate build files
cmake ..

# Build the project
make
```

## Usage

```bash
# Show help menu
./TaskList help

# List all tasks
./TaskList list

# Add a new task
./TaskList add "Complete project" "Finish the TaskList project implementation"

# Mark task as complete
./TaskList done 1

# Delete a task
./TaskList delete 1

# Clear completed tasks
./TaskList clear
```

## Project Structure

```
TaskList/
├── src/
│   ├── BaseTask.hpp      # Abstract base class for tasks
│   ├── Task.cpp          # Concrete task implementation
│   ├── Task.hpp
│   ├── TaskList.cpp      # Main task management logic
│   ├── TaskList.hpp
│   ├── Logger.cpp        # Logging functionality
│   ├── Logger.hpp
│   ├── TUI.cpp          # Text User Interface
│   ├── TUI.hpp
│   └── main.cpp         # Entry point
├── CMakeLists.txt       # Build configuration
├── .gitignore
└── README.md
```

## Contributing

Feel free to contribute to this project by:

1. Forking the repository
2. Creating a new branch for your feature
3. Submitting a pull request

## License

This project is open source and available under the MIT License.

## Author

[xOphiuchus](https://github.com/xOphiuchus)
