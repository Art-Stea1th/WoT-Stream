#pragma once
#include "../shared.h"

namespace wot_stream::extension::helpers {

    class ICommand {
    public:
        virtual bool CanExecute() = 0;
        virtual void Execute() = 0;

        virtual ~ICommand() {}

    protected:
        ICommand() = default;
    };

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