#ifndef CLI_COPYCOMMAND_H
#define CLI_COPYCOMMAND_H

#include "Command.h"

class CopyCommand : public Command {
public:
    CopyCommand() : Command("copy") {}

    bool requiresArgument() const override {return true;}
    bool argumentsAsInput() const override {return false;}
    bool acceptsDirectInput() const override {return true;}

    void execute() override;
};

#endif //CLI_COPYCOMMAND_H