#include "Audio.h"
#include "Video.h"
#include "Source.h"
#include "SceneItem.h"
#include "Scene.h"
#include "Extension.h"

namespace WotStream {

	Extension::Extension() {
		_audio = make_unique<Audio>();
		_video = make_unique<Video>();
		Load();
	}

	Extension::~Extension() {
		obs_shutdown();
	}

	void Extension::Load() {
		Startup();
		ResetAudio();
		ResetVideo();
		LoadAllModules();
	}
	
	shared_ptr<Scene> Extension::MakeScene(const string &name) {
		return make_shared<Scene>(name);
	}

	shared_ptr<Source> Extension::MakeSource(const string &id, const string &name) {
		return make_shared<Source>(id, name);
	}



	/*void Extension::AddScene(shared_ptr<Scene> &scene) {
		SceneItem = obs_scene_add(scene->Raw(), source->Raw());
	}*/

	void Extension::SetOutputScene(shared_ptr<Scene> scene) {

		/*auto source = scene->GetSource();
		obs_set_output_source(0, scene.get());*/
	}

	void Extension::Startup() {
		if (!obs_startup("en-US", nullptr, nullptr)) {
			throw "OBS startup failed";
		}
	}
	
	void Extension::ResetAudio() {
		_audio->Reset();
	}

	void Extension::ResetVideo() {
		_video->Reset();
	}

	void Extension::LoadAllModules() {
		obs_load_all_modules();
	}
}