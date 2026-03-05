#include "CopyCommand.h"

void CopyCommand::execute() {
    const std::vector<std::string>& args = getArguments();

    bool append = hasOption("-a");

    if (args.empty()) {
        throw CommandError("missing destination file", name);
    }

    if (args.size() > 2) {
        throw CommandError("too many arguments", name);
    }

    std::string destination = args[0];

    std::ios::openmode mode = std::ios::out;
    if (append) {
        mode |= std::ios::app;
    } else {
        mode |= std::ios::trunc;
    }

    std::ofstream outFile(destination, mode);
    if (!outFile.is_open()) {
        throw FileError("cannot open destination file", destination);
    }

    if (args.size() == 2) {
        if (isArgumentLiteral.size() > 1 && isArgumentLiteral[1]) {
            outFile << args[1] << std::endl;
        }
        else {
            std::string source = args[1];
            std::ifstream inFile(source);

            if (!inFile.is_open()) {
                outFile.close();
                throw FileError("cannot open source file", source);
            }

            outFile << inFile.rdbuf();
            inFile.close();
        }
    }
    else {
        outFile << streamManager.getInputStream().rdbuf();
    }

    outFile.close();
}