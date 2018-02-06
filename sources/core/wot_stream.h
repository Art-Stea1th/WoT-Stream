#pragma once
#include "shared.h"
#include "obs_management/modules_loader.h"
#include "obs_management/sources/wot_scene.h"
#include "obs_management/encoders/encoder.h"
#include "obs_management/services/service.h"
#include "obs_management/outputs/output.h"

namespace wot_stream::core {

    class WoTStream {
    public:
        WoTStream();
        ~WoTStream();

        void Initialize();

        void UpdateScreenSize(int width, int height);
        void UpdateStreamToken(const std::string &token);

        bool StartStream();
        bool StopStream();

        obs_management::outputs::OutputState GetStreamState();

    private:

        std::unique_ptr<obs_management::sources::WoTScene> scene;
        std::unique_ptr<obs_management::encoders::Encoder> video_encoder;
        std::unique_ptr<obs_management::encoders::Encoder> audio_encoder;
        std::unique_ptr<obs_management::services::Service> service;
        std::unique_ptr<obs_management::outputs::Output> output;

        bool initialized = false;
    };
}