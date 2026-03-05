#ifndef CLI_TAILCOMMAND_H
#define CLI_TAILCOMMAND_H

#include "Command.h"

class TailCommand : public Command {
public:
    TailCommand() : Command("tail"), countLines(10), useBytes(false) {}

    bool requiresArgument() const override { return false; }
    bool acceptsDirectInput() const override { return true; }
    bool argumentsAsInput() const override {return true;}

    void execute() override;

private:
    int countLines;
    bool useBytes;
};

#endif //CLI_TAILCOMMAND_H