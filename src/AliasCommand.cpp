#include "AliasCommand.h"

void AliasCommand::execute() {
    const std::vector<std::string>& args = getArguments();

    if (args.size() != 2) {
        throw CommandError("requires two arguments: alias \"name\" \"command\"", name);
    }
    if (!context) return;

    context->setAlias(args[0], args[1]);
}