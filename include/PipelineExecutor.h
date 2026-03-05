#ifndef CLI_PIPELINEEXECUTOR_H
#define CLI_PIPELINEEXECUTOR_H

#include "Command.h"
#include <vector>
#include <sstream>

class PipelineExecutor {
public:
    PipelineExecutor() = default;

    void execute(std::vector<Command*>& commands);

private:
    void setupCommandIO(Command* cmd, const std::string& pipedInput, bool isFirst, bool isLast, std::stringstream*& outputBuffer);
};

#endif //CLI_PIPELINEEXECUTOR_H