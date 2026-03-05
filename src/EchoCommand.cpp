#include "EchoCommand.h"
#include <algorithm>
#include <sstream>
#include <set>

void EchoCommand::execute()
{
    std::set<std::string> simpleOptions = { "-u", "-l", "-reverse", "-t"};

    int repeatCount = 1;

    for (const std::string& opt : getOptions()) {
        if (simpleOptions.find(opt) != simpleOptions.end()) {
            continue;
        }

        if (opt.length() >= 2 && opt.substr(0, 2) == "-r") {
            if (opt == "-r") {
                continue;
            }

            std::string numPart = opt.substr(2);

            try {
                int val = std::stoi(numPart);
                repeatCount = val;
                continue;
            } catch (...) {
                throw CommandError("Invalid number format for -r", name);
            }
        }

        throw CommandError("Unknown option: " + opt, name);
    }

    if (repeatCount <= 0) repeatCount = 1;

    if (!io.hasInputRedirect && getArguments().size() > 1) {
        throw CommandError("too many arguments", name);
    }

    std::string content = readInput();

    if (hasOption("-u")) {
        for (auto& c : content) {
            c = std::toupper(c);
        }
    }

    if (hasOption("-l")) {
        for (auto& c : content) {
            c = std::tolower(c);
        }
    }

    if (hasOption("-t")) {
        if (!content.empty()) {
            std::string tabbed;

            tabbed += "\t";

            for (size_t i = 0; i < content.length(); ++i) {
                tabbed += content[i];

                if (content[i] == '\n' && i < content.length() - 1) {
                    tabbed += "\t";
                }
            }
            content = tabbed;
        }
    }

    if (hasOption("-reverse")) {
        int left = 0;
        int right = content.size() - 1;
        while (left < right) {
            std::swap(content[left], content[right]);
            left++;
            right--;
        }
    }

    for (int i = 0; i < repeatCount; i++) {
        streamManager.getOutputStream() << content;
    }

    if (&streamManager.getOutputStream() == &std::cout) {
        if (content.empty() || content.back() != '\n') {
            streamManager.getOutputStream() << std::endl;
        }
    }
}