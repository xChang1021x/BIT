#include "pdu.h"
#include "utils.h"
#include "sender.cpp"
#include "receiver.cpp"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <config_file>" << std::endl;
        return 1;
    }

    // Read configuration
    Config config = readConfig(argv[1]);
    std::ofstream logFile("transfer.log", std::ios::app);
    if (!logFile) {
        std::cerr << "Cannot open log file" << std::endl;
        return 1;
    }

    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }

    // Create UDP socket
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return 1;
    }

    // Bind to local port
    sockaddr_in localAddr{};
    localAddr.sin_family = AF_INET;
    localAddr.sin_port = htons(config.localPort);
    localAddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sock, (sockaddr*)&localAddr, sizeof(localAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed" << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Set up remote address
    sockaddr_in remoteAddr{};
    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_port = htons(config.remotePort);
    inet_pton(AF_INET, config.remoteIP.c_str(), &remoteAddr.sin_addr);

    // Start sender and receiver threads
    std::thread senderThread(sender, sock, remoteAddr, config, std::ref(logFile));
    std::thread receiverThread(receiver, sock, remoteAddr, config, std::ref(logFile));

    senderThread.join();
    receiverThread.join();

    // Cleanup
    logFile.close();
    closesocket(sock);
    WSACleanup();
    return 0;
}