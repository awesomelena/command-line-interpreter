#include <iostream>

#include "CommandLineInterpreter.h"

int main() {
    try {
        CommandLineInterpreter interpreter;
        interpreter.run();
    } catch (std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}