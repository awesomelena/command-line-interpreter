#ifndef CLI_COUNTCOMMAND_H
#define CLI_COUNTCOMMAND_H

#include "Command.h"

class CountCommand : public Command {
public:
    CountCommand() : Command("count") {}

    bool requiresArgument() const override {return false;}
    bool acceptsDirectInput() const override {return false;}
    bool argumentsAsInput() const override {return false;}

    void execute() override;
};

#endif //CLI_COUNTCOMMAND_H