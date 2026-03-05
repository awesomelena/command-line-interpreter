#ifndef CLI_EXITCOMMAND_H
#define CLI_EXITCOMMAND_H

#include "Command.h"

class ExitCommand : public Command {
public:
    ExitCommand() : Command("exit") {}

    void execute() override {
        if (context) {
            context->signalExit();
        }
    }
};

#endif //CLI_EXITCOMMAND_H