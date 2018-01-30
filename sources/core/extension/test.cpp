#include <iostream>
#include "api.h"

int main() {

    initialize();

    std::cin.get();

    start_stream();

    std::cin.get();

    stop_stream();

    std::cin.get();

    shutdown();

}