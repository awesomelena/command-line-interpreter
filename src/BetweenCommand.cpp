#include "BetweenCommand.h"
#include <sstream>

void BetweenCommand::execute() {
    int startLine = -1;
    int endLine = -1;

    for (const std::string& opt : getOptions()) {
        if (opt.substr(0, 6) == "-start") {
            try {
                startLine = std::stoi(opt.substr(6));
            } catch (...) {
                throw CommandError("invalid start line number", name);
            }
        }
        else if (opt.substr(0, 4) == "-end") {
            try {
                endLine = std::stoi(opt.substr(4));
            } catch (...) {
                throw CommandError("invalid end line number", name);
            }
        }
    }

    if (startLine < 1 || endLine < 1) {
        throw CommandError("must specify -startN and -endM where N,M > 0", name);
    }
    if (startLine > endLine) {
        throw CommandError("start must be <= end", name);
    }

    std::string content = readInput();
    std::stringstream ss(content);
    std::string line;
    int current = 1;

    while (std::getline(ss, line)) {
        if (current >= startLine && current <= endLine) {
            streamManager.getOutputStream() << line << std::endl;
        }
        if (current > endLine) break;
        current++;
    }
}
