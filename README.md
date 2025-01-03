


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

### 3. Configuration

Update the `ChatCommon.h` file to configure server IP, port, and buffer size:

```cpp
const std::string SERVER_IP = "127.0.0.1"; // Server IP address
const int PORT = 54000;                     // Port number
const int BUFFER_SIZE = 4096;               // Message buffer size
```

## How to Use

1. Start the server by running the `ChatServer` executable.
2. Start one or more clients by running the `ChatClient` executable.
3. Type messages in the client terminal to send messages to the server.
4. Type `quit` in the client terminal to disconnect from the server.

## File Structure

```
chat-application/
├── server/
│   ├── ChatServer.cpp  # Server-side implementation
│   └── ChatCommon.h    # Shared configuration header
├── client/
│   ├── ChatClient.cpp  # Client-side implementation
│   └── ChatCommon.h    # Shared configuration header
└── README.md           # Documentation
```

## Known Issues

- The application is designed for local testing and may require additional configuration for use over a network.
- Error handling can be improved for robustness.
