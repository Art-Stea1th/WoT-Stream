#pragma once
#include "shared.h"

namespace wot_stream::internal {

    class SceneItem {
    public:
        SceneItem();
        ~SceneItem();

        void SetPos(float x, float y);

    private:
        obs_sceneitem_t* sceneitem;
    };
} // namespace wot_stream::internal