#ifndef CLI_ECHOCOMMAND_H
#define CLI_ECHOCOMMAND_H

#include "Command.h"

class EchoCommand : public Command {
public:
    EchoCommand() : Command("echo") {}
    void execute() override;
};

#endif //CLI_ECHOCOMMAND_H