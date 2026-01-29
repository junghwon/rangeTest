cmake_minimum_required(VERSION 3.10)
project(MicrowaveControl C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Source files
set(SOURCES
    main.c
    core.c
    io.c
    application.c
)

# Create executable
add_executable(microwave ${SOURCES})

# Platform-specific linking
if(WIN32)
    target_link_libraries(microwave)
else()
    target_link_libraries(microwave pthread m)
endif()

# Testing support
enable_testing()

# Optional: Add unit test targets
add_executable(test_core core.c)
target_compile_definitions(test_core PRIVATE UNIT_TEST)
