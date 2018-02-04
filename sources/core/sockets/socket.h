#pragma once
#include "../shared.h"

#undef UNICODE
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")

namespace wot_stream::core::sockets {

    class Socket {
    public:
        Socket();
        Socket(SOCKET socket);
        ~Socket();

        void Bind(const std::string &address, const std::string &port);
        void Listen(int max_connections);

        std::shared_ptr<Socket> Accept();

        std::string Receive(int buffer_size);
        void Send(const std::string &data);

    private:
        addrinfo* ResolveAddressInfo(const std::string &address, const std::string &port);
        void CreateListenSocket();
        void BindListeningSocket();

        void OnError(addrinfo* address_info);
        void OnError(SOCKET socket);
        void OnError(addrinfo* address_info, SOCKET socket);

        addrinfo* info;
        SOCKET    sock = INVALID_SOCKET;

    private:
        static void WSAStart();
        static WSAData wsa_data;
        static bool wsa_started;
    };
}