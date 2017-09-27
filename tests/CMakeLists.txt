


set(TEST_SRC
    ../Image.cpp
    ../Image.hpp
    main.cpp
    basicImageClassTest.cpp
    #imageClassTest.cpp
)

include_directories(${CMAKE_SOURCE_DIR})

add_executable (tester ${TEST_SRC})
target_link_libraries (tester fmt gtest)


