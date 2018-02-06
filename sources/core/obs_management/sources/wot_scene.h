#pragma once
#include "../../shared.h"
#include "source.h"

namespace wot_stream::core::obs_management::sources {

    class WoTScene {
    public:
        WoTScene(int width = 1920, int height = 1080);
        ~WoTScene();

        operator obs_scene*() const;

        void UpdateScreenSize(int width, int height);

    private:
        void ResetAudio(speaker_layout layout, int sps);
        void ResetVideo(int width, int height, int fps);

        obs_scene* scene;

        std::unique_ptr<Source> game_capture_source;
        std::unique_ptr<Source> system_audio_source;    
    };
}