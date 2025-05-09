cmake_minimum_required(VERSION 3.31)
project(testclion)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3 -Wall -stdlib=libc++")

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/thirdparty/libint/include
        ${PROJECT_SOURCE_DIR}/thirdparty/rapidjson/include
)

# 设置链接库路径
#link_directories(
#        /home/linzz/soft/anaconda3/envs/libint/lib
#)

# 收集 src 文件夹下所有源文件
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# 添加可执行文件
add_executable(MyExecutable ${SRC_FILES})

# 链接 libint2
#target_link_libraries(MyExecutable PRIVATE int2)

