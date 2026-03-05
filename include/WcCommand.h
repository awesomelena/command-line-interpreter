#ifndef CLI_WCCOMMAND_H
#define CLI_WCCOMMAND_H

#include "Command.h"

class WcCommand : public Command {
public:
    WcCommand() : Command("wc") {}

    bool requiresArgument() const override {return false;}
    bool acceptsDirectInput() const override {return true;}

    void execute() override;
};

#endif //CLI_WCCOMMAND_H