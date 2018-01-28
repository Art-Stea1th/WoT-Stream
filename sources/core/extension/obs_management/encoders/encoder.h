/*
    Encoders are specific implementations of video/audio encoders,
    which are used with outputs that use encoders.
    x264, NVENC, Quicksync are examples of encoder implementations.
*/
#pragma once
#include "../settings.h"

namespace wot_stream::extension::obs_management::encoders {

    class Encoder {
    public:
        virtual ~Encoder();
        operator obs_encoder* () const;

        obs_data* GetSettings() const;
        void UpdateSettings(const Settings &settings);

    protected:
        Encoder();

        Settings settings;
        obs_encoder* encoder;
    };

    class SimpleStreamVideo : public Encoder {
    public:
        SimpleStreamVideo();
        ~SimpleStreamVideo();

    protected:
        void InitializeDefaults();
    };

    class SimpleStreamAudio : public Encoder {
    public:
        SimpleStreamAudio();
        ~SimpleStreamAudio();

    protected:
        void InitializeDefaults();
    };
}