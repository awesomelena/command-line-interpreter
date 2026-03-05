#ifndef CLI_PWDCOMMAND_H
#define CLI_PWDCOMMAND_H

#include "Command.h"
#include <filesystem>

class PwdCommand : public Command {
public:
    PwdCommand() : Command("pwd") {}

    bool acceptsDirectInput() const override {return false;}
    bool argumentsAsInput() const override {return false;}

    void execute() override {
        streamManager.getOutputStream() << std::filesystem::current_path().string() << std::endl;
    }
};

#endif //CLI_PWDCOMMAND_H