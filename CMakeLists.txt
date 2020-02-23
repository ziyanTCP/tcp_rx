cmake_minimum_required(VERSION 3.15)
project(tcp_rx C)

set(CMAKE_C_STANDARD 11)

include_directories(/home/ziyan/song/Dropbox/dpdk/x86_64-native-linuxapp-gcc/include/)
LINK_DIRECTORIES(/home/ziyan/song/Dropbox/dpdk/x86_64-native-linuxapp-gcc/include/)


include_directories(/home/ziyan/Dropbox/mylibrary/dpdk_tools/lib/tcp/)
LINK_DIRECTORIES(/home/ziyan/Dropbox/mylibrary/dpdk_tools/lib/tcp/)


add_executable(tcp_rx
        tcp_rx.c
        /home/ziyan/Dropbox/mylibrary/dpdk_tools/lib/tcp/tcp.c)

