
#pragma once

#include <string>

namespace TerminalUI
{
    void printBanner();

    void printStep(const std::string& message);

    void printServerInfo(const std::string& address);

    void printError(const std::string& message);

    void printShutdown();

    void printSection(const std::string& title);
}
