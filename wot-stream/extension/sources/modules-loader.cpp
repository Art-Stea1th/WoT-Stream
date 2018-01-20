#include "modules-loader.h"

namespace wot_stream::internal {

    ModulesLoader::ModulesLoader()
        : default_bin_path("../../obs-plugins/32bit/"),          // 'll be changed
        default_data_path("../../data/obs-plugins/%module%/") {  // 'll be changed

        authorized_module_names = {
            "win-wasapi", "win-mf", "win-dshow", "win-capture", // "win-decklink",
            "rtmp-services",
            "obs-x264", "obs-qsv11", "obs-outputs", // "obs-ffmpeg",
            // "image-source",
            // "coreaudio-encoder"
        };
    }

    ModulesLoader::~ModulesLoader() {}

    void ModulesLoader::LoadAuthorized() {
        for (auto &module_name : authorized_module_names) {
            auto bin_path = default_bin_path + module_name + ".dll";
            auto data_path = default_data_path + module_name;
            LoadModule(bin_path, data_path);
        }
    }

    void ModulesLoader::LoadModule(const std::string &bin_path, const std::string &data_path) {

        obs_module* module;

        int code = obs_open_module(&module, bin_path.c_str(), data_path.c_str());
        if (code != MODULE_SUCCESS) {
            blog(LOG_DEBUG, "Failed to load module file '%s': %d", bin_path.c_str(), code);
            return;
        }
        obs_init_module(module);
    }

    void ModulesLoader::AddPath(const std::string &bin, const std::string &data) {
        obs_add_module_path(bin.c_str(), data.c_str());
    }
}