#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *addr = argv[1];
    int port = atoi(argv[2]);
    printf("start TCP Server at %s:%d ...\n", addr, port);

    struct sockaddr_in local_address;
    memset(&local_address, 0, sizeof(local_address));
    local_address.sin_family = AF_INET;
    local_address.sin_addr.s_addr = inet_addr(addr);;
    local_address.sin_port = htons(port);
    struct sockaddr *local_socket_address = (struct sockaddr *) &local_address;
    size_t socket_address_length = sizeof(struct sockaddr);

    int socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("socket error");
        return 1;
    }

    int bind_ret = bind(socket_fd, local_socket_address, socket_address_length);
    if (bind_ret < 0) {
        perror("bind error");
        return 1;
    }

//    connection requests will be queued before further requests are refused
    int listen_queue_length = 20;
    int listen_ret = listen(socket_fd, listen_queue_length);
    if (listen_ret < 0) {
        perror("listen failed");
        return 1;
    }

    printf("waiting for clients connecting...\n");

    socklen_t socket_address_in_size = sizeof(struct sockaddr_in);
    while (1) {
        struct sockaddr_in remote_address;
        struct sockaddr *remote_socket_address = (struct sockaddr *) &remote_address;
        int client_socket_fd = accept(socket_fd, remote_socket_address, &socket_address_in_size);
        if (client_socket_fd < 0) {
            perror("could not accept client");
            continue;
//            exit(1);
        }

        printf("waiting for a packet...\n");

        while (1) {
            char buf[BUFSIZ];
            int read_bytes_length = read(client_socket_fd, &buf, BUFSIZ);
            if (read_bytes_length < 0) {
                perror("read data error");
                close(client_socket_fd);
                continue;
//            exit(1);
            }

            printf("received packet from [%s]: %s \n", inet_ntoa(remote_address.sin_addr), buf);
        }
    }

    close(socket_fd);

    return 0;
}

