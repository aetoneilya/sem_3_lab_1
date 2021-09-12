#include "crypto.h"

std::istream &operator>>(std::istream &is, commands &command)
{
    std::string input;
    is >> input;
    if (input == "DFHLM")
        command = commands::DFHLM;
    else if (input == "RSA")
        command = commands::RSA;
    else if (input == "SHMR")
        command = commands::SHMR;
    else if (input == "ALGML")
        command = commands::ALGML;
    else if (input == "ENCODE")
        command = commands::ENCODE;
    else if (input == "DECODE")
        command = commands::DECODE;
    else if (input == "FROM_FILE")
        command = commands::FROM_FILE;
    else if (input == "EXIT")
        command = commands::EXIT;
    else if (input == "HELP")
        command = commands::HELP;
    else if (input == "CLEAR")
        command = commands::CLEAR;
    else
        command = commands::NONE;
    return is;
}


void Interface::run()
{
    while (true)
    {
        std::cin >> cmd;
        if (cmd == commands::EXIT)
            return;
        doCommand(cmd);
    }
}

void Interface::doCommand(commands cmd)
{
    switch (cmd)
    {
    case commands::DFHLM:
        /* code */
        std::cout << "Diffie-Hellman" << std::endl;
        break;
    case commands::ALGML:
        std::cout << "Al-Gamal" << std::endl;
        break;
    case commands::RSA:
        std::cout << "RSA" << std::endl;
        break;
    case commands::SHMR:
        std::cout << "Shamir" << std::endl;
        break;
    case commands::CLEAR:
        std::cout << "clear" << std::endl;
        break;

    default:
        std::cout << "unknoun" << std::endl;
        break;
    }
}


