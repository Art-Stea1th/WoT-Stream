#include "socket.h"

namespace wot_stream::core::sockets {

    Socket::Socket() {}

    Socket::Socket(SOCKET socket) {
        this->sock = socket;
    }

    Socket::~Socket() {
        closesocket(sock);
    }

    void Socket::Bind(const std::string &address, const std::string &port) {
        if (!wsa_started) {
            WSAStart();
        }
        if (wsa_started) {
            info = ResolveAddressInfo(address, port);
            CreateListenSocket();
            BindListeningSocket();
        }
    }

    void Socket::Listen(int max_connections) {
        if (listen(sock, max_connections) == SOCKET_ERROR) {
            OnError(sock);
        }
    }

    std::shared_ptr<Socket> Socket::Accept() {

        std::cout << "Wait for client connect" << std::endl;

        SOCKET accepted_socket = accept(sock, NULL, NULL);

        if (accepted_socket == INVALID_SOCKET) {
            OnError(sock);
            return nullptr;
        }

        std::cout << "Client accepted" << std::endl;
        return std::make_shared<Socket>(accepted_socket);
    }

    std::string Socket::Receive(int buffer_size) {

        std::string result = "";

        if (buffer_size > 0) {

            char* buffer = new char[buffer_size];

            int received = recv(sock, buffer, buffer_size, 0);
            if (received > 0) {
                result = std::string(buffer, received);
            }
            delete[] buffer;
        }
        return result;
    }

    void Socket::Send(const std::string &data) {

        int sent = send(sock, data.c_str(), data.length(), 0);
        if (sent == SOCKET_ERROR) {
            OnError(sock);
        }
    }

    // HARDCODE, fake resolve
    addrinfo* Socket::ResolveAddressInfo(const std::string &address, const std::string &port) {

        addrinfo hints;

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        addrinfo* info;

        if (getaddrinfo("127.0.0.1", port.c_str(), &hints, &info) == 0) {
            return info;
        }

        WSACleanup();
        return nullptr;
    }

    void Socket::CreateListenSocket() {
        sock = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
        if (sock == INVALID_SOCKET) {
            OnError(info);
        }
    }

    void Socket::BindListeningSocket() {
        if (bind(sock, info->ai_addr, (int)info->ai_addrlen) == SOCKET_ERROR) {
            OnError(info, sock);
        }
        freeaddrinfo(info);
    }

    void Socket::OnError(addrinfo* address_info) {
        freeaddrinfo(address_info);
        WSACleanup();
    }

    void Socket::OnError(SOCKET socket) {
        closesocket(socket);
        WSACleanup();
    }

    void Socket::OnError(addrinfo* address_info, SOCKET socket) {
        freeaddrinfo(address_info);
        closesocket(socket);
        WSACleanup();
    }

    void Socket::WSAStart() {
        if (WSAStartup(MAKEWORD(2, 2), &wsa_data) == 0) {
            wsa_started = true;
        }
    }

    WSAData Socket::wsa_data;
    bool Socket::wsa_started = false;
}