#pragma once
#include "shared.h"

namespace WotStream::Internal {

	class Scene {
	public:

		Scene(const string & name);
		~Scene();

		obs_scene* GetRaw(); // tmp

	private:

		obs_scene* _scene;
	};
}