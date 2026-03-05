#ifndef CLI_GREPCOMMAND_H
#define CLI_GREPCOMMAND_H

#include "Command.h"

class GrepCommand : public Command {
public:
    GrepCommand() : Command("grep") {}

    bool requiresArgument() const override {return true;}
    bool acceptsDirectInput() const override {return true;}
    bool argumentsAsInput() const override {return false;}

    void execute() override;
};

#endif //CLI_GREPCOMMAND_H