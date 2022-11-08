cmake_minimum_required(VERSION 3.21)
project(untitled26)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled26 main.cpp Vector2D/Vector2D.cpp Vector2D/Vector2D.h Trace/Trace.cpp Trace/Trace.h)

include_directories(D:/MyProzects/SFML_CLion/SFML-2.5.1/include)

set(SFML_ROOT D:/MyProzects/SFML_CLion/SFML-2.5.1)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(untitled26 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()


# Copy dlls to build
