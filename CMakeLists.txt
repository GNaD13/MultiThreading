cmake_minimum_required(VERSION 3.0)

# C++ std 14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-no-pie")

project(testMultiThread)

#Setup
file(GLOB SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    -lpthread
)
