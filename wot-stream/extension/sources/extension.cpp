#include "extension.h"
#include "modules-loader.h"
#include "audio.h"
#include "scene.h"
#include "scene-item.h"
#include "source.h"
#include "video.h"

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
        LoadModules();
    }

    void Extension::Startup() {
        if (!obs_startup("en-US", nullptr, nullptr)) {
            throw "OBS startup failed";
        }
    }

    void Extension::ResetAudio() { audio->Reset(); }

    void Extension::ResetVideo() { video->Reset(); }

    void Extension::LoadModules() {

        ModulesLoader loader {};
        loader.LoadAuthorized();

        //obs_load_all_modules();
        obs_log_loaded_modules();
        obs_post_load_modules();
    }
} // namespace wot_stream