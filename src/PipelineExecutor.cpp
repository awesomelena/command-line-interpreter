#include "PipelineExecutor.h"
#include <iostream>

void PipelineExecutor::setupCommandIO(Command* cmd, const std::string& pipedInput, bool isFirst, bool isLast, std::stringstream*& outputBuffer) {
    const IORedirection& io = cmd->getIO();

    if (isFirst) {
        if (io.hasInputRedirect) {
            cmd->streamManager.setInputFile(io.inputFile);
        }
        else if (!cmd->getArguments().empty() && cmd->argumentsAsInput()) {
            if (cmd->isArgumentLiteral.size() > 0 && cmd->isArgumentLiteral[0]) {
                cmd->streamManager.setInputString(cmd->getArguments()[0]);
            } else {
                cmd->streamManager.setInputFile(cmd->getArguments()[0]);
            }
        }
    }
    else {
        cmd->streamManager.setInputString(pipedInput);
    }

    if (isLast) {
        if (io.hasOutputRedirect) {
            cmd->streamManager.setOutputFile(io.outputFile, io.appendOutput);
        }
    }
    else {
        std::stringstream* temp = new std::stringstream();
        try {
            cmd->streamManager.setOutputStream(temp, true);
        } catch (...) {
            delete temp;
            throw;
        }
        outputBuffer = temp;
    }
}

void PipelineExecutor::execute(std::vector<Command*>& commands) {
    if (commands.empty()) return;

    if (commands.size() == 1) {
        commands[0]->run();
        return;
    }

    std::string pipeBuffer;

    for (size_t i = 0; i < commands.size(); ++i) {
        Command* cmd = commands[i];
        bool isFirst = (i == 0);
        bool isLast = (i == commands.size() - 1);

        std::stringstream* outputBuffer = nullptr;

        setupCommandIO(cmd, pipeBuffer, isFirst, isLast, outputBuffer);

        cmd->execute();

        if (!isLast && outputBuffer != nullptr) {
            pipeBuffer = outputBuffer->str();
        }
    }
}