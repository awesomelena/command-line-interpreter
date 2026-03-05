#include "TeeCommand.h"
#include <fstream>

void TeeCommand::execute() {
    const std::vector<std::string>& args = getArguments();

    if (args.empty()) {
        throw CommandError("missing filename", name);
    }

    bool append = hasOption("-a");

    std::ios::openmode mode = std::ios::out;
    if (append) mode |= std::ios::app;
    else mode |= std::ios::trunc;

    std::ofstream file(args[0], mode);
    if (!file.is_open()) {
        throw FileError("cannot open file", args[0]);
    }

    std::string content = readInput();

    file << content;
    file.close();

    streamManager.getOutputStream() << content;

    if (&streamManager.getOutputStream() == &std::cout) {
        if (content.empty() || content.back() != '\n') {
            streamManager.getOutputStream() << std::endl;
        }
    }
}