#include "wot_stream.h"

namespace wot_stream::core {

    using namespace obs_management;
    using namespace std;

    using WoTScene = sources::WoTScene;
    using VideoEncoder = encoders::SimpleStreamVideo;
    using AudioEncoder = encoders::SimpleStreamAudio;
    using YouTubeService = services::YouTubeService;
    using StreamOutput = outputs::Output;
    using OutputState = outputs::OutputState;

    WoTStream::WoTStream() {
        if (!obs_startup("en-US", nullptr, nullptr)) {
            throw "OBS startup failed";
        }
        Initialize();
    }

    WoTStream::~WoTStream() {

        while (output && output->GetState() != OutputState::Stopped) {
            output->Stop();
            std::this_thread::sleep_for(200ms);
        }
        output.release();
        service.release();
        audio_encoder.release();
        video_encoder.release();
        scene.release();
        obs_shutdown();
    }

    void WoTStream::Initialize() {

        if (initialized) { return; }

        auto modules_loader = std::make_unique<ModulesLoader>();
        modules_loader->LoadAuthorized();

        scene = std::make_unique<WoTScene>();

        video_encoder = std::make_unique<VideoEncoder>();
        audio_encoder = std::make_unique<AudioEncoder>();

        service = std::make_unique<YouTubeService>();
        service->ApplyEncoders(*video_encoder, *audio_encoder);

        output = std::make_unique<StreamOutput>();
        output->SetVideoEncoder(*video_encoder);
        output->SetAudioEncoder(*audio_encoder);
        output->SetService(*service);

        initialized = true;
    }

    void WoTStream::UpdateScreenSize(int width, int height) { scene->UpdateScreenSize(width, height); }
    void WoTStream::UpdateStreamToken(const std::string &token) { service->UpdateToken(token); }

    bool WoTStream::StartStream() { return output->Start(); }
    bool WoTStream::StopStream() { return output->Stop(); }

    OutputState WoTStream::GetStreamState() { return output->GetState(); }
}