
find_package(OpenCV REQUIRED)

set(TEST_SRC
    ../Image.cpp
    ../Image.hpp
    ../ImageUtil.hpp
    ../ImageUtil.cpp
    main.cpp
    imageUtilFileTest.cpp
)

include_directories(${CMAKE_SOURCE_DIR})

add_executable (fileTester ${TEST_SRC})
target_link_libraries (fileTester ${OpenCV_LIBS} fmt gtest)


