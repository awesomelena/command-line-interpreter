#include "RevCommand.h"
#include <algorithm>

void RevCommand::execute() {
    std::string content = readInput();
    std::stringstream ss(content);
    std::string line;

    while (getline(ss, line)) {
        std::reverse(line.begin(), line.end());
        streamManager.getOutputStream() << line << std::endl;
    }
}