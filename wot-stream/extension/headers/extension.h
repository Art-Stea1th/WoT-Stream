#pragma once
#include "shared.h"

namespace wot_stream {

    using namespace internal;

    class Extension {
    public:
        Extension();
        ~Extension();

        void Load();

    private:
        std::unique_ptr<Audio> audio;
        std::unique_ptr<Video> video;

        std::unique_ptr<Scene> scene;

        void Startup();

        void ResetAudio();
        void ResetVideo();

        void LoadAllModules();
    };
} // namespace wot_stream