#ifndef CLI_MENUCOMMAND_H
#define CLI_MENUCOMMAND_H

#include "Command.h"

class MenuCommand : public Command {
public:
    MenuCommand() : Command("menu") {}

    bool requiresArgument() const override {return false;}
    bool acceptsDirectInput() const override {return false;}

    void execute() override {
        if (context) {
            auto cmds = context->getAvailableCommands();
            streamManager.getOutputStream() << "Available commands:\n";
            for(const auto& c : cmds) {
                streamManager.getOutputStream() << ">>  " << c << "\n";
            }
        }
    }
};

#endif //CLI_MENUCOMMAND_H