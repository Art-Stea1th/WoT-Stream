#pragma once
#include "../shared.h"
#include "source.h"
#include "output.h"
#include "encoder.h"
#include "service.h"

namespace wot_stream::extension::obs_management {

    class OBSContext {
    public:
        OBSContext(OBSContext const&) = delete;
        void operator=(OBSContext const&) = delete;
        ~OBSContext();

        static OBSContext& GetInstance();


    private:
        OBSContext();

        std::unique_ptr<Source> source;
        std::unique_ptr<Output> output;

        std::vector<Encoder> encoders;
        std::vector<Service> services;
    };
}