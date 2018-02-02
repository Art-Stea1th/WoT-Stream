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

namespace wot_stream::core {


    class WinSockServer {
    public:
        WinSockServer();
        ~WinSockServer();

        void Initialize();
        void Startup();

        void ResolveAddressInfo();

    private:

        void PrintError(const std::string &operation_name, int error_code);
        void PrintSuccess(const std::string &operation_name);

        addrinfo addr_info_hints;
        addrinfo* addr_info_result;

    };
}