#pragma once
#include <iostream>

enum class commands
{
    DFHLM,
    RSA,
    SHMR,
    ALGML,
    ENCODE,
    DECODE,
    FROM_FILE,
    HELP,
    CLEAR,
    NONE,
    EXIT
};

class Interface
{
private:
    commands cmd;

public:
    void run();
    void doCommand(commands cmd);
};

class CryptoAlgTest
{
public:
    int diffieHellmanTest();
};

class DiffieHellman
{
private:
    int closeKey, openKey;
    int g, p;
    int mod;

public:
    void setOpenKey();
};