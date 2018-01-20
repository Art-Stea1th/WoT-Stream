#include "Audio.h"

namespace wot_stream::internal {

    Audio::Audio() { info = std::make_unique<obs_audio_info>(); }

    void Audio::Reset() { // used hardcode values

        auto a = info.get();

        a->samples_per_sec = 44100;
        a->speakers = SPEAKERS_STEREO;

        if (!obs_reset_audio(a)) {
            throw "audio: reset failed";
        }

        // audio = std::make_shared<audio_t>(obs_get_audio());
    }
} // namespace wot_stream::internal