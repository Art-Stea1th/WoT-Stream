#include <iostream>
// #include "api.h"
#include "win_sock_server.h"

using namespace wot_stream::core;

int main() {

    WinSockServer server {};

    server.Initialize();
    server.Startup();
    server.ResolveAddressInfo();
    server.CreateListenSocket();
    server.BindListeningSocket();
    server.StartListen();
    server.AcceptClientSocket();
    server.StartListen();
    server.StartReceive();
    server.Shutdown();

    std::cin.get();

    /*initialize();

    std::cin.get();

    start_stream();

    std::cin.get();

    stop_stream();

    std::cin.get();

    shutdown();*/

}