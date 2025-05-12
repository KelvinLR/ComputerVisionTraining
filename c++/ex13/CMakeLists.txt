cmake_minimum_required(VERSION 3.10)
project(MyProject)

find_package(OpenCV REQUIRED)

add_executable(MyProject ex13.cpp)
target_link_libraries(MyProject ${OpenCV_LIBS})

add_custom_command(TARGET MyProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/beach.jpg
            ${CMAKE_CURRENT_BINARY_DIR}
)
