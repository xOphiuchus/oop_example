cmake_minimum_required(VERSION 3.10)
project(TaskList)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)

add_executable(TaskList
    main.cpp
    Task.cpp
    TaskList.cpp
    Logger.cpp
    TUI.cpp
)

target_link_libraries(TaskList PRIVATE nlohmann_json::nlohmann_json)

