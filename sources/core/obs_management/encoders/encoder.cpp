#include "encoder.h"

namespace wot_stream::core::obs_management::encoders {

    Encoder::Encoder() {}
    Encoder::~Encoder() { obs_encoder_release(encoder); }

    Encoder::operator obs_encoder* () const { return encoder; }

    obs_data* Encoder::GetSettings() const { return settings; }

    void Encoder::UpdateSettings(const Settings &settings) {
        this->settings = settings;
        obs_encoder_update(encoder, this->settings);
    }


    SimpleStreamVideo::SimpleStreamVideo() {
        InitializeDefaults();
        encoder = obs_video_encoder_create("obs_x264", "simple_h264_stream", settings, nullptr);
        obs_encoder_set_video(encoder, obs_get_video());
    }
    SimpleStreamVideo::~SimpleStreamVideo() {}

    void SimpleStreamVideo::InitializeDefaults() {
        settings
            .SetString("rate_control", "CBR")
            .SetInt("bitrate", 2500);
    }


    SimpleStreamAudio::SimpleStreamAudio() {
        InitializeDefaults();
        encoder = obs_audio_encoder_create("mf_aac", "simple_aac", settings, 0, nullptr);
        obs_encoder_set_audio(encoder, obs_get_audio());
    }
    SimpleStreamAudio::~SimpleStreamAudio() {}

    void SimpleStreamAudio::InitializeDefaults() {
        settings
            .SetString("rate_control", "CBR")
            .SetInt("bitrate", 160);
    }
}