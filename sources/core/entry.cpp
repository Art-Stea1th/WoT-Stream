#include "shared.h"
#include "sockets/server.h"

using namespace std;
using namespace wot_stream::core::sockets;

void ConfigureView();
VOID WINAPI SetConsoleColors(WORD attributes);

int main() {

    ConfigureView();

    Server server {};
    server.Start();
}

void ConfigureView() {
    SetConsoleTitle("WoT Stream: Remote v0.0.3");
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