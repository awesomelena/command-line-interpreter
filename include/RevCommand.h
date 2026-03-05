#ifndef CLI_REVCOMMAND_H
#define CLI_REVCOMMAND_H

#include "Command.h"

class RevCommand : public Command {
public:
    RevCommand() : Command("rev") {}

    bool acceptsDirectInput() const override {return true;}
    bool argumentsAsInput() const override {return true;}

    void execute() override;
};

#endif //CLI_REVCOMMAND_H