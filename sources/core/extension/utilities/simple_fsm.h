#pragma once
#include "../shared.h"
#include "../helpers/command.h"

namespace wot_stream::extension::utilities {

    class SimpleFSM {
    public:
        SimpleFSM();
        ~SimpleFSM();

        void Initialize();
        void Start();
        void Stop();
        void Reset();

    protected:

        virtual void OnInitialize() = 0;
        virtual void OnStart() = 0;
        virtual void OnStop() = 0;

    private:
        enum class State { Idle, Ready, Started };
        State state;

        void Configure();

        std::shared_ptr<helpers::ICommand> initialize, start, stop, reset;
    };
}