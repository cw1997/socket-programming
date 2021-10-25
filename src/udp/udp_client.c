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
    printf("start UDP Client to connect UDP Server: %s:%d ...\n", addr, port);

    struct sockaddr_in remote_address;
    memset(&remote_address, 0, sizeof(remote_address));
    remote_address.sin_family = AF_INET;
    remote_address.sin_addr.s_addr = inet_addr(addr);
    remote_address.sin_port = htons(port);
    struct sockaddr *remote_socket_address = (struct sockaddr *) &remote_address;
    size_t socket_address_length = sizeof(struct sockaddr);

    int socket_fd;
    socket_fd = socket(PF_INET, SOCK_DGRAM, 0);
    if (socket_fd < 0) {
        perror("socket error");
        return 1;
    }

    while (1) {
        char buf[BUFSIZ];
        printf("please input message:");
        scanf("%s", buf);

        size_t send_ret = sendto(socket_fd, buf, strlen(buf), 0, remote_socket_address, socket_address_length);
        if (send_ret == 0) {
            perror("send error");
            return 1;
        }
    }

    close(socket_fd);

    return 0;
}
