#pragma once
#include "../../shared.h"
#include "source.h"

namespace wot_stream::core::obs_management::sources {

    class WoTScene {
    private:

    public:
        WoTScene();
        ~WoTScene();

        operator obs_scene*() const;

    private:
        obs_scene* scene;

        std::unique_ptr<Source> game_capture_source;
        std::unique_ptr<Source> system_audio_source;    
    };
}