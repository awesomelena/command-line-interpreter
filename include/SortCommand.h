#ifndef CLI_SORTCOMMAND_H
#define CLI_SORTCOMMAND_H

# include "Command.h"

class SortCommand : public Command {
public:
    SortCommand() : Command("sort") {}

    bool requiresArgument() const override {return false;}
    bool argumentsAsInput() const override {return true;}
    bool acceptsDirectInput() const override {return true;}

    void execute() override;
};

#endif //CLI_SORTCOMMAND_H