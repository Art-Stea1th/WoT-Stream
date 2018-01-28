/*
    Services are wrap implementations of streaming services, which are used with outputs that stream.
    For example, you could have a custom implementation for streaming to YouTube etc. to allow the ability
    to log in and use their APIs to do things such as get the RTMP servers or control the channel.
*/
#pragma once
#include "../settings.h"
#include "../encoders/encoder.h"

namespace wot_stream::extension::obs_management::services {

    class Service {
    public:
        virtual ~Service();
        operator obs_service* () const;

        void ApplyEncoders(const encoders::Encoder &video_encoder, const encoders::Encoder &audio_encoder);
        void UpdateToken(const std::string &token);
        void UpdateSettings(const Settings &settings);

        const char* GetOutputType();

    protected:
        Service();

        Settings settings;
        obs_service* service;
        char* output_type;
    };

    class YouTubeService : public Service {
    public:
        ~YouTubeService();
        YouTubeService();

    protected:
        void InitializeDefaults();
    };
}