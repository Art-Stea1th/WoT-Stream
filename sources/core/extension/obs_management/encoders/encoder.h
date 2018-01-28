/*
    Encoders are specific implementations of video/audio encoders,
    which are used with outputs that use encoders.
    x264, NVENC, Quicksync are examples of encoder implementations.
*/
#pragma once
#include "../../shared.h"

namespace wot_stream::extension::obs_management::encoders {

    class Encoder {
    public:
        virtual ~Encoder();

    protected:
        Encoder();

        obs_data* settings;
        obs_encoder* encoder;
    };

    class SimpleStreamAudio : Encoder {
    public:
        SimpleStreamAudio();
        ~SimpleStreamAudio();
    };    

    class SimpleStreamVideo : Encoder {
    public:
        SimpleStreamVideo();
        ~SimpleStreamVideo();
    };

}