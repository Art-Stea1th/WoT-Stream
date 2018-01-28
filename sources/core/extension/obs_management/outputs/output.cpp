#include "output.h"

namespace wot_stream::extension::obs_management::outputs {

    Output::Output() {}
    Output::~Output() { obs_output_release(output); }

    void Output::SetVideoEncoder(const encoders::Encoder &encoder) {
        obs_output_set_video_encoder(output, encoder);
    }

    void Output::SetAudioEncoder(const encoders::Encoder &encoder) {
        obs_output_set_audio_encoder(output, encoder, 0);
    }

    void Output::SetService(const services::Service &service) {
        obs_output_set_service(output, service);
    }

    void Output::UpdateSettings(const Settings &settings) {
        this->settings = settings;
        obs_output_update(output, this->settings);
    }

    void Output::Start() {
        if (state != State::Started) {
            obs_output_start(output);    // !!! internal async. call, I need a notification on a state changed
        }
        state = State::Started;
    }

    void Output::Stop() {
        if (state != State::Stopped) {
            obs_output_stop(output);     // !!! internal async. call, I need a notification on a state changed
        }
        state = State::Stopped;
    }

    bool Output::Started() { return state == State::Started; }


    StreamOutput::StreamOutput() {
        InitializeDefaults();
        output = obs_output_create("rtmp_output", "simple_stream", settings, nullptr);
        obs_output_set_delay(output, 0, OBS_OUTPUT_DELAY_PRESERVE);
        obs_output_set_reconnect_settings(output, 20, 10);
    }
    StreamOutput::~StreamOutput() {}

    void StreamOutput::InitializeDefaults() {
        settings
            .SetString("bind_ip", "default")
            .SetBool("new_socket_loop_enabled", false)
            .SetBool("low_latency_mode_enabled", false);
    }
}