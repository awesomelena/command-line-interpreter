#ifndef CLI_PROMPTCOMMAND_H
#define CLI_PROMPTCOMMAND_H

#include "Command.h"

class PromptCommand : public Command {
public:
    PromptCommand() : Command("prompt") {}

    bool requiresArgument() const override { return true; }
    bool acceptsDirectInput() const override { return true; }
    bool argumentsAsInput() const override { return false; }
    bool producesOutput() const override { return false; }

    void execute() override {
        if (getArguments().empty()) throw CommandError("Missing argument", name);
        if (context) {
            bool oneTime = hasOption("-t");
            context->setPrompt(getArguments()[0], oneTime);
        }
    }

    friend class CommandLineInterpreter;
};

#endif //CLI_PROMPTCOMMAND_H