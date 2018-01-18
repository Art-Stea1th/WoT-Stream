#pragma once
#include <stl-deps.h>
#include <internal-shared.h>

namespace WotStream {

	using namespace Sources;

	class Extension {
	public:

		Extension();
		~Extension();

		void Startup();

		void ResetAudio();
		void ResetVideo();

		void LoadAllModules();

		// ----------

		/*void SetOutputSource();

		void SetOutputScene();
		void GetOutputScene();

		void GetOutputSource();


		void Render();

		void GetSourceTypeDisplayName();

		void GetSourceInputTypes();
		void GetSourceFilterTypes();
		void GetSourceTransitionTypes();

		void GetBaseEffect();

		void GetVersion();*/
	
	private:

		unique_ptr<AudioSource> _audio;
		unique_ptr<VideoSource> _video;

		void Initialize();
		void AddScene();

		void Shutdown();
	};
}