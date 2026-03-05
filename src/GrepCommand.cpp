#include "GrepCommand.h"

static std::string toLower(const std::string& str) {
    std::string result = str;
    for (auto& c : result) {
        c = std::tolower(static_cast<unsigned char>(c));
    }
    return result;
}

void GrepCommand::execute() {
    bool invert = hasOption("-v");
    bool countOnly = hasOption("-c");
    bool caseInsensitive = hasOption("-i");

    const std::vector<std::string>& args = getArguments();

    if (args.empty()) {
        throw CommandError("missing search word", name);
    }

    if (args.size() > 2) {
        throw CommandError("too many arguments", name);
    }

    std::string word = args[0];

    if (args.size() == 2) {
        streamManager.setInputFile(args[1]);
    }

    std::string content = readInput();
    std::stringstream ss(content);
    std::string line;
    int matchCount = 0;

    while (std::getline(ss, line)) {
        bool found;
        if (caseInsensitive) {
            found = (toLower(line).find(toLower(word)) != std::string::npos);
        } else {
            found = (line.find(word) != std::string::npos);
        }

        if (invert) found = !found;

        if (found) {
            matchCount++;
            if (!countOnly) {
                streamManager.getOutputStream() << line << std::endl;
            }
        }
    }

    if (countOnly) {
        streamManager.getOutputStream() << matchCount << std::endl;
    }
}