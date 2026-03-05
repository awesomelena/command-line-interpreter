#include "ClearCommand.h"

void ClearCommand::execute()
{
    streamManager.getOutputStream() << "\033[2J\033[1;1H";
}