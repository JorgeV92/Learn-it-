cmake_minimum_required(VERSION 3.11)

project(BST)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    cli11_proj
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.3.2
)

FetchContent_MakeAvailable(cli11_proj)

add_executable(bst bst.cpp)

target_link_libraries(bst PRIVATE CLI11::CLI11)
