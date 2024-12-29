#include <iostream>
#include "httpServer.h"

int main() {
    try {
        std::cout << "Starting the HTTP server on port 8081..." << std::endl;

        // Start the HTTP server
        int result = CreateHTTPserver();

        if (result == 0) {
            std::cout << "HTTP server exited successfully." << std::endl;
        } else {
            std::cerr << "HTTP server encountered an error." << std::endl;
        }
        return result;
    } catch (const std::exception &ex) {
        std::cerr << "Exception caught: " << ex.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown exception occurred." << std::endl;
        return 1;
    }
}
