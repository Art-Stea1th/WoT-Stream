#include "api.h"
#include "extension.h"

using namespace wot_stream::core;

std::unique_ptr<Extension> instance;

void initialize() {
    instance = std::make_unique<Extension>();
    instance->UpdateStreamToken("k7ku-0msp-7x5s-atzf");
}

void start_stream() {
    instance->StartStream();
}

void stop_stream() {
    instance->StopStream();
}

void shutdown() {
    instance.release();
}