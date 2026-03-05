#include "LineCommand.h"

void LineCommand::execute() {
    int targetLine = -1;

    for (const std::string& opt : getOptions()) {
        if (opt.length() > 2 && opt[0] == '-' && opt[1] == 'n') {
            try {
                targetLine = std::stoi(opt.substr(2));
            } catch (...) {
                throw CommandError("invalid line number format", name);
            }
        }
    }

    if (targetLine < 1) {
        throw CommandError("must specify -nN where N > 0", name);
    }

    std::string content = readInput();
    std::stringstream ss(content);
    std::string line;
    int current = 1;

    while (std::getline(ss, line)) {
        if (current == targetLine) {
            streamManager.getOutputStream() << line << std::endl;
            return;
        }
        current++;
    }

    throw CommandError("line " + std::to_string(targetLine) + " does not exist (only " + std::to_string(current - 1) + " lines)", name);
}