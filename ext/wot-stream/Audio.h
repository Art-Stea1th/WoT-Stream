#pragma once
#include "shared.h"

namespace WotStream::Internal {

	class Audio {
	public:

		Audio();
		void Reset();

	private:

		unique_ptr<obs_audio_info> _info;
	};
}