#pragma once
#include "../shared.h"
#include "sources/wot_scene.h"
//#include "output.h"
//#include "encoder.h"
//#include "service.h"

namespace wot_stream::extension::obs_management {

    class OBSContext {
    public:
        OBSContext();
        ~OBSContext();

    private:

        void Initialize();

    };
}