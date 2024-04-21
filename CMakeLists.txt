cmake_minimum_required(VERSION 3.22.1)

project(huffman_encoder_decoder)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(SRC_DIR src)
set(TEST_DIR test)
set(SRC ${SRC_DIR}/huffman_archiver.cpp ${SRC_DIR}/huffman_tree_node.cpp ${SRC_DIR}/huffman_tree.cpp)

include_directories(include)

add_executable(hw-02_huffman_test ${SRC} ${TEST_DIR}/test.cpp)

add_executable(hw-02_huffman ${SRC} ${SRC_DIR}/main.cpp)