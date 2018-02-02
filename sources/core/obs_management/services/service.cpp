#include "service.h"

namespace wot_stream::core::obs_management::services {

    Service::Service() {}
    Service::~Service() { obs_service_release(service); }

    Service::operator obs_service*() const { return service; }

    void Service::ApplyEncoders(const encoders::Encoder &video_encoder, const encoders::Encoder &audio_encoder) {
        obs_service_apply_encoder_settings(service, video_encoder.GetSettings(), audio_encoder.GetSettings());
    }

    void Service::UpdateToken(const std::string &token) {
        settings
            .SetString("key", token.c_str());
        obs_service_update(service, settings);
    }

    void Service::UpdateSettings(const Settings &settings) {
        this->settings = settings;
        obs_service_update(service, this->settings);
    }

    const char* Service::GetOutputType() { return obs_service_get_output_type(service); }
    

    YouTubeService::YouTubeService() {
        InitializeDefaults();
        service = obs_service_create("rtmp_common", "default_service", settings, nullptr);
    }

    void YouTubeService::InitializeDefaults() {
        settings
            .SetString("server", "rtmp://a.rtmp.youtube.com/live2")
            .SetString("service", "YouTube / YouTube Gaming");
    }
    YouTubeService::~YouTubeService() {}
}