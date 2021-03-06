#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *addr = (argv[1]);
    int port = atoi(argv[2]);
    printf("start TCP Client to connect TCP Server: %s:%d ...\n", addr, port);

    int socket_fd;
    socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("socket error");
        return 1;
    }

    struct sockaddr_in remote_address;
    memset(&remote_address, 0, sizeof(remote_address));
    remote_address.sin_family = AF_INET;
    remote_address.sin_addr.s_addr = inet_addr(addr);
    remote_address.sin_port = htons(port);
    struct sockaddr *remote_socket_address = (struct sockaddr *) &remote_address;
    size_t socket_address_length = sizeof(struct sockaddr);

    int connect_ret = connect(socket_fd, remote_socket_address, socket_address_length);
    if (connect_ret < 0) {
        perror("connect server failed");
        return 1;
    }

    while (1) {
        char buf[BUFSIZ];
        printf("please input message:");
        scanf("%s", buf);

        size_t send_ret = write(socket_fd, buf, strlen(buf));
        if (send_ret <= 0) {
            perror("send error");
            return 1;
        }
    }

    close(socket_fd);

    return 0;
}
