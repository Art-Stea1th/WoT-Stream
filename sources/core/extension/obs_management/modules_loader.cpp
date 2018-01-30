#include "modules_loader.h"

namespace wot_stream::extension::obs_management {

    using string = std::string;

    ModulesLoader::ModulesLoader()
        : default_bin_path("../../obs-plugins/32bit/"),          // 'll be changed
        default_data_path("../../data/obs-plugins/%module%/") {  // 'll be changed

        authorized_module_names = {
            "win-wasapi", "win-mf", "win-dshow", "win-capture", //"win-decklink",
            "rtmp-services",
            "obs-x264", "obs-qsv11", "obs-outputs", //"obs-ffmpeg",
                                                    //"image-source",                                                    
                                                    //"coreaudio-encoder"
        };
    }

    ModulesLoader::~ModulesLoader() {}

    void ModulesLoader::LoadAuthorized() {

        // obs_load_all_modules(); // tmp. for valid inject to game process, del. "frontend-tools.dll" before start

        for (auto &module_name : authorized_module_names) {
            auto bin_path = /*default_bin_path +*/ module_name + ".dll";
            auto data_path = default_data_path + module_name;
            LoadModule(bin_path, data_path);
        }
        PostLoad();
    }

    void ModulesLoader::AddPath(const string &bin, const string &data) {
        obs_add_module_path(bin.c_str(), data.c_str());
    }

    void ModulesLoader::LoadModule(const string &bin_path, const string &data_path) {

        obs_module* module;

        int code = obs_open_module(&module, bin_path.c_str(), data_path.c_str());
        if (code != MODULE_SUCCESS) {
            blog(LOG_DEBUG, "Failed to load module file '%s': %d", bin_path.c_str(), code);
            return;
        }
        obs_init_module(module);
    }

    void ModulesLoader::PostLoad() {
        obs_log_loaded_modules();
        obs_post_load_modules();
    }

}