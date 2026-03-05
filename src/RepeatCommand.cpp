#include "RepeatCommand.h"

void RepeatCommand::execute() {
    int count = -1;

    for (const std::string& opt : getOptions()) {
        if (opt.length() > 2 && opt[0] == '-' && opt[1] == 'n') {
            try {
                count = std::stoi(opt.substr(2));
            } catch (...) {
                throw CommandError("invalid count format", name);
            }
        }
    }

    if (count < 0) {
        throw CommandError("must specify -nN where N >= 0", name);
    }

    std::string content = readInput();

    for (int i = 0; i < count; ++i) {
        streamManager.getOutputStream() << content;
    }

    if (&streamManager.getOutputStream() == &std::cout) {
        if (content.empty() || content.back() != '\n') {
            streamManager.getOutputStream() << std::endl;
        }
    }
}