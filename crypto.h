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
    int g = 7;
    int p = 919;
    int modCompare(int num, int pow, int mod);
    int resKey;

public:
    void setgp(int g, int p);
    void setCloseKey();
    void setOpenKey();
    int getOpenKey();
    void setResKey(int friendOpenKey);
    int getResKey();
};

class AlGamal
{
private:
    int closeKey, openKey;
    int k, key, r, e, keyEnd;

public:
    void setgp();
    void setCloseKey();
    void setOpenKey();
};