
#include "TerminalUI.hpp"

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <unistd.h>

namespace
{
    // ANSI colors
    constexpr const char* RESET  = "\033[0m";
    constexpr const char* PINK   = "\033[38;5;213m";
    constexpr const char* PURPLE = "\033[38;5;141m";
    constexpr const char* CYAN   = "\033[38;5;117m";
    constexpr const char* GREEN  = "\033[38;5;120m";
    constexpr const char* RED    = "\033[38;5;203m";
    constexpr const char* GRAY   = "\033[38;5;245m";
    constexpr const char* WHITE  = "\033[38;5;255m";

    bool supportsColor()
    {
        return isatty(STDOUT_FILENO)
            && std::getenv("NO_COLOR") == nullptr;
    }

    const char* color(const char* ansi)
    {
        return supportsColor() ? ansi : "";
    }
}

namespace TerminalUI
{
    // ========================================================
    // STARTUP SCREEN
    // ========================================================

    void printStartupScreen(
        const std::string& frontendPath,
        const std::string& address
    )
    {
        // ----------------------------------------------------
        // LEFT COLUMN
        // ----------------------------------------------------

        const std::vector<std::string> left =
        {
            "  _   _ _____ _   _ _____   ___  ____  ___ _____",
            " | \\ | | ____| | | | ____| / _ \\|  _ \\|_ _|_   _|",
            " |  \\| |  _| | | | |  _|  | | | | |_) || |  | |",
            " | |\\  | |___| |_| | |___ | |_| |  _ < | |  | |",
            " |_| \\_|_____\\___/|_____(_)___/|_| \\_\\___| |_|",
            "",
            "          NEURODIGIT // SYSTEM",
            "          Handwriting Recognition",
            "",
            "  +------------------------------------------------------+",
            "",
            "  [ MODEL INITIALIZATION ]",
            "  [ OK ] Neural network loaded",
            "  [ OK ] Model weights initialized",
            "",
            "",
            "",
            "  [ HTTP SERVER ]",
            "  [ OK ] Frontend directory detected",
            "  [ OK ] Frontend mounted successfully",
            "",
            "  +---------------- SERVER -----------------------------+",
            "  | STATUS   : ONLINE",
            "  | ADDRESS  : " + address,
            "  | MODEL    : MNIST",
            "  +------------------------------------------------------+"
        };

        // ----------------------------------------------------
        // RIGHT COLUMN: ASTOLFO
        // Original artwork. Do not modify its lines.
        // ----------------------------------------------------

        const char* cat[] =
        {
            R"(⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⠶⣶⣤⣔⣶⡶⣦⣤⣠⣶⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣯⡏⠉⣴⣿⢿⢿⣿⢷⣶⣍⡻⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⠀⠀⢠⡶⢤⣴⣿⠟⠀⢁⡞⠛⡟⢣⠐⢳⡀⠈⢻⣯⡺⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⠀⠀⢸⣇⣾⣟⠎⠀⢠⡞⠀⡀⢀⠆⠀⠀⣧⠀⡀⠹⡳⣦⣿⡦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⠀⠀⡸⣻⣟⡟⠀⠀⢸⠁⢀⢧⢸⡾⡀⠶⣿⡿⣳⣅⣼⢻⠙⢿⡶⢤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⠀⠞⠉⡿⢡⢡⠀⠀⣿⠀⣿⣯⣭⣹⢝⡊⢸⠚⢻⠝⢺⣗⢆⣸⡷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⠀⠀⢠⢳⣮⣣⣤⣄⡟⣇⡿⣻⡿⣿⠉⠻⣜⠐⠿⣛⡻⠿⠿⠵⡳⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⠀⢀⡿⢻⢡⡿⣼⡃⢡⠈⣴⠈⠒⠋⠀⠀⠐⠀⠀⠀⠌⡟⡦⣌⡉⠻⡉⢣⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⠀⢸⠃⢹⣾⠀⢹⣷⡜⣷⣿⣧⠀⠀⢴⠞⠛⣿⠀⢀⢧⡜⡟⠀⠉⠓⢄⡀⠈⠓⠤⣀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⠀⠈⠀⢸⢹⡆⢸⣿⡛⡷⣝⣽⠳⢦⣌⡓⠀⣢⠔⡡⢻⡋⠀⠀⠀⠀⠀⠑⢦⡀⠀⠀⠑⠢⣄⠀⠀⠀⠀)",
            R"(⠀⠀⠀⠀⠀⠈⣼⢇⡼⠿⣿⣿⡿⣿⡄⠀⠀⢹⢉⡰⠛⠁⠈⠁⠀⠀⠀⠀⠀⠀⠀⠙⢶⡀⠀⠀⠀⠙⠢⡀⠀)",
            R"(⠀⠀⠀⠀⠀⢏⣞⠝⠀⠀⠸⣿⣿⡺⣮⣤⢀⣘⠓⠶⣶⡔⢶⣖⢤⡤⠤⠤⠠⣖⢲⣦⡤⠽⢦⡀⠀⠀⠀⠘⣆)",
            R"(⠀⠀⠀⢀⢴⣾⡾⠀⠀⠀⢀⠚⣿⣷⡈⠻⣆⡈⠁⢁⣈⣇⠘⣿⣄⠀⠀⠀⠀⢸⠈⡿⡇⠀⠀⠉⠀⠀⠀⠀⢸)",
            R"(⠀⠀⠀⡎⣫⠟⡇⠀⠀⠀⠘⠀⠈⠻⣿⣶⣾⣽⣲⣗⠋⢻⣦⣿⠀⠀⠀⠀⠀⢠⣤⣆⡧⠤⠤⠄⠤⠐⠒⠂⠁)",
            R"(⠀⠀⢀⢾⢯⡎⠀⠀⠀⠀⠀⣴⠁⠀⠀⠉⠙⢟⠻⠿⣿⣼⡟⣬⠂⣧⠴⠐⠂⠚⠋⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⣸⡼⢣⣿⡖⠒⠂⠀⠒⡳⠀⠀⠀⠀⠀⠈⠑⠚⠓⣟⣉⣳⠀⢱⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⣿⡧⢺⢻⣿⣿⣓⣲⣾⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⡇⠫⣆⠸⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⡻⡅⠊⣶⡇⠀⠀⠀⢸⡆⠀⠀⠀⠀⠀⠀⠀⠀⢀⡇⠀⠀⠸⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⢻⡿⡾⠈⡇⠀⠀⠀⢸⢇⠀⠀⠀⠀⠀⠀⠀⠀⠘⣴⡀⠀⠀⢸⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⠰⣝⠿⣐⡏⠀⠀⠀⣼⡸⠀⠀⠀⠀⠀⠀⠀⠀⠀⢣⠱⡄⠀⡟⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⠀⠙⣿⣿⣯⠀⠀⠀⡟⡇⠀⠀⠀⠀⠀⣀⣀⡀⠤⠬⢆⡿⣄⣃⡈⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⠀⠀⠹⣿⣿⠀⠀⠀⢱⣷⠈⠉⠉⠉⠉⠀⠀⠀⠀⠀⠘⠁⢸⠧⠞⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⠀⠀⠀⠈⠯⣆⠀⢀⡴⠁⠀⠀⠀⠀⠀⠀⠀⠀⢀⠆⠀⢀⡎⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⠀⠀⠀⠀⠀⠈⣳⠟⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⡿⠀⠀⢸⡃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⠀⠀⠀⠀⢠⡾⢇⠀⠀⠉⠓⠲⠤⠤⠤⠤⠤⠤⠲⢲⣻⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⠀⠀⠀⣰⠏⠀⡸⠓⢵⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣨⣼⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⠀⢀⣾⠛⢀⡞⠁⠀⠀⡞⠉⠉⠉⠁⡖⠀⠈⠹⡍⠉⠈⠙⣞⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⢠⡴⡟⠉⠀⡾⠀⠀⠀⡸⠀⠀⠀⠀⢠⠇⠀⠀⠀⡇⠀⠀⠀⠘⡜⢦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⢸⣿⡽⠀⠀⡰⠁⠀⠀⢰⠃⠀⠀⠀⠀⣼⠄⠀⠀⠀⢱⡄⠀⠀⠀⠹⣄⢳⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⢨⣿⣄⠀⣴⠃⠀⠀⢀⡏⠀⠀⠀⠀⠀⣯⠀⠀⠀⠀⢸⣳⠀⠀⠀⠀⠙⣦⢝⣶⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠻⢿⣿⣥⣀⡀⠀⡼⠀⠀⠀⠀⠀⠀⣇⠀⠀⠀⠀⠀⡟⢇⠀⢀⠀⣀⣌⣿⡃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⠸⠟⠙⢻⣿⣶⣿⣿⣷⣶⣤⣀⣰⡿⣿⣶⣶⣦⣤⣼⣾⠿⠛⠛⠋⠉⠉⢳⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⠀⠀⠀⠀⢧⠉⠙⠁⠈⠉⠛⠛⠚⠛⢀⡇⠉⢯⠙⠉⠁⠀⠀⠀⠀⠀⠀⠀⢣⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
            R"(⠀⠀⠀⠀⠀⠀⠸⡄⠀⠀⠀⠀⠀⠀⠀⠀⠰⠂⠀⠀⢧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢧⠀⠀⠀⠀)"
        };

        // ----------------------------------------------------
        // PRINT BOTH COLUMNS
        // ----------------------------------------------------

        constexpr std::size_t LEFT_WIDTH = 58;

        const std::size_t leftLines = left.size();
        const std::size_t catLines =
            sizeof(cat) / sizeof(cat[0]);

        const std::size_t totalLines =
            leftLines > catLines ? leftLines : catLines;

        std::cout << '\n';

        for (std::size_t i = 0; i < totalLines; ++i)
        {
            if (i < leftLines)
            {
                const std::string& line = left[i];

                if (line.find("[ MODEL") != std::string::npos ||
                    line.find("[ HTTP") != std::string::npos)
                {
                    std::cout
                        << color(PURPLE)
                        << line
                        << color(RESET);
                }
                else if (line.find("[ OK ]") != std::string::npos)
                {
                    const std::size_t position =
                        line.find("[ OK ]");

                    std::cout
                        << color(GREEN)
                        << line.substr(0, position + 6)
                        << color(RESET)
                        << color(WHITE)
                        << line.substr(position + 6)
                        << color(RESET);
                }
                else if (line.find("+---") != std::string::npos)
                {
                    std::cout
                        << color(PURPLE)
                        << line
                        << color(RESET);
                }
                else
                {
                    std::cout
                        << color(WHITE)
                        << line
                        << color(RESET);
                }

                if (line.length() < LEFT_WIDTH)
                {
                    std::cout
                        << std::string(
                            LEFT_WIDTH - line.length(),
                            ' '
                        );
                }
            }
            else
            {
                std::cout << std::string(LEFT_WIDTH, ' ');
            }

            if (i < catLines)
            {
                std::cout
                    << color(PINK)
                    << cat[i]
                    << color(RESET);
            }

            std::cout << '\n';
        }

        // ----------------------------------------------------
        // SYSTEM READY
        // ----------------------------------------------------

        std::cout
            << '\n'
            << color(PINK)
            << "                  < system ready > <3\n"
            << color(RESET);

        // ----------------------------------------------------
        // NEURAL NETWORK INFORMATION
        // ----------------------------------------------------

        std::cout
            << '\n'
            << color(PURPLE)
            << "  +---------------- NEURAL NETWORK INFO ---------------+\n"
            << color(RESET);

        std::cout
            << "  | "
            << color(GRAY) << "INPUT LAYER    : "
            << color(RESET)
            << color(WHITE) << "784 neurons"
            << color(RESET) << '\n';

        std::cout
            << "  | "
            << color(GRAY) << "HIDDEN LAYERS  : "
            << color(RESET)
            << color(WHITE) << "2"
            << color(RESET) << '\n';

        std::cout
            << "  | "
            << color(GRAY) << "HIDDEN NEURONS : "
            << color(RESET)
            << color(WHITE) << "128 + 64"
            << color(RESET) << '\n';

        std::cout
            << "  | "
            << color(GRAY) << "OUTPUT LAYER   : "
            << color(RESET)
            << color(WHITE) << "10 neurons"
            << color(RESET) << '\n';

        std::cout
            << "  | "
            << color(GRAY) << "TOTAL NEURONS  : "
            << color(RESET)
            << color(CYAN) << "986"
            << color(RESET) << '\n';

        std::cout
            << color(PURPLE)
            << "  +------------------------------------------------------+\n"
            << color(RESET)
            << '\n';
    }


    // ========================================================
    // ERROR
    // ========================================================

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


    // ========================================================
    // SHUTDOWN
    // ========================================================

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
