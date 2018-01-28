#pragma once
#include "../shared.h"
#include "settings.h"
//#include "sources/wot_scene.h"
//#include "output.h"
//#include "encoder.h"
//#include "service.h"

namespace wot_stream::extension::obs_management {

    class Extension {
    public:
        Extension();
        ~Extension();

    private:

        void Initialize();

    };

    Extension::Extension() {
        Initialize();
    }

    Extension::~Extension() {

    }

    void Extension::Initialize() {

    }

    // ------------------------------------------


}