#include "TouchCommand.h"

void TouchCommand::execute()
{
    const std::vector<std::string>& args = getArguments();

    if (args.size() != 1) {
        throw CommandError("requires exactly one argument (filename)", name);
    }

    const std::string& filename = args[0];

    std::ifstream checkFile(filename);
    if (checkFile.good()) {
        checkFile.close();
        throw FileError("file already exists", filename);
    }
    checkFile.close();

    std::ofstream file(filename);
    if (!file) {
        throw FileError("cannot create file", filename);
    }
    file.close();
}