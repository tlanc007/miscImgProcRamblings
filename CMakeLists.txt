cmake_minimum_required(VERSION 3.9)

project(simpleImageProcessing)

set(CMAKE_CXX_STANDARD 14)

include_directories (/usr/local/include)

link_directories (/usr/local/lib)

set(sources
    main.cpp
    image.cpp
    image.hpp
)

add_executable(image ${sources})
target_link_libraries(image fmt)

