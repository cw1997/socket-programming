add_executable(main main.cpp)

add_executable(udp_server config.h udp_server.c)
add_executable(udp_client config.h udp_client.c)

add_executable(tcp_server config.h tcp_server.c)
add_executable(tcp_client config.h tcp_client.c)
