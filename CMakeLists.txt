cmake_minimum_required(VERSION 3.10)

project(sdl_game LANGUAGES CUDA CXX)

# C++ 11 标准编译
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 11)

# 控制输出的二进制文件位置
set(BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

# sdl2
find_package(SDL2 REQUIRED)
link_libraries(SDL2)


# protobuf
find_package(Protobuf REQUIRED)
if (PROTOBUF_FOUND)
        message(STATUS "ProtoBuf Found")
else()
        message(STATUS "ProtoBuf Not Found")
endif()

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# protobuf_generate_cpp Not Work !??
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS
        ${PROJECT_SOURCE_DIR}/proto/mmusim.proto)

# So I have to
file(GLOB Protobuf_files ${PROJECT_SOURCE_DIR}/proto/*.proto)
set(PROTO_META_BASE_DIR ${CMAKE_CURRENT_BINARY_DIR})

FOREACH(FIL ${Protobuf_files})
EXECUTE_PROCESS(
COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} --proto_path=${PROJECT_SOURCE_DIR}/proto --cpp_out=${PROTO_META_BASE_DIR} ${FIL}
)
endforeach()

# glog 
find_package(glog REQUIRED)
if (GLOG_FOUND)
        message(STATUS "Glog Found")
else()
        message(STATUS "Glog Not Found")
endif()

# gtest
find_package(GTest REQUIRED)
if (GTEST_FOUND)
        message(STATUS "GTest Found")
else()
        message(STATUS "GTest Not Found")
endif()

include(GoogleTest)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test main.cpp)