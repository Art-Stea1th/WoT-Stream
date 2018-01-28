#include "source.h"

namespace wot_stream::extension::obs_management::sources {

    // public

    Source::Source(SourceType type) {
        source = MakeBy(type);
    }

    Source::~Source() {
        obs_source_release(source);
        obs_data_release(settings);
    }

    SourceType Source::GetType() { return type; }
    std::string Source::GetName() { return name; }

    Source::operator obs_source*() const { return source; }

    // private

    /// PORNOGRAPHY
    obs_source* Source::MakeBy(SourceType type) {

        this->type = type;

        switch (type) {
        case SourceType::GameCapture:
            this->name = "World of Tanks";

            return obs_source_create(
                "game_capture", name.c_str(), settings = GetGameCapturePreset(), nullptr);

        case SourceType::SystemAudio:
            this->name = "Desktop Audio";

            return obs_source_create(
                "wasapi_output_capture", name.c_str(), settings = GetSystemAudioPreset(), nullptr);

        default:
            throw std::invalid_argument("SourceType::Unknown is not allowed");
        }
    }


    /// HARDCODE
    obs_data* Source::GetGameCapturePreset() {

        auto settings = obs_data_create();
        obs_data_set_string(settings, "capture_mode", "window");
        obs_data_set_string(settings, "window", "WoT Client:App:WorldOfTanks.exe");
        obs_data_set_int(settings, "priority", 2); // WINDOW_PRIORITY_EXE
        obs_data_set_bool(settings, "sli_compatibility", false);
        obs_data_set_bool(settings, "capture_cursor", true);
        obs_data_set_bool(settings, "allow_transparency", false);
        obs_data_set_bool(settings, "force_scaling", false);
        obs_data_set_bool(settings, "limit_framerate", false);
        obs_data_set_bool(settings, "capture_overlays", false);
        obs_data_set_bool(settings, "anti_cheat_hook", true);
        obs_data_set_string(settings, "scale_res", "1920x1080");

        obs_data_set_default_double(settings, "volume", 1.0);
        obs_data_set_default_int(settings, "mixers", 0xF);
        obs_data_set_default_int(settings, "flags", 0);
        obs_data_set_default_bool(settings, "enabled", true);

        return settings;
    }

    /// HARDCODE
    obs_data* Source::GetSystemAudioPreset() {

        auto settings = obs_data_create();
        obs_data_set_default_double(settings, "volume", 1.0);
        obs_data_set_default_int(settings, "mixers", 0xFF);
        obs_data_set_default_int(settings, "flags", 0);
        obs_data_set_default_bool(settings, "enabled", true);
        obs_data_set_default_bool(settings, "muted", false);

        return settings;
    }
}