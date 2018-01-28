/*
    Outputs allow the ability to output the currently rendering audio/video.
    Streaming and recording are two common examples of outputs, but not the only types of outputs.
    Outputs can receive the raw data or receive encoded data.
*/
#pragma once
#include "../../shared.h"
#include "../services/service.h"
#include "../encoders/encoder.h"


namespace wot_stream::extension::obs_management::outputs {

    class Output {
    public:
        Output();
        ~Output();

        void SetService(const services::Service &service);

        void SetVideoEncoder(const encoders::Encoder &encoder);
        void SetAudioEncoder(const encoders::Encoder &encoder);

        void Start();
        void Stop();

    private:

    };    
}