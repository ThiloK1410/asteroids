cmake_minimum_required(VERSION 3.19)
project(Asteroids)

set(CMAKE_CXX_STANDARD 14)

add_executable(Asteroids src/main.cpp src/Engine.cpp headers/Engine.h src/Player.cpp headers/Player.h src/Formulas.cpp headers/Formulas.h)

include_directories(headers c:/SFML/include)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Asteroids ${SFML_LIBRARIES})
endif()



if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()