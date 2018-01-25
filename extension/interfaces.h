#pragma once
#include "shared.h"

namespace wot_stream::extension::interfaces {

    class ICommand {
    public:
        virtual bool CanExecute() = 0;
        virtual void Execute() = 0;

        virtual ~ICommand() {}

    protected:
        ICommand() = default;
    };    
}