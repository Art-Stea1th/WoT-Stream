#pragma once
#include "shared.h"

namespace WotStream::Internal {

	class Video {
	public:

		Video();
		void Reset();

	private:

		unique_ptr<obs_video_info> _info;
	};
}