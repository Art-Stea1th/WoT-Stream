#include "Scene.h"


namespace WotStream::Internal {

	Scene::Scene(const string & name) {
		_scene = obs_scene_create(name.c_str());
	}

	Scene::~Scene() {
		obs_scene_release(_scene);
	}
}