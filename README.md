# socket-programming
[![CMake](https://github.com/cw1997/socket-programming/actions/workflows/cmake.yml/badge.svg)](https://github.com/cw1997/socket-programming/actions/workflows/cmake.yml)

As a Teaching Assistant, this is a sample project about socket programming for my teaching in a capstone course in NTUST(National Taiwan University of Science and Technology)

## build
    chmod +x ./build.sh && ./build.sh

Then check the directory `./build/bin`

## usage
tcp_client_Linux_x86_64 <ip address> <port>
tcp_server_Linux_x86_64 <ip address> <port>
udp_client_Linux_x86_64 <ip address> <port>
udp_server_Linux_x86_64 <ip address> <port>

    chmod +x ./build/bin/*
    cd ./build/bin
    ./tcp_client_Linux_x86_64 127.0.0.1 10607
    ./tcp_server_Linux_x86_64 127.0.0.1 10607
    ./udp_client_Linux_x86_64 127.0.0.1 10607
    ./udp_server_Linux_x86_64 127.0.0.1 10607
