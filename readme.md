# TCP Echo Server and Client

This project implements a simple TCP server and client in C using sockets. The server can handle multiple clients concurrently using `fork` and responds to messages from clients based on specific logic.

## Features:
- The server responds with "world" when the client sends "hello".
- Any other message sent by the client is echoed back to the client.
- The server can handle multiple clients concurrently using `fork()`.
- The client can send messages and disconnect gracefully.

## How to Build:
1. Clone this repository or copy the source code.
2. Use `make` to build the server and client:
   ```bash
   make
   
Run the Server:
```bash
./server
```
Run the Client:
```
./client
```
![cpp_socket_tutorial](https://github.com/mKagiaogloy/tcp-client-server/blob/main/cpp_socket_tutorial.webp)
