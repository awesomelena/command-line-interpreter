#include "CountCommand.h"
#include <sstream>

void CountCommand::execute() {
    if (!context) return;

    const std::vector<std::string>& history = context->getHistory();
    const std::vector<std::string>& opts = getOptions();

    if (opts.empty()) {
        streamManager.getOutputStream() << "Total commands: " << history.size() << std::endl;
        return;
    }

    for (const std::string& opt : opts) {
        std::string targetName = opt;

        if (!targetName.empty() && targetName[0] == '-') {
            targetName = targetName.substr(1);
        }

        if (targetName.size() >= 2 && targetName.front() == '"' && targetName.back() == '"') {
            targetName = targetName.substr(1, targetName.size() - 2);
        }

        if (targetName.empty()) continue;

        int specificCount = 0;

        for (const std::string& line : history) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string cmdName;
            ss >> cmdName;

            if (cmdName == targetName) {
                specificCount++;
            }
        }

        streamManager.getOutputStream() << targetName << ": " << specificCount << std::endl;
    }
}