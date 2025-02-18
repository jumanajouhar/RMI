#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    int choice;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    printf("Choose operation:\n1. Factorial\n2. Power\nEnter choice: ");
    scanf("%d", &choice);
    send(sock, &choice, sizeof(choice), 0);
    
    if (choice == 1) {
        int num, result;
        printf("Enter a number: ");
        scanf("%d", &num);
        send(sock, &num, sizeof(num), 0);
        read(sock, &result, sizeof(result));
        printf("Factorial: %d\n", result);
    } else if (choice == 2) {
        double base, result;
        int exp;
        printf("Enter base and exponent: ");
        scanf("%lf %d", &base, &exp);
        send(sock, &base, sizeof(base), 0);
        send(sock, &exp, sizeof(exp), 0);
        read(sock, &result, sizeof(result));
        printf("Power: %lf\n", result);
    }
    
    close(sock);

    return 0;
}
