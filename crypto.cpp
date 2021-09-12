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
        CryptoAlgTest().diffieHellmanTest();
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

int CryptoAlgTest::diffieHellmanTest() {
    DiffieHellman Alice, Bob;

    std::cout << "Enter close key for Alice" << std::endl;
    Alice.setCloseKey();
    Alice.setOpenKey();

    std::cout << "Enter close key for Bob" << std::endl;
    Bob.setCloseKey();
    Bob.setOpenKey();

    Alice.setResKey(Bob.getOpenKey());
    Bob.setResKey(Alice.getOpenKey());

    if (Alice.getResKey() == Bob.getResKey()) {
        std::cout << "Diffie-Hellman success." << std::endl 
        << "Your secret key is " << Alice.getResKey()
        << std::endl;
    }
}

void DiffieHellman::setCloseKey()
{
    int xA;
    std::cin >> xA;
    while (xA <= 2 || xA > p - 1)
    {
        std::cout << "ERROR: secret code must be greater than 2 but smaller than " 
        << p - 1 << std::endl << "Please, enter it again: ";
        std:: cin >> xA;
    }
}

void DiffieHellman::setOpenKey()
{
    openKey = modCompare(g, closeKey, p);
}

int DiffieHellman::getOpenKey()
{
    return openKey;
}

void DiffieHellman::setResKey(int friendOpenKey)
{
    resKey = modCompare(friendOpenKey, closeKey, p);
}

int DiffieHellman::getResKey()
{
    return resKey;
}

int DiffieHellman::modCompare(int num, int pow, int mod)
{
    pow = pow % (mod - 1); //теоремка ферма
    num %= mod;

    int result = 1;
    for (int i = 1; i <= pow; i++)
    {
        result *= num;
        result %= mod;
    }
    return result;
}