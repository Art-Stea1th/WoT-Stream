/*
    Services are wrap implementations of streaming services, which are used with outputs that stream.
    For example, you could have a custom implementation for streaming to YouTube etc. to allow the ability
    to log in and use their APIs to do things such as get the RTMP servers or control the channel.
*/

namespace wot_stream::extension::obs_management {

    class Service {
    public:
        Service();
        ~Service();

    private:

    };

    Service::Service() {}

    Service::~Service() {}
}