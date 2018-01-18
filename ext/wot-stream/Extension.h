#pragma once
#include "shared.h"

namespace WotStream {	

	using namespace Internal;

	class Extension {
	public:

		Extension();
		~Extension();

		void Load();

		shared_ptr<Scene> MakeScene(const string &name);
		shared_ptr<Source> MakeSource(const string &id, const string &name);
		shared_ptr<SceneItem> MakeSceneItem();

		void AddScene(shared_ptr<Scene> &scene, shared_ptr<Source> &source);

		void SetOutputScene(shared_ptr<Scene> scene);
	
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