#ifndef CLI_CLEARCOMMAND_H
#define CLI_CLEARCOMMAND_H

#include "Command.h"

class ClearCommand : public Command {
public:
    ClearCommand() : Command("clear") {}

    bool acceptsDirectInput() const override {return false;}

    void execute() override;
};

#endif //CLI_CLEARCOMMAND_H