#include "TailCommand.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

void TailCommand::execute() {
    const std::vector<std::string>& opts = getOptions();
    for (const std::string& opt : opts) {
        if (opt.length() > 1) {
            if (opt[0] == '-' && opt[1] == 'n') {
                try {
                    if (opt.length() > 2) countLines = std::stoi(opt.substr(2));
                    useBytes = false;
                } catch (...) { throw CommandError("Invalid line count", name); }
            }
            else if (opt[0] == '-' && opt[1] == 'c') {
                try {
                    if (opt.length() > 2) countLines = std::stoi(opt.substr(2));
                    useBytes = true;
                } catch (...) { throw CommandError("Invalid char count", name); }
            }
        }
    }
    if (countLines < 0) throw CommandError("Count must be non-negative", name);

    std::string content = readInput();

    if (useBytes) {
        size_t len = content.length();
        size_t startPos = 0;

        if (static_cast<size_t>(countLines) < len) {
            startPos = len - countLines;
        }

        std::string output = content.substr(startPos);
        streamManager.getOutputStream() << output;

        if (&streamManager.getOutputStream() == &std::cout) {
            if (!output.empty() && output.back() != '\n') {
                streamManager.getOutputStream() << std::endl;
            }
        }
    }
    else {
        std::vector<std::string> lines;
        std::stringstream ss(content);
        std::string line;

        while (std::getline(ss, line)) {
            lines.push_back(line);
        }

        size_t totalLines = lines.size();
        size_t startIndex = 0;

        if (static_cast<size_t>(countLines) < totalLines) {
            startIndex = totalLines - countLines;
        }

        for (size_t i = startIndex; i < totalLines; ++i) {
            streamManager.getOutputStream() << lines[i] << std::endl;
        }
    }
}