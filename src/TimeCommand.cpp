#define _CRT_SECURE_NO_WARNINGS // for visual studio
#include "TimeCommand.h"
#include <ctime>

void TimeCommand::execute()
{
    std::time_t now = std::time(nullptr);
    std::tm* timeinfo = std::localtime(&now);

    char buffer[100];

    bool h = hasOption("-h");
    bool m = hasOption("-m");
    bool s = hasOption("-s");

    std::string format = "";

    if (!h && !m && !s) {
        format = "%H:%M:%S";
    }
    else {
        if (h) format += "%H:";
        if (m) format += "%M:";
        if (s) format += "%S:";

        if (!format.empty() && format.back() == ':') {
            format.pop_back();
        }
    }

    std::strftime(buffer, sizeof(buffer), format.c_str(), timeinfo);

    streamManager.getOutputStream() << buffer << std::endl;
}