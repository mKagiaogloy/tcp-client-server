# TCP Echo Server and Client

This project implements a simple TCP server and client in C using sockets. The server can handle multiple clients concurrently using `fork` and responds to messages from clients based on specific logic.

## Features:
- The server responds with "world" when the client sends "hello".
- Any other message sent by the client is echoed back to the client.
- The server can handle multiple clients concurrently using `fork`.
- The client can send messages and disconnect gracefully.

## How to Build:
1. Clone this repository or copy the source code.
2. Use `make` to build the server and client:
   ```bash
   make


Run the server : ./server
Run the client : ./client


Summary of every file !

1. Server Program (server.c):
Created a TCP server that listens on port 8080.
Handles multiple clients concurrently using fork().
Responds with "world" if the client sends "hello", echoes any other message, and disconnects when the client sends "disconnect".

2. Client Program (client.c):
Connects to the server on port 8080.
Allows the user to send messages to the server and receive responses.
Disconnects when the user sends the message "disconnect".

3. Makefile:
A Makefile that builds both the server and client programs.

4. README.md:
Provides instructions for building, running, and using the server and client.

What's Next:
Testing: Run the server and client to ensure they work as expected. You can run the server on one terminal window and the client on another.
Improvements: If needed, we can later add more advanced features like error handling, logging, or implementing threads using pthread for better performance.