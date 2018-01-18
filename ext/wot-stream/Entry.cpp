#include <stl-deps.h>
#include <obs-deps.h>
#include <internal-shared.h>

using namespace std;
using namespace WotStream;

void test();

int main() {

	// curl_global_init(CURL_GLOBAL_ALL);
	test();

	cin.get();
}

void test() {

	Extension ext;
	ext.Startup();
	ext.ResetAudio();
	ext.ResetVideo();
	ext.LoadAllModules();

	cin.get();
}