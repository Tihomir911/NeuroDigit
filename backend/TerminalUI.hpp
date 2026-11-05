#pragma once

#include <string>

namespace TerminalUI
{
    void printStartupScreen(
        const std::string& frontendPath,
        const std::string& address
    );

    void printError(const std::string& message);

    void printShutdown();
}