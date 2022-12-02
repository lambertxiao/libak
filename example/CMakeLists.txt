project(libak)

set(CODE_ROOT "/root/workspace/libak")
include_directories("${CODE_ROOT}/src")
include_directories("${CODE_ROOT}/deps/include")
link_directories("${CODE_ROOT}/deps/lib")

aux_source_directory("${CODE_ROOT}/src" SRC)
aux_source_directory("${CODE_ROOT}/src/poller" POLLER)
aux_source_directory("${CODE_ROOT}/src/channelg" CHANNELG)
aux_source_directory("${CODE_ROOT}/src/common" COMMON)
set(SRC_DIR ${SRC} ${COMMON} ${POLLER} ${CHANNELG})

set(WARNING_FLAGS "-Wall")

set(CMAKE_C_COMPILER "/usr/local/bin/g++")
set(CMAKE_CXX_COMPILER "/usr/local/bin/g++")

set(CMAKE_CXX_FLAGS "${WARNING_FLAGS} -std=c++17 -Wall -fPIC -DRTE_MACHINE_CPUFLAG_AVX2 -fstack-protector-all -lpthread -D_FILE_OFFSET_BITS=64")
set(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb -O0 ")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -ggdb -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(libak-hello ${CODE_ROOT}/example/hello.cpp ${SRC_DIR})

# 链接静态库
target_link_libraries(
    libak-hello dl libfmt.a libfmtlog-static.a
)
