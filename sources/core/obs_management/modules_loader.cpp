#include "modules_loader.h"

namespace wot_stream::core::obs_management {

    using string = std::string;

    ModulesLoader::ModulesLoader() {

        authorized_module_names = {
            "win-wasapi", "win-mf", "win-capture",
            "rtmp-services",
            "obs-outputs", "obs-x264",
        };
    }

    ModulesLoader::~ModulesLoader() {}

    void ModulesLoader::LoadAuthorized() {

        for (auto &module_name : authorized_module_names) {
            LoadModule(module_name + ".dll", "./");
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