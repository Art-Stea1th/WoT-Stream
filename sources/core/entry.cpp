#include "sockets/socket.h"
#include "extension.h"

using namespace wot_stream::core;
using namespace wot_stream::core::sockets;

void ConfigureView();
VOID WINAPI SetConsoleColors(WORD attributes);

void StartInteraction(std::shared_ptr<Socket> connection);

int main() {

    ConfigureView();

    Socket socket {};
    socket.Bind("127.0.0.1", "48684");
    socket.Listen(1);

    while (true) {
        std::cout << "----------------------------" << std::endl;
        auto connection = socket.Accept();
        StartInteraction(connection);
    }
    std::cin.get();
}

void ConfigureView() {
    SetConsoleTitle("WoT Stream: Remote");
    SetConsoleColors(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
}

VOID WINAPI SetConsoleColors(WORD attributes) {

    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFOEX cbi;
    cbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    GetConsoleScreenBufferInfoEx(hOutput, &cbi);
    cbi.wAttributes = attributes;
    SetConsoleScreenBufferInfoEx(hOutput, &cbi);
}

void StartInteraction(std::shared_ptr<Socket> connection) {

    Extension extension {};
    bool started = true;
    bool wait_for_token = false;

    while (started) {

        if (wait_for_token) {

            auto token = connection->Receive(20);
            if (token.empty()) {
                continue;
            }

            extension.UpdateStreamToken(token);
            extension.StartStream();

            wait_for_token = false;

            std::cout << "- Rt: " << token << std::endl;

            connection->Send("0");
        }

        auto request = connection->Receive(1);
        if (request.empty()) {
            request = "4";
        }

        auto ch_rq = request[0];
        std::string response = "255";

        switch (ch_rq) { // need protocol where collection <char, func()>
        case '0':
            std::cout << "- Rq: Initialize" << std::endl;
            extension.Initialize();
            response = "0";
            break;
        case '1':
            std::cout << "- Rq: Stream Started?" << std::endl;
            response = extension.GetStreamStarted() ? "1" : "0";
            break;
        case '2':
            std::cout << "- Rq: Start Stream" << std::endl;
            wait_for_token = true;
            response = "1";
            break;
        case '3':
            std::cout << "- Rq: Stop Stream" << std::endl;
            extension.StopStream();
            response = "0";
            break;
        case '4':
            std::cout << "- Rq: Shutdown" << std::endl;
            started = false;
            response = "0";
            break;
        }
        connection->Send(response);
    }
    std::cout << "The interaction was complete" << std::endl;
}