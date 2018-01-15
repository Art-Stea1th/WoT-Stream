#include <iostream>
#include <obs.hpp>
#include <audio-io.h>

using namespace std;

static const int width = 1920;
static const int height = 1080;

void Start();
void Initialize();
void ClearSceneData();
bool ResetVideo();
bool ResetAudio();
void CreateScene();
void CreateService();

int main() {
	Start();
	cin.get();
}

void Start() {
	Initialize();
	cout << endl << "Init success!";
	cin.get();
}


void Initialize() {

	if (!obs_startup("en-US", nullptr, nullptr)) {
		throw;
	}

	if (!ResetVideo()) {
		throw;
	}

	if (!ResetAudio()) {
		throw;
	}

	obs_load_all_modules();
	CreateScene();
	CreateService();
}

void CreateScene() {

	ClearSceneData();

	//auto scene = obs_scene_create("Scene");
	//auto source = obs_scene_get_source(scene);

	struct obs_source* source = obs_source_create("game_capture", "World of Tanks", nullptr, nullptr);

	const char *name = obs_source_get_name(source);
	obs_scene_t *scene = obs_scene_from_source(source);


	obs_set_output_source(0, source);

	auto addSceneItem = [/*this*/](obs_sceneitem_t *item) {

		obs_scene_t  *scene = obs_sceneitem_get_scene(item);
		obs_source_t *sceneSource = obs_scene_get_source(scene);
		obs_source_t *itemSource = obs_sceneitem_get_source(item);
	};

	using addSceneItem_t = decltype(addSceneItem);

	obs_scene_enum_items(scene, [](obs_scene_t*, obs_sceneitem_t *item, void *param) {
		addSceneItem_t *func = reinterpret_cast<addSceneItem_t*>(param);
		(*func)(item);
		return true;
	}, &addSceneItem);




}

void CreateService() {

	auto service = obs_service_create("rtmp_common", NULL, NULL, nullptr);

	//obs_service_release(service);
	//return service;
}

void ClearSceneData() {

	obs_set_output_source(0, nullptr);
	obs_set_output_source(1, nullptr);
	obs_set_output_source(2, nullptr);
	obs_set_output_source(3, nullptr);
	obs_set_output_source(4, nullptr);
	obs_set_output_source(5, nullptr);

	auto cb = [](void *unused, obs_source_t *source) {
		obs_source_remove(source);
		UNUSED_PARAMETER(unused);
		return true;
	};

	obs_enum_sources(cb, nullptr);
}

bool ResetVideo() {

	obs_video_info ovi;

	ovi.graphics_module = "libobs-d3d11.dll";

	ovi.base_width = 1920;
	ovi.base_height = 1080;

	ovi.output_width = 1280;
	ovi.output_height = 720;

	ovi.output_format = VIDEO_FORMAT_RGBA;

	ovi.adapter = 0;
	ovi.gpu_conversion = true;

	return obs_reset_video(&ovi);
}

bool ResetAudio() {

	obs_audio_info oai;

	oai.samples_per_sec = 44100;
	oai.speakers = SPEAKERS_STEREO;

	return obs_reset_audio(&oai);
}