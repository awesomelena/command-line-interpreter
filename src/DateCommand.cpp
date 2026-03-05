#define _CRT_SECURE_NO_WARNINGS // for visual studio
#include "DateCommand.h"
#include <ctime>
#include <cmath>
#include <cstdio>

void DateCommand::execute()
{
    std::time_t now = std::time(nullptr);


    bool d = hasOption("-d");
    bool m = hasOption("-m");
    bool y = hasOption("-y");
    bool r = hasOption("-r");
    bool day = hasOption("-day");
    bool tomorrow = hasOption("-tomorrow");
    bool yesterday = hasOption("-yesterday");
    bool diff = hasOption("-diff");

    if (diff) {
        if (getArguments().empty()) {
            throw CommandError("missing date argument for -diff", name);
        }

        std::string dateStr = getArguments()[0]; // e.g., "01.01.2023"
        std::tm targetTm = {0};

        int day, month, year;
        if (sscanf(dateStr.c_str(), "%d.%d.%d", &day, &month, &year) != 3) {
            throw CommandError("invalid date format. Use DD.MM.YYYY", name);
        }

        targetTm.tm_mday = day;
        targetTm.tm_mon = month - 1;
        targetTm.tm_year = year - 1900;
        targetTm.tm_isdst = -1;

        std::time_t targetTime = std::mktime(&targetTm);

        if (targetTime == -1) {
            throw CommandError("invalid date", name);
        }

        double secondsDiff = std::difftime(now, targetTime);
        long days = static_cast<long>(std::abs(secondsDiff) / (60 * 60 * 24));

        streamManager.getOutputStream() << days << " days" << std::endl;
        return;
    }


    if (tomorrow) {
        now += (24 * 60 * 60);
    }
    else if (yesterday) {
        now -= (24 * 60 * 60);
    }

    std::tm* timeinfo = std::localtime(&now);

    char buffer[100];

    if (d) {
        std::strftime(buffer, sizeof(buffer), "%d", timeinfo);
        streamManager.getOutputStream() << buffer << std::endl;
    } else if (m) {
        std::strftime(buffer, sizeof(buffer), "%m", timeinfo);
        streamManager.getOutputStream() << buffer << std::endl;
    } else if (y) {
        std::strftime(buffer, sizeof(buffer), "%Y", timeinfo);
        streamManager.getOutputStream() << buffer << std::endl;
    } else if (r) {
        streamManager.getOutputStream() << now << std::endl;
    } else if (day) {
        std::strftime(buffer, sizeof(buffer), "%A", timeinfo);
        streamManager.getOutputStream() << buffer << std::endl;
    } else {
        std::strftime(buffer, sizeof(buffer), "%d.%m.%Y.", timeinfo);
        streamManager.getOutputStream() << buffer << std::endl;
    }
}