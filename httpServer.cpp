#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "MyTrigFunction.h"

#define PORT 8081

const char HTTP_200HEADER[] = "HTTP/1.1 200 OK\r\n";

int CreateHTTPserver() {
    int connectionSocket, clientSocket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket
    if ((connectionSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(connectionSocket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(connectionSocket);
        return -1;
    }

    if (listen(connectionSocket, 10) < 0) {
        perror("Listen failed");
        close(connectionSocket);
        return -1;
    }

    std::cout << "Server started on port " << PORT << ". Waiting for connections..." << std::endl;

    while (true) {
        if ((clientSocket = accept(connectionSocket, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }

        // Read HTTP request
        char buffer[30000] = {0};
        int bytesRead = read(clientSocket, buffer, sizeof(buffer));

        if (bytesRead <= 0) {
            std::cerr << "Failed to read request or client disconnected." << std::endl;
            close(clientSocket);
            continue;
        }

        // Parse request
        std::string request(buffer);
        std::string method = request.substr(0, request.find(' '));
        std::string path = request.substr(request.find(' ') + 1, request.find(' ', request.find(' ') + 1) - request.find(' ') - 1);

        std::cout << "Method: " << method << ", Path: " << path << std::endl;

        // Handle `/compute` endpoint
        if (method == "GET" && path == "/compute") {
            auto start = std::chrono::high_resolution_clock::now();

            // Perform computation
            std::vector<double> values;
            MyTrigFunction trigFunc;
            int n = 200000000; // Adjust n to make the computation last ~20 seconds
            for (int i = 0; i < n; ++i) {
                values.push_back(trigFunc.FuncA(i % 10));
            }

            std::sort(values.begin(), values.end());

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

            // Send response
            std::string body = std::to_string(duration);
            std::string response = std::string(HTTP_200HEADER) +
                                    "Content-Type: text/plain\r\n" +
                                    "Content-Length: " + std::to_string(body.size()) + "\r\n\r\n" +
                                    body;

            send(clientSocket, response.c_str(), response.size(), 0);
            std::cout << "Response sent: " << body << " seconds" << std::endl;
        } else {
            // Handle other paths or methods
            const char *notFoundResponse = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
            send(clientSocket, notFoundResponse, strlen(notFoundResponse), 0);
            std::cout << "Response sent: 404 Not Found" << std::endl;
        }

        close(clientSocket);
    }

    close(connectionSocket);
    return 0;
}
