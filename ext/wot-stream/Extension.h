#pragma once
#include "shared.h"

namespace WotStream {	

	using namespace Internal;

	class Extension {
	public:

		Extension();
		~Extension();

		void Load();
	
	private:

		unique_ptr<Audio> _audio;
		unique_ptr<Video> _video;

		unique_ptr<Scene> _scene;

		void Startup();

		void ResetAudio();
		void ResetVideo();

		void LoadAllModules();		
	};
}