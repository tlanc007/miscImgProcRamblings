cmake_minimum_required(VERSION 3.9)

project(simpleImageProcessing)

set(CMAKE_CXX_STANDARD 14)

set(STOPWATCH_DIR /Volumes/users/tal/Documents/GoogleDrive/Docs/Programming)

include_directories (/usr/local/include ${STOPWATCH_DIR} )

link_directories (/usr/local/lib)

set(sources
    main.cpp
    image.cpp
    image.hpp
    bmpFormat.cpp
    bmpFormat.hpp
)

add_executable(image ${sources})
target_link_libraries(image fmt)

