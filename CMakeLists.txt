cmake_minimum_required(VERSION 3.14)
project(graphbuilder)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)

FetchContent_Declare(
    graphbuilder
    GIT_REPOSITORY https://github.com/frozenbubble/graphbuilder.git
    GIT_TAG 0.0.1
)

FetchContent_MakeAvailable(graphbuilder)
# find_package(graphbuilder REQUIRED)

add_executable(graphcli main.cc)
target_link_libraries(graphcli graphbuilder)
target_include_directories(graphcli PRIVATE build/_deps/graphbuilder-src)
# include(graphbuilder)