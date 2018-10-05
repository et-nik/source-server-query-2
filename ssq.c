#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>

int get_server_info(char ip_addr[], char port[]);
int write();
char A2S_INFO[] = {0xFF, 0xFF, 0xFF, 0xFF, 0x54, 0x53, 0x6F, 0x75, 0x72, 0x63,
                   0x65, 0x20, 0x45, 0x6E, 0x67, 0x69, 0x6E, 0x65, 0x20, 0x51,
                   0x75, 0x65, 0x72, 0x79, 0x00};

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Incorrect number of parameters:\n");
        printf("    ./ssq server port\n");
        return 1;
    }

    printf("Given parameters:\n");
    printf("     Host: %s\n", argv[1]);
    printf("     Port: %s\n", argv[2]);
    get_server_info(argv[1], argv[2]);

    return 0;
}

int get_server_info(char ip_addr[], char port[])
{
    int udp_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (udp_sock == -1) {
        printf("Failed to create UDP socket\n");
        exit(1);
    }

    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    if (setsockopt(udp_sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0) {
        printf("Setsockopt failed\n");
        exit(1);
    }

    struct addrinfo hints;
    struct addrinfo *result;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;
    int src_addr = getaddrinfo(ip_addr, port, &hints, &result);

    if (src_addr != 0) {
        printf("Failed to resolve remote socket address: %s\n", gai_strerror(src_addr));
        exit(1);
    }

    //printf("%s\n", A2S_INFO);
    ssize_t resp = sendto(udp_sock, A2S_INFO, strlen(A2S_INFO) + 1, 0, result->ai_addr, result->ai_addrlen);

    if (resp == -1) {
        printf("Sending packet failed: %s\n", strerror(errno));
        exit(1);
    }

    char buffer[1472];
    ssize_t recv = recvfrom(udp_sock, buffer, sizeof(buffer), 0, NULL, NULL);

    //memset(&buffer, 0, 5);
    if (recv < 1) {
        printf("Response was empty or error occurred.\n");
        exit(1);
    }

    // i = 6 since 0-4 is just packet information.
    // Different attributes about the server are separated in the
    // incoming data by the \0 character, so "replacing" those with
    // newlines makes the output more legible.
    // I also really only care about the first 4 attributes, so the loop
    // breaks once it's printed the first four.
    int j = 0;
    for (int i = 6; i < recv; i++) {
        if (j == 4) {
            break;
        }

        if (buffer[i] == '\0') {
            printf("\n");
            j++;
        }
        else {
            printf("%c", buffer[i]);
        }
    }

    return 0;
}