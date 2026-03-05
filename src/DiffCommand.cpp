#include "DiffCommand.h"
#include <fstream>
#include <string>
#include <sstream>

void DiffCommand::execute() {
    const std::vector<std::string>& args = getArguments();

    if (args.empty()) throw CommandError("requires at least one file", name);
    if (args.size() > 2) throw CommandError("too many arguments", name);

    std::ifstream file1(args[0]);
    if (!file1.is_open()) throw FileError("cannot open file", args[0]);

    std::ifstream file2;
    std::stringstream buffer;
    std::istream* stream2Ptr = nullptr;

    if (args.size() == 2) {
        file2.open(args[1]);
        if (!file2.is_open()) {
            file1.close();
            throw FileError("cannot open file", args[1]);
        }
        stream2Ptr = &file2;
    } else {
        buffer << streamManager.getInputStream().rdbuf();
        stream2Ptr = &buffer;
    }

    std::string line1, line2;
    int lineNum = 1;
    bool foundDifference = false;

    while (true) {
        bool read1 = (bool)std::getline(file1, line1);
        bool read2 = (bool)std::getline(*stream2Ptr, line2);

        if (!read1 && !read2) {
            break;
        }

        if (!read1 && read2) {
            streamManager.getOutputStream() << "Line " << lineNum << ": File 1 ended, but Input 2 has: " << line2 << std::endl;
            foundDifference = true;
        }
        else if (read1 && !read2) {
            streamManager.getOutputStream() << "Line " << lineNum << ": Input 2 ended, but File 1 has: " << line1 << std::endl;
            foundDifference = true;
        }
        else if (line1 != line2) {
            streamManager.getOutputStream() << "Difference at line " << lineNum << ":" << std::endl;
            streamManager.getOutputStream() << " < " << line1 << std::endl;
            streamManager.getOutputStream() << " > " << line2 << std::endl;
            foundDifference = true;
        }

        lineNum++;
    }

    if (!foundDifference) {
        streamManager.getOutputStream() << "Files are identical." << std::endl;
    }

    file1.close();
    if (file2.is_open()) file2.close();
}