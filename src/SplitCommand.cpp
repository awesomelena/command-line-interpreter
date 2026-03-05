#include "SplitCommand.h"
#include <sstream>

void SplitCommand::execute() {
    const std::vector<std::string>& args = getArguments();

    if (args.empty()) {
        throw CommandError("missing delimiter argument", name);
    }

    std::string delimiter = args[0];

    if (args.size() > 1) {
        if (isArgumentLiteral.size() > 1 && isArgumentLiteral[1]) {
            streamManager.setInputString(args[1]);
        } else {
            streamManager.setInputFile(args[1]);
        }
    }

    std::string content = readInput();

    if (delimiter.empty()) {
        streamManager.getOutputStream() << content << std::endl;
        return;
    }

    size_t pos = 0;
    size_t lastPos = 0;

    while ((pos = content.find(delimiter, lastPos)) != std::string::npos) {
        streamManager.getOutputStream() << content.substr(lastPos, pos - lastPos) << std::endl;
        lastPos = pos + delimiter.length();
    }

    streamManager.getOutputStream() << content.substr(lastPos) << std::endl;
}