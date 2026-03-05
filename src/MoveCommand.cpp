#include "MoveCommand.h"

void MoveCommand::execute() {
    const std::vector<std::string>& args = getArguments();

    if (args.size() != 2) {
        throw CommandError("requires two arguments: move source destination", name);
    }

    const std::string& source = args[0];
    const std::string& destination = args[1];

    std::ifstream checkSource(source);
    if (!checkSource.good()) {
        checkSource.close();
        throw FileError("source file does not exist", source);
    }
    checkSource.close();

    // copy content
    std::ifstream inFile(source, std::ios::binary);
    std::ofstream outFile(destination, std::ios::binary);

    if (!inFile.is_open()) throw FileError("cannot open source file", source);
    if (!outFile.is_open()) {
        inFile.close();
        throw FileError("cannot open destination file", destination);
    }

    outFile << inFile.rdbuf();
    inFile.close();
    outFile.close();

    // delete original
    if (std::remove(source.c_str()) != 0) {
        throw FileError("cannot remove source file after move", source);
    }
}