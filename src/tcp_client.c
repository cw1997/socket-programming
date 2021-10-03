#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory.h>

#include "config.h"

int main(int argc, char *argv[]) {
    struct sockaddr_in local_address;
    memset(&local_address, 0, sizeof(local_address));
    local_address.sin_family = AF_INET;
    local_address.sin_addr.s_addr = CLIENT_IP;
    local_address.sin_port = htons(CLIENT_PORT);
    struct sockaddr *local_socket_address = (struct sockaddr *) &local_address;
    size_t socket_address_length = sizeof(struct sockaddr);

    int socket_fd;
    socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("socket error");
        return 1;
    }

    int bind_ret = bind(socket_fd, local_socket_address, socket_address_length);
    if (bind_ret < 0) {
        perror("bind error");
        return 1;
    }

    struct sockaddr_in remote_address;
    memset(&remote_address, 0, sizeof(remote_address));
    remote_address.sin_family = AF_INET;
    remote_address.sin_addr.s_addr = SERVER_IP;
    remote_address.sin_port = htons(SERVER_PORT);
    struct sockaddr *remote_socket_address = (struct sockaddr *) &remote_address;

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
