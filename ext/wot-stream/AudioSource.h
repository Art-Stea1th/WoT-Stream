#pragma once
#include <stl-deps.h>
#include <obs-deps.h>

namespace WotStream::Sources {

	using namespace std;

	class AudioSource {
	public:

		AudioSource();
		~AudioSource();

		void Reset();

	private:

		unique_ptr<obs_audio_info> _info;
	};
}