#ifndef CLI_BATCHCOMMAND_H
#define CLI_BATCHCOMMAND_H

#include "Command.h"

class CommandLineInterpreter;

class BatchCommand : public Command {
public:
    BatchCommand() : Command("batch"), interpreter(nullptr) {}

    bool requiresArgument() const override { return true; }
    bool acceptsDirectInput() const override { return false; }
    bool argumentsAsInput() const override { return false; }
    bool producesOutput() const override { return true; }

    void execute() override;

    void setInterpreter(CommandLineInterpreter* interp) {interpreter = interp;}

private:
    CommandLineInterpreter* interpreter;
};

#endif //CLI_BATCHCOMMAND_H