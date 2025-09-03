#include <stdio.h>
#include <string.h>

// Socket headers
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFSIZE 1024

int main() {
    printf("Start socket test.\n");

    int status = 0;
    struct addrinfo hints = {0};
    struct addrinfo *result;
    char receive_bf[BUFSIZE];

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    status = getaddrinfo("www.google.com", "80", &hints, &result);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 1;
    }

    printf("Socket address: http://www.google.com\n");
    char ipstr[INET6_ADDRSTRLEN];
    char *ip_ver;
    struct addrinfo *cur;
    int socketfd = 0;

    for (cur = result; cur != NULL; cur = cur->ai_next) {
        if (cur->ai_family ==  AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)cur->ai_addr;
            inet_ntop(cur->ai_family, &(ipv4->sin_addr), ipstr, INET6_ADDRSTRLEN);
        }
        else if (cur->ai_family == AF_INET6) {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)cur->ai_addr;
            inet_ntop(cur->ai_family, &(ipv6->sin6_addr), ipstr, INET6_ADDRSTRLEN);
        }
        ip_ver = cur->ai_family ==  AF_INET ? "IPv4" : "IPv6";
        printf("\tIP version: %s\n", ip_ver);
        printf("\tIP address: %s\n", ipstr);
        printf("\n");

        socketfd = socket(cur->ai_family, cur->ai_socktype, cur->ai_protocol);
        if (socketfd == -1) {
            perror("Socket()");
            continue;
        };

        status = connect(socketfd, cur->ai_addr, cur->ai_addrlen);
        if (status == -1) {;
            // close(socket_fd);
            perror("Connect()");
            continue;
        }
        break;
    }
    freeaddrinfo(result);
    if (cur == NULL) {
        fprintf(stderr, "Could not connect to host.\n");
        return 0;
    }

    const char* get = "GET / HTTP/1.0\r\n"
                       "\r\n";

    printf("Sending request:\n");
    printf("%s\n", get);
    status = send(socketfd, get, strlen(get), 0);
    if (status == -1) {
        perror("Send()");
    }

    size_t bytes_rec = 0;
    while ((bytes_rec = recv(socketfd, receive_bf, BUFSIZE - 1, 0)) > 0) {
        receive_bf[bytes_rec] = '\0';
        printf("%s", receive_bf);
    }

    return 0;
}