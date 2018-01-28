/*
    this file will be removed after integration
*/

#include "extension.h"
using namespace std;

void Check() {

    wot_stream::extension::Extension extension {};
    extension.UpdateStreamToken("0000-0000-0000-0000");
    extension.StartStream();

    cin.get();

    extension.StopStream();
}

int main() {
    Check();
    cin.get();
}