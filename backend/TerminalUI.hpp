#pragma once

#include <string>

namespace TerminalUI
{
    // Display the NeuroDigit startup banner.
    void printBanner();

    // Display a successful initialization step.
    void printStep(const std::string& message);

    // Display server information.
    void printServerInfo(const std::string& address);

    // Display an error message.
    void printError(const std::string& message);

    // Display a shutdown message.
    void printShutdown();
}