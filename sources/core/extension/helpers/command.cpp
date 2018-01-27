#include "command.h"

namespace wot_stream::extension::helpers {

    Command::Command(std::function<void()> execute, std::function<bool()> can_execute) : ICommand() {
        this->execute = execute != nullptr ? execute : throw std::invalid_argument("execute can't be null");
        this->can_execute = can_execute;
    }
    Command::~Command() {}

    bool Command::CanExecute() { return can_execute == nullptr || can_execute(); }

    void Command::Execute() { execute(); }
}