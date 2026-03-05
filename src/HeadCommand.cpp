#include "HeadCommand.h"
#include <string>


void HeadCommand::execute() {
    const std::vector<std::string>& opts = getOptions();
    for (const std::string& opt : opts) {
        if (opt.length() > 1) {
            if (opt[0] == '-' && opt[1] == 'n') {
                try {
                    if (opt.length() > 2) {
                        lineCount = std::stoi(opt.substr(2));
                    }
                    useBytes = false;
                } catch (...) {
                    throw CommandError("Invalid line count format", name);
                }
            }
            else if (opt[0] == '-' && opt[1] == 'c') {
                try {
                    if (opt.length() > 2) {
                        lineCount = std::stoi(opt.substr(2));
                    }
                    useBytes = true;
                } catch (...) {
                    throw CommandError("Invalid char count format", name);
                }
            }
        }
    }

    if (lineCount < 0) throw CommandError("Count must be non-negative", name);

    std::string content = readInput();

    std::stringstream processStream(content);

    char lastChar = '\0';

    if (useBytes) {
        char c;
        int charsRead = 0;

        processStream >> std::noskipws;

        while (charsRead < lineCount && processStream >> c) {
            streamManager.getOutputStream() << c;
            lastChar = c;
            charsRead++;
        }
    }
    else {
        std::string line;
        int linesRead = 0;

        while (linesRead < lineCount && std::getline(processStream, line)) {
            streamManager.getOutputStream() << line;
            linesRead++;

            if (!processStream.eof() || linesRead < lineCount) {
                streamManager.getOutputStream() << std::endl;
                lastChar = '\n';
            } else {
                lastChar = line.empty() ? '\0' : line.back();
            }
        }
    }

    if (&streamManager.getOutputStream() == &std::cout) {
        if (lastChar != '\n') {
            streamManager.getOutputStream() << std::endl;
        }
    }
}