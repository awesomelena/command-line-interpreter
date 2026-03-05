#include "BatchCommand.h"
#include "CommandLineInterpreter.h"
#include <fstream>
#include <sstream>

void BatchCommand::execute() {
    const std::vector<std::string>& args = getArguments();

    if (args.size() != 1) {
        throw CommandError("requires exactly one argument (filename)", name);
    }

    const std::string& filename = args[0];

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw FileError("cannot open batch file", filename);
    }

    if (!interpreter) {
        throw CommandError("interpreter not set for batch execution", name);
    }

    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(streamManager.getOutputStream().rdbuf());

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        try {
            interpreter->processCommandLine(line);
        }
        catch (InterpreterException& e) {
            ErrorHandler handler;
            e.accept(handler);
        }
        catch (const std::exception& e) {
            std::cerr << "Error in batch: " << e.what() << std::endl;
        }
    }

    std::cout.rdbuf(originalCoutBuffer);
    file.close();
}