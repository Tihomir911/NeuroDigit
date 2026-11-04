#include "TerminalUI.hpp"

#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>

namespace
{
    // ANSI colors.
    constexpr const char* RESET   = "\033[0m";
    constexpr const char* PINK    = "\033[38;5;213m";
    constexpr const char* PURPLE  = "\033[38;5;141m";
    constexpr const char* CYAN    = "\033[38;5;117m";
    constexpr const char* GREEN   = "\033[38;5;120m";
    constexpr const char* RED     = "\033[38;5;203m";
    constexpr const char* GRAY    = "\033[38;5;245m";
    constexpr const char* WHITE   = "\033[38;5;255m";

    // Check whether stdout supports terminal colors.
    bool supportsColor()
    {
        return isatty(STDOUT_FILENO) && std::getenv("NO_COLOR") == nullptr;
    }

    // Return ANSI color or an empty string.
    const char* color(const char* ansi)
    {
        return supportsColor() ? ansi : "";
    }

    void printLine()
    {
        std::cout
            << color(PURPLE)
            << "  +------------------------------------------------------+\n"
            << color(RESET);
    }
}

namespace TerminalUI
{
    void printBanner()
    {
        std::cout << '\n';

        std::cout
            << color(PINK)
            << "  _   _ _____ _   _ _____   ___  ____  ___ _____\n"
            << " | \\ | | ____| | | | ____| / _ \\|  _ \\|_ _|_   _|\n"
            << " |  \\| |  _| | | | |  _|  | | | | |_) || |  | |\n"
            << " | |\\  | |___| |_| | |___ | |_| |  _ < | |  | |\n"
            << " |_| \\_|_____\\___/|_____(_)___/|_| \\_\\___| |_|\n"
            << color(RESET)
            << '\n';

        std::cout
            << color(PINK)
            << "          /\\_/\\\\\n"
            << "         ( o.o )"
            << color(CYAN)
            << "       NEURODIGIT // SYSTEM\n"
            << color(PINK)
            << "          > ^ < "
            << color(CYAN)
            << "       Handwriting Recognition\n"
            << color(RESET)
            << '\n';

        printLine();

        std::cout
            << color(PURPLE)
            << "                  SYSTEM INITIALIZATION\n"
            << color(RESET);

        printLine();

        std::cout << '\n';
    }

    void printStep(const std::string& message)
    {
        std::cout
            << "  "
            << color(GREEN)
            << "[ OK ] "
            << color(RESET)
            << color(WHITE)
            << message
            << color(RESET)
            << '\n';
    }

    void printServerInfo(const std::string& address)
    {
        std::cout << '\n';

        std::cout
            << color(PURPLE)
            << "  +---------------- SERVER -----------------------------+\n"
            << color(RESET);

        std::cout
            << "  | "
            << color(GRAY)
            << "STATUS   : "
            << color(RESET)
            << color(GREEN)
            << "ONLINE"
            << color(RESET)
            << "                                      |\n";

        std::cout
            << "  | "
            << color(GRAY)
            << "ADDRESS  : "
            << color(RESET)
            << color(CYAN)
            << address;

        // Pad the address line to keep the frame aligned.
        const std::size_t contentLength = 12 + address.length();
        const std::size_t padding =
            contentLength < 46 ? 46 - contentLength : 1;

        std::cout << std::string(padding, ' ') << "|\n";

        std::cout
            << "  | "
            << color(GRAY)
            << "MODEL    : "
            << color(RESET)
            << color(WHITE)
            << "MNIST"
            << color(RESET)
            << "                                         |\n";

        std::cout
            << color(PURPLE)
            << "  +------------------------------------------------------+\n"
            << color(RESET);

        std::cout
            << '\n'
            << color(PINK)
            << "                  < system ready > <3\n"
            << color(RESET)
            << '\n';
    }

    void printError(const std::string& message)
    {
        std::cerr
            << '\n'
            << color(RED)
            << "  [ ERROR ] "
            << color(RESET)
            << message
            << '\n';
    }

    void printShutdown()
    {
        std::cout
            << '\n'
            << color(PINK)
            << "  [ SYSTEM ] NeuroDigit is shutting down...\n"
            << "  [ SYSTEM ] See you next time! <3\n"
            << color(RESET)
            << '\n';
    }
}