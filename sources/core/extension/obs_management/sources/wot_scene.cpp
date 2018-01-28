#include "wot_scene.h"


namespace wot_stream::extension::obs_management::sources {

    WoTScene::WoTScene() {

        scene = obs_scene_create("scene");

        game_capture_source = std::make_unique<Source>(SourceType::GameCapture);
        system_audio_source = std::make_unique<Source>(SourceType::SystemAudio);
        
        obs_set_output_source(0, *game_capture_source.get());
        obs_set_output_source(1, *system_audio_source.get());
    }

    WoTScene::~WoTScene() {
        
        system_audio_source.release();
        game_capture_source.release();

        obs_scene_release(scene);
    }

    WoTScene::operator obs_scene* () const {
        return scene;
    }
}