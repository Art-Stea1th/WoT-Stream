#include "Extension.h"

using namespace std;
using namespace WotStream;

void test() {

	auto extension = make_unique<Extension>();

	auto scene = obs_scene_create("scene");
	auto source = obs_source_create("game_capture", "World of Tanks", nullptr, nullptr);

	auto scene_item = obs_scene_add(scene, source);
	obs_sceneitem_addref(scene_item);

	vec2 pos{ 0, 0 }, scale{ 1, 1 }, bounds{ 1920, 1080 };

	obs_sceneitem_set_pos(scene_item, &pos);
	obs_sceneitem_set_scale(scene_item, &scale);

	obs_sceneitem_set_bounds(scene_item, &bounds);
	obs_sceneitem_set_bounds_type(scene_item, OBS_BOUNDS_SCALE_INNER);
	obs_sceneitem_set_bounds_alignment(scene_item, 0); // center

	obs_set_output_source(0, source);

	obs_sceneitem_selected(scene_item);

	cin.get();
}

int main() {

	test();
	cin.get();
}