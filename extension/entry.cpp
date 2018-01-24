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

    /*Check();
    cin.get();*/
}

void Check() {


    // --------------------------------------------------------------------------------------------
    // TODO: 'll wrap in the object oriented model after clarifying all of the requirements
    // TODO: IMPORTANT! to use a wrappers from "obs.hpp" for simplify the interaction with it
    // --------------------------------------------------------------------------------------------



    // + init audio, video, created default scene & game source, configured -----------------------

    Startup();
    ResetAudio();
    ResetVideo();

    ModulesLoader modules_loader {};
    modules_loader.LoadAuthorized();

    // --------------------------------------------------------------------------------------------

    cout << string(64, '=') << endl;

    // --- source ---------------------------------------------------------------------------------

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


    auto video_encoder = obs_video_encoder_create("obs_x264", "simple_h264_stream", nullptr, nullptr);
    auto audio_encoder = obs_audio_encoder_create("mf_aac", "simple_aac", nullptr, 0, nullptr);

    // obs_set_output_source(0, source);

    // - start graphics & audio threads

    // - start stream


    // --- service --------------------------------------------------------------------------------

    auto service = obs_service_create("rtmp_common", "default_service", nullptr, nullptr); // need settings

    auto h264_settings = obs_data_create();
    auto aac_settings = obs_data_create();

    obs_data_set_string(h264_settings, "rate_control", "CBR");
    obs_data_set_int(h264_settings, "bitrate", 2500);

    obs_data_set_string(aac_settings, "rate_control", "CBR");
    obs_data_set_int(aac_settings, "bitrate", 160);

    obs_service_apply_encoder_settings(service, h264_settings, aac_settings);

    auto video = obs_get_video();
    auto video_format = video_output_get_format(video);

    obs_encoder_update(video_encoder, h264_settings);
    obs_encoder_update(audio_encoder, aac_settings);

    auto output_type = obs_service_get_output_type(service);
    auto url = obs_service_get_url(service);


    // --- stream output --------------------------------------------------------------------------

    auto stream_output = obs_output_create(output_type, "simple_stream", nullptr, nullptr); // type - rtmp_output
    obs_output_addref(stream_output); // ?

    // --- SIGNALS --- for obs-signal from wrappers ("obs.hpp")
    // streamDelayStarting.Connect(obs_output_get_signal_handler(streamOutput), "starting", OBSStreamStarting, this);
    // streamStopping.Connect(obs_output_get_signal_handler(streamOutput), "stopping", OBSStreamStopping, this);
    // startStreaming.Connect(obs_output_get_signal_handler(streamOutput), "start", OBSStartStreaming, this);
    // stopStreaming.Connect(obs_output_get_signal_handler(streamOutput), "stop", OBSStopStreaming, this);

    auto supported_audio_codec = obs_output_get_supported_audio_codecs(stream_output);

    obs_output_set_video_encoder(stream_output, video_encoder);
    obs_output_set_audio_encoder(stream_output, audio_encoder, 0);
    obs_output_set_service(stream_output, service);

    auto stream_output_settings = obs_data_create();

    auto reconnect = true;
    auto retryDelay = 10;
    auto maxRetries = 20;
    auto useDelay = false;
    auto delaySec = 20;
    auto preserveDelay = true;
    auto bindIP = "default";
    auto enableNewSocketLoop = false;
    auto enableLowLatencyMode = false;

    obs_data_set_string(stream_output_settings, "bind_ip", bindIP);
    obs_data_set_bool(stream_output_settings, "new_socket_loop_enabled", enableNewSocketLoop);
    obs_data_set_bool(stream_output_settings, "low_latency_mode_enabled", enableLowLatencyMode);

    obs_output_update(stream_output, stream_output_settings);


    if (!reconnect)
        maxRetries = 0;

    obs_output_set_delay(stream_output, useDelay ? delaySec : 0, preserveDelay ? OBS_OUTPUT_DELAY_PRESERVE : 0);
    obs_output_set_reconnect_settings(stream_output, maxRetries, retryDelay);

    // --- stream_output --------------------------------------------------------------------------

    obs_output_start(stream_output);

    // --------------------------------------------------------------------------------------------
    cout << string(64, '=') << endl;
    cin.get();

    // --- release memory -------------------------------------------------------------------------

    obs_output_release(stream_output);

    obs_data_release(stream_output_settings);

    obs_data_release(aac_settings);
    obs_data_release(h264_settings);

    obs_service_release(service);

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