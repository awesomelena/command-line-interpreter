#include "CommandFactory.h"
#include "CommandLineInterpreter.h"
#include "EchoCommand.h"
#include "TimeCommand.h"
#include "DateCommand.h"
#include "TouchCommand.h"
#include "WcCommand.h"
#include "PromptCommand.h"
#include "ExitCommand.h"
#include "ClearCommand.h"
#include "LastCommand.h"
#include "MenuCommand.h"
#include "HistoryCommand.h"
#include "CopyCommand.h"
#include "DiffCommand.h"
#include "GrepCommand.h"
#include "CountCommand.h"
#include "TruncateCommand.h"
#include "RmCommand.h"
#include "TrCommand.h"
#include "HeadCommand.h"
#include "BatchCommand.h"
#include "SortCommand.h"
#include "CatCommand.h"
#include "TailCommand.h"
#include "AliasCommand.h"
#include "PwdCommand.h"
#include "RevCommand.h"
#include "UniqCommand.h"
#include "MoveCommand.h"
#include "LineCommand.h"
#include "TeeCommand.h"
#include "SplitCommand.h"
#include "JoinCommand.h"
#include "RepeatCommand.h"
#include "WrapCommand.h"
#include "BetweenCommand.h"
#include "FindCommand.h"

CommandFactory::CommandFactory() {
    registerCommands();
}

CommandFactory::~CommandFactory() {}

void CommandFactory::registerCommands() {
    commandRegistry["echo"] = []() { return new EchoCommand(); };
    commandRegistry["time"] = []() { return new TimeCommand(); };
    commandRegistry["date"] = []() { return new DateCommand(); };
    commandRegistry["touch"] = []() { return new TouchCommand(); };
    commandRegistry["wc"] = []() { return new WcCommand(); };
    commandRegistry["prompt"] = []() { return new PromptCommand(); };
    commandRegistry["exit"] = []() { return new ExitCommand(); };
    commandRegistry["clear"] = []() { return new ClearCommand(); };
    commandRegistry["last"] = []() { return new LastCommand(); };
    commandRegistry["menu"] = []() { return new MenuCommand(); };
    commandRegistry["history"] = []() { return new HistoryCommand(); };
    commandRegistry["copy"] = []() { return new CopyCommand(); };
    commandRegistry["diff"] = []() { return new DiffCommand(); };
    commandRegistry["grep"] = []() { return new GrepCommand(); };
    commandRegistry["count"] = []() { return new CountCommand(); };
    commandRegistry["truncate"] = []() { return new TruncateCommand(); };
    commandRegistry["rm"] = []() { return new RmCommand(); };
    commandRegistry["tr"] = []() { return new TrCommand(); };
    commandRegistry["head"] = []() { return new HeadCommand(); };
    commandRegistry["batch"] = [this]() {
        BatchCommand* cmd = new BatchCommand();
        cmd->setInterpreter(interpreter);
        return cmd;
    };
    commandRegistry["sort"] = []() { return new SortCommand(); };
    commandRegistry["cat"] = []() { return new CatCommand(); };
    commandRegistry["tail"] = [](){return new TailCommand();};
    commandRegistry["alias"] = [](){return new AliasCommand();};
    commandRegistry["pwd"] = []() { return new PwdCommand(); };
    commandRegistry["rev"] = []() { return new RevCommand(); };
    commandRegistry["uniq"] = []() { return new UniqCommand(); };
    commandRegistry["move"] = []() { return new MoveCommand(); };
    commandRegistry["line"] = []() { return new LineCommand(); };
    commandRegistry["tee"] = []() { return new TeeCommand(); };
    commandRegistry["split"] = []() { return new SplitCommand(); };
    commandRegistry["join"] = []() { return new JoinCommand(); };
    commandRegistry["repeat"] = []() { return new RepeatCommand(); };
    commandRegistry["wrap"] = []() { return new WrapCommand(); };
    commandRegistry["between"] = []() { return new BetweenCommand(); };
    commandRegistry["find"] = []() { return new FindCommand(); };
}

Command* CommandFactory::createCommand(const std::string& name) {
    auto it = commandRegistry.find(name);
    if (it != commandRegistry.end()) {
        Command* cmd = it->second();
        cmd->setContext(interpreter);
        return cmd;
    }
    throw UnknownCommandError(name);
}

bool CommandFactory::isValidCommand(const std::string& name) const
{
    return commandRegistry.find(name) != commandRegistry.end();
}

std::vector<std::string> CommandFactory::getAvailableCommands() const
{
    std::vector<std::string> commands;
    for (const auto& pair : commandRegistry) {
        commands.push_back(pair.first);
    }
    return commands;
}