#ifndef CLI_PHASE2_FINDCOMMAND_H
#define CLI_PHASE2_FINDCOMMAND_H

#include "Command.h"

class FindCommand : public Command {
public:
    FindCommand() : Command("find") {}

    bool acceptsDirectInput() const override {return true;}
    bool requiresArgument() const override {return false;}
    bool argumentsAsInput() const override {return true;}

    void execute() override;
};

#endif //CLI_FINDCOMMAND_H