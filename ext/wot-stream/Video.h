#pragma once
#include "shared.h"

namespace wot_stream::internal {

    class Video {
    public:
        Video();
        void Reset();

    private:
        std::unique_ptr<obs_video_info> info;
        std::shared_ptr<video_t> video;
    };
} // namespace wot_stream::internal