#include "AudioSource.h"

namespace WotStream::Sources {

	AudioSource::AudioSource() {
		_info = make_unique<obs_audio_info>();
	}
	AudioSource::~AudioSource() {}
	
	void AudioSource::Reset() { // used hardcode values

		auto a = _info.get();

		a->samples_per_sec = 44100;
		a->speakers = SPEAKERS_STEREO;

		if (!obs_reset_audio(a)) {
			throw "audio: reset failed";
		}
	}
}