#include "source.h"

namespace wot_stream::core::obs_management::sources {

    Source::Source() {}
    Source::~Source() { obs_source_release(source); }

    Source::operator obs_source*() const { return source; }

    void Source::UpdateSettings(const Settings &settings) {
        this->settings = settings;
        obs_source_update(source, this->settings);
    }


    GameCaptureSource::GameCaptureSource() {
        InitializeDefaults();
        source = obs_source_create("game_capture", "World of Tanks", settings, nullptr);
    }
    GameCaptureSource::~GameCaptureSource() {}

    void GameCaptureSource::InitializeDefaults() {
        settings
            .SetString("capture_mode", "window")
            .SetString("window", "WoT Client:App:WorldOfTanks.exe")
            .SetInt("priority", 2)
            .SetBool("sli_compatibility", false)
            .SetBool("capture_cursor", true)
            .SetBool("allow_transparency", false)
            .SetBool("force_scaling", false)
            .SetBool("limit_framerate", false)
            .SetBool("capture_overlays", false)
            .SetBool("anti_cheat_hook", true)
            .SetString("scale_res", "1920x1080");
        settings
            .SetDefaultDouble("volume", 1.0)
            .SetDefaultInt("mixers", 0xF)
            .SetDefaultInt("flags", 0)
            .SetDefaultBool("enabled", true);
    }


    SystemAudioSource::SystemAudioSource() {
        InitializeDefaults();
        source = obs_source_create("wasapi_output_capture", "Desktop Audio", settings, nullptr);
    }
    SystemAudioSource::~SystemAudioSource() {}

    void SystemAudioSource::InitializeDefaults() {
        settings
            .SetDefaultDouble("volume", 1.0)
            .SetDefaultInt("mixers", 0xFF)
            .SetDefaultInt("flags", 0)
            .SetDefaultBool("enabled", true)
            .SetDefaultBool("muted", false);
    }
}