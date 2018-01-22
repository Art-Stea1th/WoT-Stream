#pragma once

// stl

#include <iostream>
#include <memory>
#include <vector>
#include <string>

// obs

#include "../dependencies/obs_rep/libobs/obs.hpp"

// defs

typedef unsigned int uint;

namespace wot_stream::extension::encoders {
    class IEncoder;
} // namespace wot_stream::extension::encoders

namespace wot_stream::extension::input {
    class IInput;
} // namespace wot_stream::extension::input

namespace wot_stream::extension::output {
    class IOutput;
} // namespace wot_stream::extension::output

namespace wot_stream::extension::services {
    class IService;
} // namespace wot_stream::extension::output

namespace wot_stream::extension::utilities {
    class ModulesLoader;
} // namespace wot_stream::extension::utilities