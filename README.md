# Chat Application

This project is a simple client-server chat application implemented in C++ using Winsock2. It allows multiple clients to connect to a server and exchange messages in real time.

## Features

- **Multi-client support**: The server can handle multiple clients simultaneously.
- **Real-time communication**: Clients can send and receive messages instantly.
- **Simple commands**: Clients can type `quit` to exit the chat.

## Requirements

- Windows OS
- C++ compiler with support for C++11 or later
- Winsock2 library

## Setup Instructions

### 1. Clone the Repository

Clone this repository to your local machine:

```bash
https://github.com/your-username/chat-application.git
```

### 2. Compile the Code

You can use any IDE or build system that supports C++. Below are the steps for compiling and running the application using the command line:

#### Server

1. Navigate to the server file directory:

   ```bash
   cd server
   ```

2. Compile the server code:

   ```bash
   g++ -o ChatServer ChatServer.cpp -lws2_32
   ```

3. Run the server:

   ```bash
   ./ChatServer
   ```

#### Client

1. Navigate to the client file directory:

   ```bash
   cd client
   ```

2. Compile the client code:

   ```bash
   g++ -o ChatClient ChatClient.cpp -lws2_32
   ```

3. Run the client:

   ```bash
   ./ChatClient
   ```



