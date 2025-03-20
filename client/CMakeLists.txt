cmake_minimum_required(VERSION 3.10)

# Set the project name and C++ standard
project(client)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_U)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG_U} ${CMAKE_BINARY_DIR})
endforeach()

# Add the executable, assuming your file is main.cpp
add_executable(client client.cpp)

target_link_libraries(client PRIVATE Ws2_32)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
