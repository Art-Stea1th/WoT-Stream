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