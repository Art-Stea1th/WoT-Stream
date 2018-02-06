#include "output.h"

namespace wot_stream::core::obs_management::outputs {

    Output::Output() {
        InitializeDefaults();
        output = obs_output_create("rtmp_output", "simple_stream", settings, nullptr);
        obs_output_set_delay(output, 0, OBS_OUTPUT_DELAY_PRESERVE);
        obs_output_set_reconnect_settings(output, 20, 10);
        SignalsConnect();
    }

    Output::~Output() {
        SignalsDisconnect();
        obs_output_release(output);
    }

    void Output::InitializeDefaults() {
        settings
            .SetString("bind_ip", "default")
            .SetBool("new_socket_loop_enabled", false)
            .SetBool("low_latency_mode_enabled", false);
    }

    void Output::SignalsConnect() {
        SignalConnect("starting", OnOutputBusy);
        SignalConnect("start", OnOutputStarted);
        SignalConnect("stopping", OnOutputBusy);
        SignalConnect("stop", OnOutputStopped);
    }

    void Output::SignalsDisconnect() {
        SignalDisconnect("starting", OnOutputBusy);
        SignalDisconnect("start", OnOutputStarted);
        SignalDisconnect("stopping", OnOutputBusy);
        SignalDisconnect("stop", OnOutputStopped);
    }

    void Output::SignalConnect(const std::string &signal, signal_callback_t callback) {
        auto handler = obs_output_get_signal_handler(output);
        signal_handler_connect(handler, signal.c_str(), callback, this);
    }

    void Output::SignalDisconnect(const std::string &signal, signal_callback_t callback) {
        auto handler = obs_output_get_signal_handler(output);
        signal_handler_disconnect(handler, signal.c_str(), callback, this);
    }

    void Output::SetVideoEncoder(const encoders::Encoder &encoder) {
        obs_output_set_video_encoder(output, encoder);
    }

    void Output::SetAudioEncoder(const encoders::Encoder &encoder) {
        obs_output_set_audio_encoder(output, encoder, 0);
    }

    void Output::SetService(const services::Service &service) {
        obs_output_set_service(output, service);
    }

    bool Output::UpdateSettings(const Settings &settings) {
        if (state == OutputState::Stopped) {
            this->settings = settings;
            obs_output_update(output, this->settings);
            return true;
        }
        return false;
    }

    bool Output::Start() {
        if (state == OutputState::Stopped) {            
            obs_output_start(output);
            return true;
        }
        return false;
    }

    bool Output::Stop() {
        if (state == OutputState::Started) {
            obs_output_stop(output);            
            return true;
        }
        return false;
    }

    OutputState Output::GetState() { return state; }

    void Output::SetState(OutputState state) { this->state = state; }
    

    void OnOutputStarted(void *data, calldata_t *params) {
        Output *output = static_cast<Output*>(data);
        output->SetState(OutputState::Started);
    }

    void OnOutputStopped(void *data, calldata_t *params) {
        Output *output = static_cast<Output*>(data);
        output->SetState(OutputState::Stopped);
    }

    void OnOutputBusy(void *data, calldata_t *params) {
        Output *output = static_cast<Output*>(data);
        output->SetState(OutputState::Busy);
    }
}