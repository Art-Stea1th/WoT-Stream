#pragma once
#include "../shared.h"

namespace wot_stream::core::obs_management {

    class Settings {
    public:
        ~Settings();
        Settings();

        operator obs_data*() const;

        Settings& SetString(const std::string &name, const std::string &value);
        Settings& SetBool(const std::string &name, bool value);
        Settings& SetInt(const std::string &name, int value);
        Settings& SetDouble(const std::string &name, double value);

        Settings& SetDefaultString(const std::string &name, const std::string &value);
        Settings& SetDefaultBool(const std::string &name, bool value);
        Settings& SetDefaultInt(const std::string &name, int value);
        Settings& SetDefaultDouble(const std::string &name, double value);

    private:
        obs_data* data;
    };
}