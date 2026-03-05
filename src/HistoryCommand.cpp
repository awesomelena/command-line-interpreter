#include "HistoryCommand.h"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

void HistoryCommand::execute() {
    if (!context) return;

    // clear history
    if (hasOption("-c")) {
        context->clearHistory();
        streamManager.getOutputStream() << "History cleared." << std::endl;
        return;
    }

    const std::vector<std::string>& history = context->getHistory();
    std::vector<std::string> filters;
    int n = -1;

    const std::vector<std::string>& opts = getOptions();

    const std::vector<std::string>& args = getArguments();
    if (hasOption("-n") && !args.empty()) {
        try { n = std::stoi(args[0]); } catch (...) {}
    }

    for (const std::string& opt : opts) {
        if (opt == "-c") continue;

        if (opt.length() > 2 && opt.substr(0, 2) == "-n") {
            try {
                n = std::stoi(opt.substr(2));
            } catch (...) {}
            continue;
        }
        if (opt == "-n") continue;

        if (opt.length() > 1 && opt[0] == '-') {
            std::string cmdName = opt.substr(1);

            if (cmdName.size() >= 2 && cmdName.front() == '"' && cmdName.back() == '"') {
                cmdName = cmdName.substr(1, cmdName.size() - 2);
            }

            if (!cmdName.empty()) {
                filters.push_back(cmdName);
            }
        }
    }

    size_t total = history.size();
    size_t startIndex = 0;

    if (n > 0 && static_cast<size_t>(n) < total) {
        startIndex = total - n;
    }

    for (size_t i = startIndex; i < total; ++i) {
        const std::string& line = history[i];

        if (!filters.empty()) {
            std::stringstream ss(line);
            std::string cmdName;
            ss >> cmdName;

            bool match = false;
            for (const std::string& filter : filters) {
                if (cmdName == filter) {
                    match = true;
                    break;
                }
            }

            if (!match) continue;
        }

        streamManager.getOutputStream() << (i + 1) << ". " << line << std::endl;
    }
}