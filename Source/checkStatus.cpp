#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include "../Headers/checkStatus.h"

int checkStatus(const char* ip, int port) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock....\n";
        return 0;
    }

    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET) {
        std::cerr << "Failed to create socket....\n";
        WSACleanup();
        return 0;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip);

    int result = connect(s, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    closesocket(s);

    WSACleanup();

    if (result == SOCKET_ERROR) {
        return 0;
    }

    return 1;
}



