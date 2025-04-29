#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

void handle_client(int client_socket) {
    char buffer[1024];
    int bytes_read;

    while (1) {
        // Read message from client
        memset(buffer, 0, sizeof(buffer));
        bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
        if (bytes_read <= 0) {
            printf("Client disconnected or error occurred.\n");
            break;
        }

        printf("Message from client: %s\n", buffer);

        // Respond based on the message
        if (strcmp(buffer, "hello") == 0) {
            write(client_socket, "world", 5);
        } else if (strcmp(buffer, "disconnect") == 0) {
            printf("Disconnecting client.\n");
            break;
        } else {
            write(client_socket, buffer, bytes_read);
        }
    }

    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Create the server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Set up the server address struct
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the address
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding socket");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        perror("Error listening");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    // Accept and handle clients
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("Error accepting client connection");
            continue;
        }

        printf("Client connected from %s\n", inet_ntoa(client_addr.sin_addr));

        // Fork to handle each client in a new process
        if (fork() == 0) {
            close(server_socket); // Child process does not need the server socket
            handle_client(client_socket);
            exit(0);
        } else {
            close(client_socket); // Parent process does not need the client socket
        }
    }

    close(server_socket);
    return 0;
}
