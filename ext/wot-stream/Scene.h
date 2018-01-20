#pragma once
#include "shared.h"

namespace wot_stream::internal {

    class Scene {
    public:
        Scene(const std::string &name);
        ~Scene();

    private:
        obs_scene * scene;
    };
} // namespace wot_stream::internal