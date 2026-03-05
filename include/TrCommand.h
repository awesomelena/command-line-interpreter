#ifndef CLI_TRCOMMAND_H
#define CLI_TRCOMMAND_H

#include "Command.h"

class TrCommand : public Command {
public:
    TrCommand() : Command("tr") {}

    bool requiresArgument() const override { return false; }
    bool acceptsDirectInput() const override { return true; }
    bool argumentsAsInput() const override { return false; }

    void execute() override;

private:
    std::string replaceAll(const std::string& text, const std::string& from, const std::string& to, int& countOut, bool onlyFirst, bool caseInsensitive);
};

#endif //CLI_TRCOMMAND_H