#include "WcCommand.h"
#include <algorithm>
#include <climits>
#include <cctype>

void WcCommand::execute()
{
    bool countWords = hasOption("-w");
    bool countChars = hasOption("-c");
    bool countLines = hasOption("-l");
    bool countBlanks = hasOption("-b");
    bool max = hasOption("-max");
    bool min = hasOption("-min");
    bool unique = hasOption("-unique");
    bool longestLine = hasOption("-L");

    if (!countWords && !countChars && !countLines && !max && !unique && !min && !countBlanks && !longestLine) {
        throw CommandError("must specify -w or -c or -l or -b or -max or -unique or -min or -L", name);
    }

    if (!io.hasInputRedirect && getArguments().size() > 1) {
        throw CommandError("too many arguments", name);
    }

    std::string content = readInput();

    if (countWords) {
        int wordCount = 0;
        bool inWord = false;

        for (char c : content) {
            if (std::isspace(static_cast<unsigned char>(c))) {
                inWord = false;
            } else {
                if (!inWord) {
                    wordCount++;
                    inWord = true;
                }
            }
        }

        streamManager.getOutputStream() << wordCount << "\t";
    }
    if (countChars) {
        streamManager.getOutputStream() << content.length() << "\t";
    }
    if (countLines) {
        int lineCount = 0;
        for (auto& c : content) {
            if (c == '\n') lineCount++;
        }

        if (!content.empty() && content.back() != '\n') {
            lineCount++;
        }

        streamManager.getOutputStream() << lineCount << "\t";
    }
    if (countBlanks) {
        long blankCount = 0;

        for (char c : content) {
            if (std::isspace(static_cast<unsigned char>(c))) {
                blankCount++;
            }
        }

        streamManager.getOutputStream() << blankCount << "\t";
    }
    if (max) {
        int maxLength = 0;
        std::istringstream iss(content);
        std::string word;
        while (iss >> word) {
            if (word.length() > maxLength) {
                maxLength = word.length();
            }
        }
        streamManager.getOutputStream() << maxLength << "\t";
    }
    if (min) {
        int minLength = INT_MAX;
        bool foundAnyWord = false;
        std::istringstream iss(content);
        std::string word;
        while (iss >> word) {
            foundAnyWord = true;
            if (word.length() < minLength) {
                minLength = word.length();
            }
        }

        if (!foundAnyWord) {
            minLength = 0;
        }

        streamManager.getOutputStream() << minLength << "\t";
    }
    if (unique) {
        std::vector<std::string> words;
        std::istringstream iss(content);
        std::string word;
        while (iss >> word) {
            bool found = false;

            for (const std::string& c : words) {
                if (c == word) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                words.push_back(word);
            }
        }
        streamManager.getOutputStream() << words.size() << "\t";

        //for (const std::string& c : words) {
        //    streamManager.getOutputStream() << c << std::endl;
        //}
    }
    if (longestLine) {
        int maxLineLength = 0;
        std::istringstream iss(content);
        std::string line;
        while (std::getline(iss, line)) {
            if (line.length() > static_cast<size_t>(maxLineLength)) {
                maxLineLength = static_cast<int>(line.length());
            }
        }

        streamManager.getOutputStream() << maxLineLength << "\t";
    }

    streamManager.getOutputStream() << std::endl;
}