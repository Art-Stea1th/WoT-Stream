#include "settings.h"

namespace wot_stream::extension::obs_management {

    Settings::Settings() { data = obs_data_create(); }
    Settings::~Settings() { obs_data_release(data); }

    Settings::operator obs_data*() const { return data; }

    Settings& Settings::SetString(const std::string &name, const std::string &value) {
        obs_data_set_string(data, name.c_str(), value.c_str());
        return *this;
    }

    Settings& Settings::SetBool(const std::string &name, bool value) {
        obs_data_set_bool(data, name.c_str(), value);
        return *this;
    }

    Settings& Settings::SetInt(const std::string &name, int value) {
        obs_data_set_int(data, name.c_str(), value);
        return *this;
    }

    Settings& Settings::SetDouble(const std::string &name, double value) {
        obs_data_set_double(data, name.c_str(), value);
        return *this;
    }


    Settings& Settings::SetDefaultString(const std::string & name, const std::string & value) {
        obs_data_set_default_string(data, name.c_str(), value.c_str());
        return *this;
    }

    Settings& Settings::SetDefaultBool(const std::string & name, bool value) {
        obs_data_set_default_bool(data, name.c_str(), value);
        return *this;
    }

    Settings& Settings::SetDefaultInt(const std::string & name, int value) {
        obs_data_set_default_int(data, name.c_str(), value);
        return *this;
    }

    Settings& Settings::SetDefaultDouble(const std::string & name, double value) {
        obs_data_set_default_double(data, name.c_str(), value);
        return *this;
    }
}