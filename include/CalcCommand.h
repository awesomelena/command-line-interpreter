#ifndef CLI_CALCCOMMAND_H
#define CLI_CALCCOMMAND_H

#include "Command.h"

class CalcCommand : public Command {
public:
    CalcCommand() : Command("calc") {}

    bool requiresArgument() const override {return true;}
    bool acceptsDirectInput() const override {return true;}

    void execute() override;
};

#endif //CLI_CALCCOMMAND_H