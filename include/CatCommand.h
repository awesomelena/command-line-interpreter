#ifndef CLI_CATCOMMAND_H
#define CLI_CATCOMMAND_H

#include "Command.h"

class CatCommand : public Command {
public:
    CatCommand() : Command("cat") {}

    bool requiresArgument() const override {return false;}
    bool argumentsAsInput() const override {return true;}
    bool acceptsDirectInput() const override {return true;}

    void execute() override;
};

#endif //CLI_CATCOMMAND_H