#include "RmCommand.h"
#include <cstdio>
#include <fstream>

void RmCommand::execute() {
    const std::vector<std::string>& args = getArguments();

    if (args.size() != 1) {
        throw CommandError("requires exactly one argument (filename)", name);
    }

    const std::string& filename = args[0];

    std::ifstream checkFile(filename);
    if (!checkFile.good()) {
        checkFile.close();
        throw FileError("file does not exist", filename);
    }
    checkFile.close();

    if (std::remove(filename.c_str()) != 0) {
        throw FileError("cannot remove file", filename);
    }
}