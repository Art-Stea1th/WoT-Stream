#include "server.h"

#define WSOK  "ok"
#define WSBAD "bp"
#define WSERR "er"

namespace wot_stream::core::sockets {

    using namespace std;
    using namespace wot_stream::core::obs_management::outputs;

    Server::Server() {
        socket = std::make_unique<Socket>();
        socket->Bind("127.0.0.1", "48684");
        socket->Listen(1);
    }

    Server::~Server() {}

    void Server::Start() {
        while (true) {
            connection = socket->Accept();
            StartInteraction();
        }
    }

    void Server::StartInteraction() {

        while (true) {

            auto request = connection->Receive(4);

            if (request == "stat") {
                connection->Send(WSGetState());
            }
            else if (request == "srts") {
                connection->Send(WSStartStream());
            }
            else if (request == "stps") {
                connection->Send(WSStopStream());
            }
            else if (request == "updt") {
                connection->Receive(2);
                request = connection->Receive(19);
                connection->Send(WSUpdateToken(request));
            }
            else if (request == "init") {
                connection->Send(WSInitialize());
            }
            else {
                connection->Send("unauthorized request");
                break;
            }
        }
    }

    std::string Server::WSGetState() {
        if (ws) {
            switch (ws->GetStreamState()) {
                case OutputState::Stopped: return "stpd";
                case OutputState::Busy:    return "busy";
                case OutputState::Started: return "srtd";
            }
        }
        return "ntin";
    }

    std::string Server::WSInitialize() {
        cout << "  rq: Initialize" << endl;
        if (ws) {
            ws->~WoTStream();
            ws.release();
        }
        ws = std::make_unique<WoTStream>();
        return WSOK;
    }

    std::string Server::WSUpdateToken(const std::string &token) {
        cout << "  rq: Update Token" << endl;
        if (ws && ws->GetStreamState() == OutputState::Stopped) {
            ws->UpdateStreamToken(token);
            return WSOK;
        }
        return WSBAD;
    }

    std::string Server::WSStartStream() {
        cout << "  rq: Start Stream" << endl;
        if (ws && ws->StartStream()) {
            int ticks = 0;
            while (ws->GetStreamState() != OutputState::Started && ticks++ < 500) { // 5s
                this_thread::sleep_for(10ms);
            }
            if (ws->GetStreamState() == OutputState::Started) {
                return WSOK;
            }
            return WSERR;
        }
        return WSBAD;
    }

    std::string Server::WSStopStream() {
        cout << "  rq: Stop Stream" << endl;
        if (ws && ws->StopStream()) {
            while (ws->GetStreamState() != OutputState::Stopped) {
                this_thread::sleep_for(10ms);
            }
            return WSOK;
        }
        return WSBAD;
    }
}