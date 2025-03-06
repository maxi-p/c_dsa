#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>

int main() {
    int sfd, cfd, result;
    socklen_t client_addr_size;
    struct sockaddr_in addr, client_addr;

    sfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sfd == -1) {
        perror("socket");
        exit(-1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr);
    result = bind(sfd, (struct sockaddr *) &addr, sizeof(addr));
    if (result == -1) {
        perror("bind");
        exit(1);
    }

    result = listen(sfd, 10);
    if (result == -1) {
        perror("listen");
        exit(1);
    }

    client_addr_size = sizeof(client_addr);
    cfd = accept(sfd, (struct sockaddr *) &client_addr, &client_addr_size);
    if (cfd == -1) {
        perror("accept");
        exit(1);
    }

    write(cfd, "Hello\n", 6);
    char buffer[1024] = {0};
    read(cfd, buffer, 1024);
    printf("%s\n", buffer);

    result = close(sfd);
    if (result == -1) {
        perror("close");
        exit(1);
    }

    return 0;
}