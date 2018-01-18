#include "SceneItem.h"

namespace WotStream::Internal {

	SceneItem::SceneItem() {}
	SceneItem::~SceneItem() {}

	void SceneItem::SetPos(float x, float y) {
		vec2 pos{ x, y };
		obs_sceneitem_get_pos(_instance, &pos);
	}
}