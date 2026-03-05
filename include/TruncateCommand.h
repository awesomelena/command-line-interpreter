#ifndef CLI_TRUNCATECOMMAND_H
#define CLI_TRUNCATECOMMAND_H

#include "Command.h"

class TruncateCommand : public Command {
public:
    TruncateCommand() : Command("truncate") {};

    bool requiresArgument() const override {return true;}
    bool acceptsDirectInput() const override {return false;}
    bool argumentsAsInput() const override {return false;}

    void execute() override;
};

#endif //CLI_TRUNCATECOMMAND_H