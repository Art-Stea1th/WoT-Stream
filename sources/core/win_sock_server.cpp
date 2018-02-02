#include "win_sock_server.h"

namespace wot_stream::core {

    WinSockServer::WinSockServer() {}

    WinSockServer::~WinSockServer() {}

    void WinSockServer::Initialize() {
        ZeroMemory(&addr_info_hints, sizeof(addr_info_hints));
        addr_info_hints.ai_family = AF_INET;
        addr_info_hints.ai_socktype = SOCK_STREAM;
        addr_info_hints.ai_protocol = IPPROTO_TCP;
        addr_info_hints.ai_flags = AI_PASSIVE;
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

        int iResult = getaddrinfo(NULL, DEFAULT_PORT, &addr_info_hints, &addr_info_result);
        if (iResult == 0) {
            PrintSuccess("getaddrinfo");
        }
        else {
            PrintError("getaddrinfo", iResult);
            WSACleanup();
        }
    }

    void WinSockServer::PrintError(const std::string &operation_name, int error_code) {
        std::cerr << operation_name << " failed with error: " << error_code << std::endl;
    }

    void WinSockServer::PrintSuccess(const std::string &operation_name) {
        std::cout << operation_name << " was successful!" << std::endl;
    }
}