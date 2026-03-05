#ifndef CLI_TIMECOMMAND_H
#define CLI_TIMECOMMAND_H

#include "Command.h"

class TimeCommand : public Command {
public:
    TimeCommand() : Command("time") {}

    bool acceptsDirectInput() const override { return false; }

    void execute() override;
};

#endif //CLI_TIMECOMMAND_H