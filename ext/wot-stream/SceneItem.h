#pragma once
#include "shared.h"

namespace WotStream::Internal {

	class SceneItem {
	public:
		SceneItem();
		~SceneItem();

		void SetPos(float x, float y);

	private:

		obs_sceneitem_t* _instance;
	};
}