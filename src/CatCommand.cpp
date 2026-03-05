#include "CatCommand.h"
#include <string>
#include <sstream>

void CatCommand::execute() {
    if (!io.hasInputRedirect && getArguments().size() > 1) {
        throw CommandError("too many arguments", name);
    }

    bool numberLines = hasOption("-n");

    std::stringstream buffer;

    buffer << streamManager.getInputStream().rdbuf();

    if (numberLines) {
        std::string line;
        int lineCount = 1;

        while (std::getline(buffer, line)) {
            streamManager.getOutputStream() << lineCount << ". " << line << std::endl;
            lineCount++;
        }
    } else {
        streamManager.getOutputStream() << buffer.str() << std::endl;
    }
}