#include "SortCommand.h"
#include <algorithm>
#include <functional>

void SortCommand::execute() {
    if (!io.hasInputRedirect && getArguments().size() > 1) {
        throw CommandError("too many arguments", name);
    }

    bool descending = hasOption("-d");

    std::stringstream buffer;
    buffer << streamManager.getInputStream().rdbuf();
    std::string content = buffer.str();

    std::vector<std::string> words;
    std::stringstream iss(content);
    std::string word;

    while (iss >> word) {
        words.push_back(word);
    }

    if (descending) {
        std::sort(words.begin(), words.end(), std::greater<std::string>());
    } else {
        std::sort(words.begin(), words.end());
    }

    for (const std::string& w : words) {
        streamManager.getOutputStream() << w << std::endl;
    }
}