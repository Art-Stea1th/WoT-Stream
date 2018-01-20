#include "SceneItem.h"

namespace wot_stream::internal {

    SceneItem::SceneItem() {}
    SceneItem::~SceneItem() {}

    void SceneItem::SetPos(float x, float y) {
        vec2 pos{ x, y };
        obs_sceneitem_get_pos(sceneitem, &pos);
    }
} // namespace wot_stream::internal