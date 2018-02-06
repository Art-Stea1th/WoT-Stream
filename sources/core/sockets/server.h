#pragma once
#include "../shared.h"
#include "../wot_stream.h"
#include "socket.h"

namespace wot_stream::core::sockets {

    class Server {
    public:
        Server();
        ~Server();

        void Start();

    private:
        void StartInteraction();

        std::string WSGetState();
        std::string WSInitialize();
        std::string WSUpdateToken(const std::string &token);

        std::string WSStartStream();
        std::string WSStopStream();

        std::unique_ptr<WoTStream> ws;

        std::unique_ptr<Socket> socket;
        std::shared_ptr<Socket> connection;
    };
}