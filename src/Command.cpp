#include "Command.h"
#include <algorithm>
#include <sstream>
#include <fstream>

bool Command::hasOption(const std::string& option) const {
    return std::find(options.begin(), options.end(), option) != options.end();
}

void Command::run()
{
    if (io.hasInputRedirect && !arguments.empty() && argumentsAsInput()) {
        throw CommandError("cannot have both argument and input redirection", name);
    }

    if (io.hasInputRedirect) {
        streamManager.setInputFile(io.inputFile);
    }
    else if (!arguments.empty() && argumentsAsInput()) {

        if (isArgumentLiteral.size() > 0 && isArgumentLiteral[0]) {
            streamManager.setInputString(arguments[0]);
        } else {
            streamManager.setInputFile(arguments[0]);
        }
    }

    if (io.hasOutputRedirect) {
        streamManager.setOutputFile(io.outputFile, io.appendOutput);
    }

    execute();
}

std::string Command::readInput() {
    if (streamManager.isConsoleInput() && context) {
        if (streamManager.getInputStream().eof()) {
            streamManager.getInputStream().clear();
        }
        std::stringstream capturedInput;
        std::string line;

        while (std::getline(streamManager.getInputStream(), line)) {
            context->addToHistory(line);
            capturedInput << line << std::endl;
        }

        streamManager.getInputStream().clear();
        return capturedInput.str();
    }

    std::stringstream buffer;
    buffer << streamManager.getInputStream().rdbuf();
    return buffer.str();
}