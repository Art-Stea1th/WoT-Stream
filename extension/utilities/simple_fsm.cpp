#include "simple_fsm.h"


namespace wot_stream::extension::utilities {

    using Command = helpers::Command;

    SimpleFSM::SimpleFSM() {
        Configure();
        state = State::Idle;
    }
    SimpleFSM::~SimpleFSM() {}

    void SimpleFSM::Configure() {

        initialize = std::make_shared<Command>(
            [this]() { OnInitialize(); state = State::Ready; }, [this]() { return state == State::Idle; }
        );
        start = std::make_shared<Command>(
            [this]() { OnStart(); state = State::Started; }, [this]() { return state == State::Ready; }
        );
        stop = std::make_shared<Command>(
            [this]() { OnStop(); state = State::Ready; }, [this]() { return state == State::Started; }
        );
    }
}