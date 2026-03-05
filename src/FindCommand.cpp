#include "FindCommand.h"
#include <vector>
#include <sstream>

void FindCommand::execute() {
    std::string pattern;
    bool foundPattern = false;

    const std::vector<std::string>& opts = getOptions();
    for (const std::string& opt : opts) {
        if (opt.length() > 1 && opt[0] == '-') {
            pattern = opt.substr(1);

            if (pattern.size() >= 2 && pattern.front() == '"' && pattern.back() == '"') {
                pattern = pattern.substr(1, pattern.size() - 2);
            }

            foundPattern = true;
            break;
        }
    }

    if (!foundPattern) {
        throw CommandError("Missing pattern (syntax: find -\"pattern\" [arg])", name);
    }

    const std::vector<std::string>& args = getArguments();

    if (!args.empty()) {
        if (!isArgumentLiteral.empty() && isArgumentLiteral[0]) {
            streamManager.setInputString(args[0]);
        } else {
            streamManager.setInputFile(args[0]);
        }
    }

    std::istream& input = streamManager.getInputStream();
    std::string line;

    while (std::getline(input, line)) {
        if (line.find(pattern) != std::string::npos) {
            streamManager.getOutputStream() << line << std::endl;
        }
    }
}