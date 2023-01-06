set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(num src/number.cpp)

target_link_libraries(num ${OpenCV_LIBS})

