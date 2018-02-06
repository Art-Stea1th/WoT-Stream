/*
    Outputs allow the ability to output the currently rendering audio/video.
    Streaming and recording are two common examples of outputs, but not the only types of outputs.
    Outputs can receive the raw data or receive encoded data.
*/
#pragma once
#include "../settings.h"
#include "../services/service.h"
#include "../encoders/encoder.h"

namespace wot_stream::core::obs_management::outputs {

    enum class OutputState {
        Stopped, Busy, Started
    };

    class Output {
    public:
        ~Output();
        Output();

        void SetVideoEncoder(const encoders::Encoder &encoder);
        void SetAudioEncoder(const encoders::Encoder &encoder);
        void SetService(const services::Service &service);

        bool UpdateSettings(const Settings &settings);

        bool Start();
        bool Stop();

        OutputState GetState();
        void SetState(OutputState state); // !! warning: public, church for obs callbacks

    private:
        void InitializeDefaults();

        void SignalsConnect();
        void SignalsDisconnect();

        void SignalConnect(const std::string &signal, signal_callback_t callback);
        void SignalDisconnect(const std::string &signal, signal_callback_t callback);        

        Settings  settings;
        obs_output* output;
        
        std::atomic<OutputState> state = OutputState::Stopped;
    };

    static void OnOutputStarted(void *data, calldata_t *params);
    static void OnOutputStopped(void *data, calldata_t *params);
    static void OnOutputBusy(void *data, calldata_t *params);   
}