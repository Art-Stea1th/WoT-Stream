/*
    Outputs allow the ability to output the currently rendering audio/video.
    Streaming and recording are two common examples of outputs, but not the only types of outputs.
    Outputs can receive the raw data or receive encoded data.
*/
#pragma once
#include "../settings.h"
#include "../services/service.h"
#include "../encoders/encoder.h"

namespace wot_stream::extension::obs_management::outputs {

    class Output {
    public:
        ~Output();

        void SetVideoEncoder(const encoders::Encoder &encoder);
        void SetAudioEncoder(const encoders::Encoder &encoder);

        void SetService(const services::Service &service);

        void UpdateSettings(const Settings &settings);

        void Start();
        void Stop();

    protected:
        Output();

        enum class State { Started, Stopped };

        Settings settings;
        obs_output* output;
    };

    class StreamOutput : public Output {
    public:
        StreamOutput();
        ~StreamOutput();

    protected:
        void InitializeDefaults();
    };

    
}