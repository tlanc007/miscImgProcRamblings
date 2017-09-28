
find_package(OpenCV REQUIRED)

set(TEST_SRC
    ../Image.cpp
    ../Image.hpp
    ../ImageUtil.hpp
    ../ImageUtil.cpp
    main.cpp
    basicImageClassTest.cpp
    imageUtilTest.cpp
    #imageClassTest.cpp
)

include_directories(${CMAKE_SOURCE_DIR})

add_executable (tester ${TEST_SRC})
target_link_libraries (tester ${OpenCV_LIBS} fmt gtest)


