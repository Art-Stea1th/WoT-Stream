#include "Scene.h"

namespace wot_stream::internal {

    Scene::Scene(const std::string &name) {
        scene = obs_scene_create(name.c_str());
    }

    Scene::~Scene() { obs_scene_release(scene); }

} // namespace wot_stream::internal