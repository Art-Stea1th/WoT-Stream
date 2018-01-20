#pragma once
#include "shared.h"

namespace wot_stream::internal {

    class Audio {
    public:
        Audio();
        void Reset();

    private:
        std::unique_ptr<obs_audio_info> info;
        std::shared_ptr<audio_t> audio;
    };
} // namespace wot_stream::internal