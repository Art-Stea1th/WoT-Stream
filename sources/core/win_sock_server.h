#pragma once
#include "shared.h"

#undef UNICODE
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "48684"

namespace wot_stream::core { // tmp. single message impl.


    class WinSockServer {
    public:
        WinSockServer();
        ~WinSockServer();

        void Initialize();
        void Startup();

        void ResolveAddressInfo();

        void CreateListenSocket();
        void BindListeningSocket();
        void StartListen();

        void AcceptClientSocket();

        void StartReceive();

        void Shutdown();

    private:

        void PrintError(const std::string &operation_name, int error_code);
        void PrintSuccess(const std::string &operation_name);

        addrinfo ai_hints;
        addrinfo* ai_result;

        SOCKET listen_socket = INVALID_SOCKET;
        SOCKET client_socket = INVALID_SOCKET;

        char recvbuf[DEFAULT_BUFLEN];
        int recvbuflen = DEFAULT_BUFLEN;

    };
}