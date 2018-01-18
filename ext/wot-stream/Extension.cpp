#include "Extension.h"


namespace WotStream {

	Extension::Extension() {
		Initialize();
	}

	Extension::~Extension() {
		Shutdown();
	}

	void Extension::Initialize() {
		_audio = make_unique<AudioSource>();
		_video = make_unique<VideoSource>();
	}

	void Extension::AddScene() {}

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

	void Extension::Shutdown() {
		obs_shutdown();
	}
}