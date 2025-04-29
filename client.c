#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char message[1024];
    char buffer[1024];
    int bytes_sent, bytes_received;

    // Create the client socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Set up the server address struct
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Assuming server is on the same machine
    server_addr.sin_port = htons(PORT);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error connecting to server");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    // Communicate with the server
    while (1) {
        printf("Enter message to send to server (or 'disconnect' to quit): ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = 0;  // Remove newline character

        // Send message to the server
        bytes_sent = write(client_socket, message, strlen(message));
        if (bytes_sent < 0) {
            perror("Error sending message");
            break;
        }

        // Exit condition
        if (strcmp(message, "disconnect") == 0) {
            printf("Disconnecting from server.\n");
            break;
        }

        // Receive server's response
        bytes_received = read(client_socket, buffer, sizeof(buffer) - 1);
        if (bytes_received < 0) {
            perror("Error receiving message");
            break;
        }

        buffer[bytes_received] = '\0'; // Null-terminate the received message
        printf("Server response: %s\n", buffer);
    }

    close(client_socket);
    return 0;
}
