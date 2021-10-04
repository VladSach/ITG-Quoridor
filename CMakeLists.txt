cmake_minimum_required(VERSION 3.11)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Quoridor)

#### Add External Dependencies ####
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

#### Quoridor ####
file(GLOB_RECURSE SOURCES src/*.cpp include/*.h)
add_executable(Quoridor ${SOURCES})
target_include_directories(Quoridor PRIVATE ${SFML_INCS} ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Quoridor sfml-window sfml-graphics sfml-system)
set_target_properties(Quoridor PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})