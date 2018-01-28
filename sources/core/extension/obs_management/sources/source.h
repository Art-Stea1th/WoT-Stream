/*
    Sources are used to render video and/or audio on stream.
    Things such as capturing displays/games/audio, playing a video,
    showing an image, or playing audio.
*/
#pragma once
#include "../settings.h"

namespace wot_stream::extension::obs_management::sources {

    class Source {
    public:
        virtual ~Source();
        operator obs_source*() const;

        void UpdateSettings(const Settings &settings);

    protected:
        Source();

        Settings settings;
        obs_source* source;
    };

    class GameCaptureSource : public Source {
    public:
        GameCaptureSource();
        ~GameCaptureSource();

    protected:
        void InitializeDefaults();
    };


    class SystemAudioSource : public Source {
    public:
        SystemAudioSource();
        ~SystemAudioSource();

    protected:
        void InitializeDefaults();
    };
    
}