#pragma once
#include "shared.h"
#include "obs_management/modules_loader.h"
#include "obs_management/sources/wot_scene.h"
#include "obs_management/encoders/encoder.h"
#include "obs_management/services/service.h"
#include "obs_management/outputs/output.h"

namespace wot_stream::extension {

    class Extension {
    public:
        Extension();
        ~Extension();

        void UpdateStreamToken(const std::string &token);

        void StartStream();
        void StopStream();

        void UpdateScreen(int width, int height, int fps);

    private:
        void ResetVideo(int width = 1920, int height = 1080, int fps = 60);
        void ResetAudio(speaker_layout layout = SPEAKERS_STEREO, int sps = 44100);

        void Initialize();
        void ClearAll();

        std::unique_ptr<obs_management::ModulesLoader> modules_loader;

        std::unique_ptr<obs_management::sources::WoTScene> scene;
        std::unique_ptr<obs_management::encoders::Encoder> video_encoder;
        std::unique_ptr<obs_management::encoders::Encoder> audio_encoder;
        std::unique_ptr<obs_management::services::Service> service;
        std::unique_ptr<obs_management::outputs::Output> output;
    };
}