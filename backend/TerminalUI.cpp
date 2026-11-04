#include "TerminalUI.hpp"

#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>

namespace
{
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

    void printLine()
    {
        std::cout
            << color(PURPLE)
            << "  +------------------------------------------------------+"
            << color(RESET);
    }
}

namespace TerminalUI
{
    void printBanner()
    {
        // Левая колонка — прежний баннер NeuroDigit.
        const std::string left[] =
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
            "                  SYSTEM INITIALIZATION",
            "  +------------------------------------------------------+"
        };

        // Правая колонка — ASCII-art, переданный пользователем.
        // Raw string literals сохраняют Unicode-символы и пробелы.
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
            R"(⠀⠀⠀⠀⠀⠀⢠⡾⢇⠀⠀⠉⠓⠲⠤⠤⠤⠤⠤⠤⠤⠲⢲⣻⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)",
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

        constexpr std::size_t LEFT_WIDTH = 58;
        constexpr std::size_t LEFT_LINES = sizeof(left) / sizeof(left[0]);
        constexpr std::size_t CAT_LINES = sizeof(cat) / sizeof(cat[0]);
        constexpr std::size_t TOTAL_LINES =
            LEFT_LINES > CAT_LINES ? LEFT_LINES : CAT_LINES;

        std::cout << '\n';

        for (std::size_t i = 0; i < TOTAL_LINES; ++i)
        {
            if (i < LEFT_LINES)
            {
                const std::string& line = left[i];

                std::cout << color(PINK) << line << color(RESET);

                if (line.length() < LEFT_WIDTH)
                {
                    std::cout << std::string(
                        LEFT_WIDTH - line.length(),
                        ' '
                    );
                }
            }
            else
            {
                std::cout << std::string(LEFT_WIDTH, ' ');
            }

            if (i < CAT_LINES)
            {
                std::cout << color(PINK) << cat[i] << color(RESET);
            }

            std::cout << '\n';
        }

        std::cout << '\n';
    }

    void printStep(const std::string& message)
    {
        std::cout
            << "  "
            << color(GREEN) << "[ OK ] "
            << color(RESET)
            << color(WHITE) << message
            << color(RESET) << '\n';
    }

    void printSection(const std::string& title)
    {
        std::cout
            << '\n'
            << color(PURPLE)
            << "  [ " << title << " ]\n"
            << color(RESET);
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
            << color(GRAY) << "STATUS   : "
            << color(RESET)
            << color(GREEN) << "ONLINE"
            << color(RESET)
            << "                                      |\n";

        std::cout
            << "  | "
            << color(GRAY) << "ADDRESS  : "
            << color(RESET)
            << color(CYAN) << address
            << color(RESET);

        const std::size_t contentLength = 12 + address.length();
        const std::size_t padding =
            contentLength < 46 ? 46 - contentLength : 1;

        std::cout << std::string(padding, ' ') << "|\n";

        std::cout
            << "  | "
            << color(GRAY) << "MODEL    : "
            << color(RESET)
            << color(WHITE) << "MNIST"
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
            << color(RED) << "  [ ERROR ] "
            << color(RESET)
            << message << '\n';
    }

    void printShutdown()
    {
        std::cout
            << '\n'
            << color(PINK)
            << "  [ SYSTEM ] NeuroDigit is shutting down...\n"
            << "  [ SYSTEM ] See you next time! <3\n"
            << color(RESET) << '\n';
    }
}
