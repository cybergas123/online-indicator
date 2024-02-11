#include <iostream>
#include <cstring> 
#include <cstdlib>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

bool isOnline() {
    const char* server = "8.8.8.8";  //dns google public server
    const int port = 53;              // port

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return false;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    inet_pton(AF_INET, server, &(serverAddress.sin_addr));

    if (connect(sock, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        std::cerr << "Offline" << std::endl;
        close(sock);
        return false;
    }

    std::cout << "Online" << std::endl;
    close(sock);
    return true;
}

int main() {
    isOnline();

    return 0;
}
