#include "TruncateCommand.h"
#include <fstream>

void TruncateCommand::execute() {
    const std::vector<std::string>& args = getArguments();

    if (args.size() != 1) {
        throw CommandError("requires exactly one argument (filename)", name);
    }

    const std::string filename = args[0];

    std::ifstream checkFile(filename);
    if (!checkFile.good()) {
        checkFile.close();
        throw FileError("file does not exist", filename);
    }
    checkFile.close();

    std::ofstream file(filename, std::ios::trunc);
    if (!file) {
        throw FileError("cannot open file for truncation", filename);
    }
    file.close();
}