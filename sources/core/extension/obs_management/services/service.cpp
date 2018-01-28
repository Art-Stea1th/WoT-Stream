#include "service.h"


namespace wot_stream::extension::obs_management::services {

    Service::Service(Destination destination, const std::string &token) {
        Initialize(destination, token);
    }

    Service::~Service() {

    }

    void Service::Initialize(Destination destination, const std::string &token) {

    }
}