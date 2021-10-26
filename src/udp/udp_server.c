#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *addr = argv[1];
    int port = atoi(argv[2]);
    printf("start UDP Server at %s:%d ...\n", addr, port);

    struct sockaddr_in local_address;
    memset(&local_address, 0, sizeof(local_address));
    local_address.sin_family = AF_INET;
    local_address.sin_addr.s_addr = inet_addr(addr);
    local_address.sin_port = htons(port);
    struct sockaddr *local_socket_address = (struct sockaddr *) &local_address;
    size_t socket_address_length = sizeof(struct sockaddr);

    int socket_fd;
    socket_fd = socket(PF_INET, SOCK_DGRAM, 0);
    if (socket_fd < 0) {
        perror("socket error");
        return 1;
    }

    int bind_ret = bind(socket_fd, local_socket_address, socket_address_length);
    if (bind_ret < 0) {
        perror("bind error");
        return 1;
    }

    socklen_t socket_address_in_size = sizeof(struct sockaddr_in);
    printf("waiting for a packet...\n");

    while (1) {
        char buf[BUFSIZ];
        memset(buf, 0, BUFSIZ);
        struct sockaddr_in remote_address;
        struct sockaddr *remote_socket_address = (struct sockaddr *) &remote_address;
        size_t recv_length = recvfrom(socket_fd, buf, BUFSIZ, 0, remote_socket_address, &socket_address_in_size);
        if (recv_length == 0) {
            perror("recvfrom error");
            return 1;
        }

        printf("received packet from [%s]: %s \n", inet_ntoa(remote_address.sin_addr), buf);
    }

    close(socket_fd);

    return 0;
}

