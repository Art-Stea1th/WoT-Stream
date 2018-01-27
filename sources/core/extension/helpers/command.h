#pragma once
#include "../interfaces.h"

namespace wot_stream::extension::helpers {

    using namespace interfaces;

    class Command : public ICommand {
    public:
        Command(std::function<void()> execute, std::function<bool()> can_execute = nullptr);
        ~Command();

        bool CanExecute() override;
        void Execute() override;

    private:
        std::function<bool()> can_execute;
        std::function<void()> execute;
    };

}