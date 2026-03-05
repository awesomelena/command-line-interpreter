#include "TrCommand.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>

static std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return result;
}

std::string TrCommand::replaceAll(const std::string &text,
                                  const std::string &from,
                                  const std::string &to,
                                  int& countOut,
                                  bool onlyFirst,
                                  bool caseInsensitive)
{
    if (from.empty()) {
        return text;
    }

    std::string result;
    size_t pos = 0;
    size_t lastPos = 0;
    countOut = 0;

    std::string searchText = caseInsensitive ? toLower(text) : text;
    std::string searchFrom = caseInsensitive ? toLower(from) : from;

    while ((pos = searchText.find(searchFrom, lastPos)) != std::string::npos) {
        result += text.substr(lastPos, pos - lastPos);
        result += to;
        lastPos = pos + from.length();
        countOut++;

        if (onlyFirst) break;
    }

    result += text.substr(lastPos);
    return result;
}

void TrCommand::execute() {
    const auto& args = getArguments();

    int dashIndex = -1;
    for (size_t i = 0; i < args.size(); ++i) {
        if (args[i] == "-") {
            dashIndex = static_cast<int>(i);
            break;
        }
    }

    if (dashIndex == -1) {
        throw CommandError("Missing search string (syntax: tr [file] -\"search\" [replace])", name);
    }

    if (dashIndex > 0) {
        if (isArgumentLiteral.size() > 0 && isArgumentLiteral[0]) {
            streamManager.setInputString(args[0]);
        } else {
            streamManager.setInputFile(args[0]);
        }
    }

    std::string search;
    if (static_cast<size_t>(dashIndex) + 1 < args.size()) {
        search = args[dashIndex + 1];
    } else {
        throw CommandError("Missing search string", name);
    }

    std::string replace;
    if (static_cast<size_t>(dashIndex) + 2 < args.size()) {
        replace = args[dashIndex + 2];
    }

    bool countOnly = hasOption("-count");
    bool onlyFirst = hasOption("-first");
    bool caseInsensitive = hasOption("-i");

    std::stringstream buffer;
    buffer << streamManager.getInputStream().rdbuf();
    std::string content = buffer.str();

    int changesCount = 0;
    std::string result = replaceAll(content, search, replace, changesCount, onlyFirst, caseInsensitive);

    if (countOnly) {
        streamManager.getOutputStream() << changesCount << std::endl;
    } else {
        streamManager.getOutputStream() << result;

        if (&streamManager.getOutputStream() == &std::cout) {
            if (result.empty() || result.back() != '\n') {
                streamManager.getOutputStream() << std::endl;
            }
        }
    }
}