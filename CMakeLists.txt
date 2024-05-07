cmake_minimum_required(VERSION 3.24)
project(LEARNOPENGL)
link_directories(./depends/lib)
link_libraries(libglfw3.a opengl32.lib)
# 添加C源文件 GLOB_RECURSE：递归地匹配指定目录下的文件，包括子目录中的文件
file(GLOB_RECURSE SOURCE_C_FILES "src/*.c")
# 添加C++源文件
file(GLOB_RECURSE SOURCE_CPP_FILES "src/*.cpp")
# 添加可执行文件
add_executable(main ${SOURCE_C_FILES} ${SOURCE_CPP_FILES})
# 设置编译选项
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++2a")
include_directories(include depends/include)
# target_include_directories(main PUBLIC ./depends/include)
# target_include_directories(main PUBLIC ./src/vendor)