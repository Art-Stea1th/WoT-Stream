/*
    Services are wrap implementations of streaming services, which are used with outputs that stream.
    For example, you could have a custom implementation for streaming to YouTube etc. to allow the ability
    to log in and use their APIs to do things such as get the RTMP servers or control the channel.
*/
#pragma once
#include "../../shared.h"

namespace wot_stream::extension::obs_management::services {

    enum class Destination { YouTube, Twitch, Facebook };

    class Service {
    public:
        Service(Destination destination, const std::string &token);
        ~Service();

    private:

        void Initialize(Destination destination, const std::string &token);

    };

    
}