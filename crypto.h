#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "CRALG.h"
#include "sha256.h"

enum class commands
{
    DFHLM,
    RSA,
    SHMR,
    ELGML,
    SHA256,
    ENCODE,
    DECODE,
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
    int elGamalTest();
    int RSATest();
    int SHMRTest();
};

void sha256(); 
void vigenereEncode(int mode);