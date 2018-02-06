#include "wot_scene.h"


namespace wot_stream::core::obs_management::sources {

    using namespace std;

    WoTScene::WoTScene(int width, int height) {

        ResetAudio(SPEAKERS_STEREO, 44100);
        ResetVideo(width, height, 60);

        scene = obs_scene_create("scene");

        game_capture_source = std::make_unique<GameCaptureSource>();
        system_audio_source = std::make_unique<SystemAudioSource>();

        obs_set_output_source(0, *game_capture_source.get());
        obs_set_output_source(1, *system_audio_source.get());
    }

    WoTScene::~WoTScene() { obs_scene_release(scene); }

    WoTScene::operator obs_scene* () const { return scene; }

    void WoTScene::UpdateScreenSize(int width, int height) {
        ResetVideo(width, height, 60);
    }

    void WoTScene::ResetAudio(speaker_layout layout, int sps) {

        auto ai = std::make_shared<obs_audio_info>();

        ai->samples_per_sec = sps;
        ai->speakers = layout;

        if (!obs_reset_audio(ai.get())) {
            throw "audio: reset failed";
        }
    }

    void WoTScene::ResetVideo(int width, int height, int fps) {

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
}