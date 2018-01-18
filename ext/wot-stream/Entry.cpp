#include "Extension.h"

using namespace std;
using namespace WotStream;

void test() {

	auto extension = make_unique<Extension>();

	auto scene = extension->MakeScene("scene");
	auto source = extension->MakeSource("game_capture", "World of Tanks");

	cin.get();
}

int main() {

	test();
	cin.get();
}