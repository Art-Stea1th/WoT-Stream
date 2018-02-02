#pragma once
#define EXPORT __declspec(dllexport)

extern "C" {

    EXPORT void initialize();

    EXPORT void start_stream();
    EXPORT void stop_stream();

    EXPORT void shutdown();
}