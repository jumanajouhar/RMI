#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080

extern int factorial(int);
extern double power(double, int);

void handle_client(int client_socket) {
    int choice;
    read(client_socket, &choice, sizeof(choice));
    
    if (choice == 1) { // Factorial
        int num, result;
        read(client_socket, &num, sizeof(num));
        result = factorial(num);
        send(client_socket, &result, sizeof(result), 0);
    } else if (choice == 2) { // Power
        double base;
        int exp;
        double result;
        read(client_socket, &base, sizeof(base));
        read(client_socket, &exp, sizeof(exp));
        result = power(base, exp);
        send(client_socket, &result, sizeof(result), 0);
    }
    
    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);
    printf("Server is listening on port %d\n", PORT);

    while ((client_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen))) {
        handle_client(client_socket);
    }

    return 0;
}