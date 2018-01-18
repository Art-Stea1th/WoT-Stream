#include "VideoSource.h"

namespace WotStream::Sources {

	VideoSource::VideoSource() {
		_info = make_unique<obs_video_info>();
	}
	VideoSource::~VideoSource() {}
	
	void VideoSource::Reset() { // used hardcode values

		auto v = _info.get();

		v->fps_num = 60;
		v->fps_den = 1;
		v->graphics_module = "libobs-d3d11.dll";
		v->base_width = 1920;
		v->base_height = 1080;
		v->output_width = v->base_width;
		v->output_height = v->base_height;
		v->output_format = VIDEO_FORMAT_NV12;
		v->colorspace = VIDEO_CS_601;
		v->range = VIDEO_RANGE_FULL;
		v->adapter = 0;
		v->gpu_conversion = true;
		v->scale_type = OBS_SCALE_BICUBIC;

		auto code = obs_reset_video(v);

		if (code != OBS_VIDEO_SUCCESS) {
			string message = "video: reset failed";
			throw message += ", error code: " + code;
		}
	}
}