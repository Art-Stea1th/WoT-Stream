#pragma once
#include "../shared.h"

namespace wot_stream::extension::obs_management {

    class ModulesLoader {
    public:
        ModulesLoader();
        ~ModulesLoader();

        void LoadAuthorized();

    private:

        const std::string default_bin_path;
        const std::string default_data_path;

        std::vector<std::string> authorized_module_names;

        void AddPath(const std::string &bin = nullptr, const std::string &data = nullptr);
        void LoadModule(const std::string &bin_path, const std::string &data_path);
        void PostLoad();

    };

}