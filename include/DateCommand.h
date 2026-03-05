#ifndef CLI_DATECOMMAND_H
#define CLI_DATECOMMAND_H

#include "Command.h"

class DateCommand : public Command {
public:
    DateCommand() : Command("date") {}

    bool acceptsDirectInput() const override { return false; }

    void execute() override;
};

#endif //CLI_DATECOMMAND_H