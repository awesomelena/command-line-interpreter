#include "WrapCommand.h"
#include <sstream>
#include <algorithm>

void WrapCommand::execute() {
    int width = -1;

    for (const std::string& opt : getOptions()) {
        if (opt.length() > 2 && opt[0] == '-' && opt[1] == 'w') {
            try {
                width = std::stoi(opt.substr(2));
            } catch (...) {
                throw CommandError("invalid width format", name);
            }
        }
    }

    if (width < 1) {
        throw CommandError("must specify -wN where N > 0", name);
    }

    std::string content = readInput();

    for (size_t i = 0; i < content.length(); i += width) {
        size_t len = std::min(static_cast<size_t>(width), content.length() - i);
        streamManager.getOutputStream() << content.substr(i, len) << std::endl;
    }
}
