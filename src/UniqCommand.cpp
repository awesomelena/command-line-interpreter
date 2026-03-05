#include "UniqCommand.h"
#include <sstream>

void UniqCommand::execute() {
    std::string content = readInput();
    std::istringstream ss(content);

    bool allDuplicates = hasOption("-a");
    bool wordMode = hasOption("-w");

    if (wordMode) {
        std::string word;
        std::string prevWord;
        std::vector<std::string> seen;
        bool first = true;

        while (ss >> word) {
            if (allDuplicates) {
                bool found = false;
                for (const std::string& s : seen) {
                    if (s == word) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    seen.push_back(word);
                    if (!first) {
                        streamManager.getOutputStream() << " ";
                    }
                    streamManager.getOutputStream() << word;
                    first = false;
                }
            } else {
                if (first || word != prevWord) {
                    if (!first) streamManager.getOutputStream() << " ";
                    streamManager.getOutputStream() << word;
                    prevWord = word;
                    first = false;
                }
            }
        }
        streamManager.getOutputStream() << std::endl;
    } else {
        std::string line;
        std::string prevLine;
        std::vector<std::string> seen;
        bool first = true;

        while (std::getline(ss, line)) {
            if (allDuplicates) {
                bool found = false;
                for (const std::string& s : seen) {
                    if (s == line) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    seen.push_back(line);
                    streamManager.getOutputStream() << line << std::endl;
                }
            } else {
                if (first || line != prevLine) {
                    streamManager.getOutputStream() << line << std::endl;
                    prevLine = line;
                    first = false;
                }
            }
        }
    }
}