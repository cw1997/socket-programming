add_executable(main_${OUTPUT_FILENAME_SUFFIX} main.cpp)

add_executable(udp_server_${OUTPUT_FILENAME_SUFFIX} config.h udp_server.c)
add_executable(udp_client_${OUTPUT_FILENAME_SUFFIX} config.h udp_client.c)

add_executable(tcp_server_${OUTPUT_FILENAME_SUFFIX} config.h tcp_server.c)
add_executable(tcp_client_${OUTPUT_FILENAME_SUFFIX} config.h tcp_client.c)
