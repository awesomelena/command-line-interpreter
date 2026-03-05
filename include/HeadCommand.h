#ifndef CLI_HEADCOMMAND_H
#define CLI_HEADCOMMAND_H

#include "Command.h"

class HeadCommand : public Command {
public:
    HeadCommand() : Command("head"), lineCount(10), useBytes(false) {}

    bool requiresArgument() const override { return false; }
    bool acceptsDirectInput() const override { return true; }
    bool argumentsAsInput() const override { return true; }

    void execute() override;

    void setLineCount(int n) { lineCount = n; }
    int getLineCount() const { return lineCount; }

private:
    int lineCount;
    bool useBytes;
};

#endif //CLI_HEADCOMMAND_H