#include "JoinCommand.h"
#include <sstream>

void JoinCommand::execute() {
    const std::vector<std::string>& args = getArguments();

    if (args.empty()) {
        throw CommandError("missing separator argument", name);
    }

    std::string separator = args[0];

    // if there's a second argument, use it as input -> can be changed
    if (args.size() > 1) {
        if (isArgumentLiteral.size() > 1 && isArgumentLiteral[1]) {
            streamManager.setInputString(args[1]);
        } else {
            streamManager.setInputFile(args[1]);
        }
    }

    std::string content = readInput();
    std::stringstream ss(content);
    std::string line;
    bool first = true;

    while (std::getline(ss, line)) {
        if (!first) {
            streamManager.getOutputStream() << separator;
        }
        streamManager.getOutputStream() << line;
        first = false;
    }

    streamManager.getOutputStream() << std::endl;
}