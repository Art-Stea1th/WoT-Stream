#include "Extension.h"
#include "Audio.h"
#include "Scene.h"
#include "SceneItem.h"
#include "Source.h"
#include "Video.h"

namespace wot_stream {

    Extension::Extension() {
        audio = std::make_unique<Audio>();
        video = std::make_unique<Video>();
        Load();
    }

    Extension::~Extension() { obs_shutdown(); }

    void Extension::Load() {
        Startup();
        ResetAudio();
        ResetVideo();
        LoadAllModules();
    }

    void Extension::Startup() {
        if (!obs_startup("en-US", nullptr, nullptr)) {
            throw "OBS startup failed";
        }
    }

    void Extension::ResetAudio() { audio->Reset(); }

    void Extension::ResetVideo() { video->Reset(); }

    void Extension::LoadAllModules() {
        obs_load_all_modules();
        obs_log_loaded_modules();
        obs_post_load_modules();
    }
} // namespace wot_stream