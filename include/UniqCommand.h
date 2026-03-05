#ifndef CLI_UNIQCOMMAND_H
#define CLI_UNIQCOMMAND_H

#include "Command.h"

class UniqCommand : public Command {
public:
    UniqCommand() : Command("uniq") {}

    bool acceptsDirectInput() const override {return true;}
    bool argumentsAsInput() const override {return true;}

    void execute() override;
};

#endif //CLI_UNIQCOMMAND_H