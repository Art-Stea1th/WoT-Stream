#include "win_sock_server.h"

namespace wot_stream::core {  // tmp. single message impl.

    WinSockServer::WinSockServer() {}

    WinSockServer::~WinSockServer() {
        freeaddrinfo(ai_result);
    }

    void WinSockServer::Initialize() {
        ZeroMemory(&ai_hints, sizeof(ai_hints));
        ai_hints.ai_family = AF_INET;
        ai_hints.ai_socktype = SOCK_STREAM;
        ai_hints.ai_protocol = IPPROTO_TCP;
        ai_hints.ai_flags = AI_PASSIVE;
    }

    void WinSockServer::Startup() {

        WSADATA wsaData;

        int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult == 0) {
            PrintSuccess("WSAStartup");
        }
        else {
            PrintError("WSAStartup", iResult);
        }
    }

    void WinSockServer::ResolveAddressInfo() {

        int iResult = getaddrinfo(NULL, DEFAULT_PORT, &ai_hints, &ai_result);
        if (iResult == 0) {
            PrintSuccess("getaddrinfo");
        }
        else {
            PrintError("getaddrinfo", iResult);
            WSACleanup();
        }
    }

    void WinSockServer::CreateListenSocket() {

        listen_socket = socket(ai_result->ai_family, ai_result->ai_socktype, ai_result->ai_protocol);
        if (listen_socket == INVALID_SOCKET) {
            PrintError("socket", WSAGetLastError());
            freeaddrinfo(ai_result);
            WSACleanup();
        }
        else {
            PrintSuccess("socket");
        }
    }

    void WinSockServer::BindListeningSocket() {

        int iResult = bind(listen_socket, ai_result->ai_addr, (int)ai_result->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            PrintError("bind", WSAGetLastError());
            freeaddrinfo(ai_result);
            closesocket(listen_socket);
            WSACleanup();
        }
        else {
            PrintSuccess("bind");
        }
    }

    void WinSockServer::StartListen() {

        int iResult = listen(listen_socket, SOMAXCONN);
        if (iResult == SOCKET_ERROR) {
            PrintError("listen", WSAGetLastError());
            closesocket(listen_socket);
            WSACleanup();
        }
        else {
            PrintSuccess("listen");
        }
    }

    void WinSockServer::AcceptClientSocket() {

        client_socket = accept(listen_socket, NULL, NULL);
        if (client_socket == INVALID_SOCKET) {
            PrintError("accept", WSAGetLastError());
            closesocket(listen_socket);
            WSACleanup();
        }
        else {
            PrintSuccess("accept");
        }
    }

    void WinSockServer::StartReceive() {

        closesocket(listen_socket); // !!!

        int iResult = 0;

        do {
            iResult = recv(client_socket, recvbuf, recvbuflen, 0);
            if (iResult > 0) {

                std::cout << "Bytes received: " << iResult << std::endl;

                // Echo the buffer back to the sender
                int iSendResult = send(client_socket, recvbuf, iResult, 0);
                if (iSendResult == SOCKET_ERROR) {

                    PrintError("send", WSAGetLastError());
                    closesocket(client_socket);
                    WSACleanup();
                }
                std::cout << "Bytes sent: " << iSendResult << std::endl;
            }
            else if (iResult == 0)
                std::cout << "Connection closing..." << std::endl;
            else {
                PrintError("recv", WSAGetLastError());
                closesocket(client_socket);
                WSACleanup();
            }
        } while (iResult > 0);
    }

    void WinSockServer::Shutdown() {
        int iResult = shutdown(client_socket, SD_SEND);
        if (iResult == SOCKET_ERROR) {
            PrintError("shutdown", WSAGetLastError());
        }
        else {
            PrintSuccess("shutdown");
        }
        closesocket(client_socket);
        WSACleanup();
    }

    void WinSockServer::PrintError(const std::string &operation_name, int error_code) {
        std::cerr << operation_name << ": failed with error: " << error_code << std::endl;
    }

    void WinSockServer::PrintSuccess(const std::string &operation_name) {
        std::cout << operation_name << ": was successful!" << std::endl;
    }
}