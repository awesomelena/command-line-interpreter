#include "LastCommand.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>

static std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (std::string::npos == first) return str;
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

void LastCommand::execute() {
    if (!context) return;

    const std::vector<std::string>& history = context->getHistory();
    // history.back() is the current "last ..." command itself
    if (history.empty()) return;

    std::string currentLine = history.back();

    // pipeline mode (... | last)
    if (currentLine.find('|') != std::string::npos) {

        // split pipeline segments
        std::vector<std::string> segments;
        std::string temp;
        for (char c : currentLine) {
            if (c == '|') {
                segments.push_back(trim(temp));
                temp = "";
            } else {
                temp += c;
            }
        }
        segments.push_back(trim(temp));

        // find "last" in the pipeline
        int myIndex = -1;
        for (size_t i = 0; i < segments.size(); ++i) {
            // check if segment starts with "last"
            if (segments[i].rfind("last", 0) == 0) {
                myIndex = i;
            }
        }

        // if found and not the first command
        if (myIndex > 0) {
            std::string prevCmd = segments[myIndex - 1];

            // forward the command TEXT
            streamManager.getOutputStream() << prevCmd << std::endl;

            // forward the command RESULT (by executing it)
            std::streambuf* originalCout = std::cout.rdbuf();
            std::cout.rdbuf(streamManager.getOutputStream().rdbuf());

            try {
                context->processLine(prevCmd);
            } catch (const std::exception& e) {
                std::cout.rdbuf(originalCout);
                throw;
            }

            std::cout.rdbuf(originalCout);
            return;
        }
    }

    // history mode
    size_t historySize = history.size();
    if (historySize <= 1) throw CommandError("History is empty", name);

    const std::vector<std::string>& args = getArguments();
    const std::vector<std::string>& opts = getOptions();

    // cut pipeline (last "n")
    if (!args.empty() && !isArgumentLiteral.empty() && isArgumentLiteral[0] && opts.empty()) {

        int cutCount = 0;
        try {
            cutCount = std::stoi(args[0]);
        } catch (...) {
            throw CommandError("Invalid number format", name);
        }

        if (cutCount <= 0) throw CommandError("Count must be positive", name);

        // find last pipeline
        std::string pipeLineCmd = "";
        for (int i = (int)historySize - 2; i >= 0; --i) {
            if (history[i].find('|') != std::string::npos) {
                pipeLineCmd = history[i];
                break;
            }
        }

        if (pipeLineCmd.empty()) throw CommandError("No pipeline found in history", name);

        // split and reconstruct
        std::vector<std::string> parts;
        std::string currentPart;
        for (char c : pipeLineCmd) {
            if (c == '|') {
                parts.push_back(currentPart);
                currentPart = "";
            } else {
                currentPart += c;
            }
        }
        parts.push_back(currentPart);

        if (static_cast<size_t>(cutCount) > parts.size()) {
            throw CommandError("Pipeline only has " + std::to_string(parts.size()) + " parts", name);
        }

        std::string newCmd;
        for (int i = 0; i < cutCount; ++i) {
            newCmd += parts[i];
            if (i < cutCount - 1) newCmd += "|";
        }

        context->processLine(newCmd);
        return;
    }

    // repeat history (last, last 2, last -2, last -"2")
    int nBack = 1;
    bool foundNumber = false;

    // case: last 2 (unquoted arg) OR last "2" (Quoted but with options like -)
    if (!args.empty()) {
        try {
            nBack = std::stoi(args[0]);
            foundNumber = true;
        } catch (...) {}
    }

    // case: last -2 (Option)
    if (!foundNumber) {
        for (const std::string& opt : opts) {
            try {
                // handle -2
                int val = std::stoi(opt);
                nBack = std::abs(val);
                foundNumber = true;
                break;
            } catch (...) {
            }
        }
    }

    if (nBack <= 0) throw CommandError("Number must be positive", name);
    if (static_cast<size_t>(nBack) >= historySize) throw CommandError("History index out of range", name);

    // execute the command from history
    size_t targetIndex = historySize - 1 - nBack;

    if (nBack == 1 && args.empty() && opts.empty()) {
        streamManager.getOutputStream() << history[targetIndex] << std::endl;
    }

    context->processLine(history[targetIndex]);
}