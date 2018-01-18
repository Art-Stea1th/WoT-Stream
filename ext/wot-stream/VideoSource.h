#pragma once
#include <stl-deps.h>
#include <obs-deps.h>

namespace WotStream::Sources {

	using namespace std;

	class VideoSource {
	public:

		VideoSource();
		~VideoSource();

		void Reset();

	private:

		unique_ptr<obs_video_info> _info;
	};
}