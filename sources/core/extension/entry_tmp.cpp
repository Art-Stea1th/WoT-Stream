#include "obs_management/modules_loader.h"
#include "obs_management/sources/wot_scene.h"
#include "obs_management/encoders/encoder.h"
#include "obs_management/services/service.h"
#include "obs_management/outputs/output.h"

using namespace std;
using namespace wot_stream::extension::obs_management;
using namespace wot_stream::extension::obs_management::sources;
using namespace wot_stream::extension::obs_management::encoders;
using namespace wot_stream::extension::obs_management::services;
using namespace wot_stream::extension::obs_management::outputs;

void Check();
void Startup();
void ResetAudio();
void ResetVideo();

int main() {
    Check();
    obs_shutdown();
    cin.get();
}

void Check() {

    Startup();
    ResetAudio();
    ResetVideo();

    ModulesLoader modules_loader {};
    modules_loader.LoadAuthorized();

    WoTScene scene {};

    SimpleStreamVideo video_encoder {};
    SimpleStreamAudio audio_encoder {};

    YouTubeService service {};
    service.UpdateToken("17a7-4xcp-wqhe-7d7d");
    service.ApplyEncoders(video_encoder, audio_encoder);

    StreamOutput output {};
    output.SetAudioEncoder(audio_encoder);
    output.SetVideoEncoder(video_encoder);
    output.SetService(service);    

    output.Start();

    cin.get();

    output.Stop();
}

void Startup() {
    if (!obs_startup("en-US", nullptr, nullptr)) {
        throw "OBS startup failed";
    }
}

void ResetAudio() {

    auto ai = make_shared<obs_audio_info>();

    ai->samples_per_sec = 44100;
    ai->speakers = SPEAKERS_STEREO;

    if (!obs_reset_audio(ai.get())) {
        throw "audio: reset failed";
    }
}

void ResetVideo() {

    auto vi = make_shared<obs_video_info>();

    vi->fps_num = 60;
    vi->fps_den = 1;
    vi->graphics_module = "libobs-d3d11.dll";
    vi->base_width = 1920;
    vi->base_height = 1080;
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
        throw message += ", error code: " + code;
    }
}