#include "obs_management/modules_loader.h"

using namespace wot_stream::extension::obs_management;
using namespace std;

void Check();
void Startup();
void ResetAudio();
void ResetVideo();

int main() {

    Check();
    cin.get();

    Check();
    cin.get();
}

void Check() { // TODO: 'll wrap in the object oriented model after clarifying
               // all of the requirements

    // + init audio, video, created default scene & game source, configured

    Startup();
    ResetAudio();
    ResetVideo();

    ModulesLoader modules_loader {};
    modules_loader.LoadAuthorized();

    cout << string(64, '=') << endl;

    auto scene = obs_scene_create("scene");
    // ? find a function sets the process id for a source
    auto source = obs_source_create("game_capture", "World of Tanks", nullptr, nullptr);

    auto scene_item = obs_scene_add(scene, source);
    obs_sceneitem_addref(scene_item);

    vec2 pos { 0, 0 }, scale { 1, 1 }, bounds { 1920, 1080 };

    obs_sceneitem_set_pos(scene_item, &pos);
    obs_sceneitem_set_scale(scene_item, &scale);

    obs_sceneitem_set_bounds(scene_item, &bounds);
    obs_sceneitem_set_bounds_type(scene_item, OBS_BOUNDS_SCALE_INNER);
    obs_sceneitem_set_bounds_alignment(scene_item, 0); // center

                                                       // - init encoder
    auto video_encoder = obs_video_encoder_create("obs_x264", "simple_h264_stream", nullptr, nullptr); // ? clarify
    auto audio_encoder = obs_audio_encoder_create("mf_aac", "simple_aac", nullptr, 0, nullptr);        // ? clarify

                                                                                                       // - create & configure service
    auto service = obs_output_create("rtpm_common", "default_service", nullptr, nullptr); // failed, need settings

    obs_set_output_source(0, source);

    // - start graphics & audio threads

    // - start stream

    cout << string(64, '=') << endl;

    cin.get();

    // - release memory

    obs_output_release(service);

    obs_encoder_release(audio_encoder);
    obs_encoder_release(video_encoder);

    obs_sceneitem_release(scene_item);
    obs_source_release(source);
    obs_scene_release(scene);

    obs_shutdown();
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