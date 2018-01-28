/*
    Sources are used to render video and/or audio on stream.
    Things such as capturing displays/games/audio, playing a video,
    showing an image, or playing audio.
*/
#pragma once
#include "../../shared.h"

namespace wot_stream::extension::obs_management::sources {

    enum class SourceType { Unknown, GameCapture, SystemAudio };

    class Source {
    public:
        Source(SourceType type);
        virtual ~Source();

        SourceType GetType();
        std::string GetName();

        operator obs_source*() const;

    private:

        obs_source* MakeBy(SourceType type);

        obs_data* GetGameCapturePreset();
        obs_data* GetSystemAudioPreset();

        SourceType type = SourceType::Unknown;
        std::string name = "";

        obs_data* settings;
        obs_source* source;
    };
}