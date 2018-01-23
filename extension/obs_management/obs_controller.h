#pragma once
#include "../shared.h"
#include "source.h"
#include "output.h"
#include "encoder.h"
#include "service.h"

namespace wot_stream::extension::obs_management {

    class ObsController {
    public:
        ObsController(ObsController const&) = delete;
        void operator=(ObsController const&) = delete;
        ~ObsController();

        static ObsController& GetInstance();


    private:
        ObsController();

        std::unique_ptr<Source> source;
        std::unique_ptr<Output> output;

        std::vector<Encoder> encoders;
        std::vector<Service> services;
    };
}