#include "extension.h"

namespace wot_stream::core {

    using namespace obs_management;
    using namespace std;

    using WotScene = sources::WoTScene;
    using VideoEncoder = encoders::SimpleStreamVideo;
    using AudioEncoder = encoders::SimpleStreamAudio;
    using YouTubeService = services::YouTubeService;
    using StreamOutput = outputs::StreamOutput;

    Extension::Extension() {
        if (!obs_startup("en-US", nullptr, nullptr)) {
            throw "Extension startup failed";
        }
        ResetVideo();
        ResetAudio();
        this_thread::sleep_for(5s);
    }

    Extension::~Extension() {
        // StopStream();
        ClearAll();
        obs_shutdown();
    }

    void Extension::ResetVideo(int width, int height, int fps) {

        auto vi = std::make_shared<obs_video_info>();

        vi->fps_num = fps;
        vi->fps_den = 1;
        vi->graphics_module = "libobs-d3d11.dll";
        vi->base_width = width;
        vi->base_height = height;
        vi->output_width = vi->base_width;
        vi->output_height = vi->base_height;
        vi->output_format = VIDEO_FORMAT_NV12;
        vi->colorspace = VIDEO_CS_601;
        vi->range = VIDEO_RANGE_FULL;
        vi->adapter = 0;
        vi->gpu_conversion = true;
        vi->scale_type = OBS_SCALE_BICUBIC;

        auto code = obs_reset_video(vi.get());

        if (code != OBS_VIDEO_SUCCESS) {
            std::string message = "video: reset failed";
            throw (message += ", error code: " + code).c_str();
        }
    }

    void Extension::ResetAudio(speaker_layout layout, int sps) {

        auto ai = std::make_shared<obs_audio_info>();

        ai->samples_per_sec = sps;
        ai->speakers = layout;

        if (!obs_reset_audio(ai.get())) {
            throw "audio: reset failed";
        }
    }

    void Extension::Initialize() {

        if (initialized) {
            return;
        }

        modules_loader = std::make_unique<ModulesLoader>();
        modules_loader->LoadAuthorized();

        scene = std::make_unique<WotScene>();

        video_encoder = std::make_unique<VideoEncoder>();
        audio_encoder = std::make_unique<AudioEncoder>();

        service = std::make_unique<YouTubeService>();
        service->ApplyEncoders(*video_encoder, *audio_encoder);

        output = std::make_unique<StreamOutput>();
        output->SetVideoEncoder(*video_encoder);
        output->SetAudioEncoder(*audio_encoder);
        output->SetService(*service);

        this_thread::sleep_for(3s);
        initialized = true;
    }

    void Extension::ClearAll() { // important

        output = nullptr;
        service = nullptr;

        audio_encoder = nullptr;
        video_encoder = nullptr;

        scene = nullptr;

        modules_loader = nullptr;
    }

    void Extension::StartStream() {
        if (!initialized) {
            Initialize();
        }
        output->Start();
        this_thread::sleep_for(2s);
    }
    void Extension::StopStream() {
        if (output != nullptr) {
            output->Stop();
            this_thread::sleep_for(2s);
        }
    }

    void Extension::UpdateStreamToken(const std::string &token) {
        if (!initialized) {
            Initialize();
        }
        service->UpdateToken(token);
    }

    void Extension::UpdateScreen(int width, int height, int fps) {}

    bool Extension::GetStreamStarted() {
        return output != nullptr && output->Started();
    }
}