#include "encoder.h"
#include "encoder.h"

namespace wot_stream::extension::obs_management::encoders {

    Encoder::~Encoder() {
        obs_encoder_release(encoder);
        obs_data_release(settings);
    }

    Encoder::Encoder() {
        settings = obs_data_create();
    }

    SimpleStreamAudio::SimpleStreamAudio() {
        obs_data_set_string(settings, "rate_control", "CBR");
        obs_data_set_int(settings, "bitrate", 2500);
        encoder = obs_audio_encoder_create("mf_aac", "simple_aac", settings, 0, nullptr);
        obs_encoder_set_audio(encoder, obs_get_audio());
    }

    SimpleStreamVideo::SimpleStreamVideo() {
        obs_data_set_string(settings, "rate_control", "CBR");
        obs_data_set_int(settings, "bitrate", 2500);
        encoder = obs_video_encoder_create("obs_x264", "simple_h264_stream", settings, nullptr);
        obs_encoder_set_video(encoder, obs_get_video());
    }
}