cmake_minimum_required(VERSION 3.26)
project(Socket_Client)

set(CMAKE_CXX_STANDARD 17)

add_executable(Socket_Client
        main.c
)

target_link_libraries(Socket_Client PRIVATE ws2_32 )
