#pragma once
#include <iostream>

class ElGamal
{
private:
    int p = 541, g = 10;
    int privateKey;
    int publicKey;
    int message;
    int encrMessage[2];
    int modCompare(int num, int pow, int mod);

public:
    void setgp(int g, int p);
    void setPrivateKey();
    void setPublicKey();
    int getPublicKey();
    void setMessage();
    int *sendEncMessage(int friendPublicKey);
    void getMessage(int message[2]);
    int decMessage();
};

class DiffieHellman
{
private:
    int closeKey, openKey;
    int g = 10;
    int p = 541;
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

class RSA
{
private:
    int p, q;
    int mod, len;
    int encKey, decKey;
    int message;
    int publicKey[2];
    int gcd(int a, int b);
    bool isPrime(int number);
    int extEucAlg(int a, int b);
    int modCompare(int num, int pow, int mod);

public:
    void setpq();
    void setEncKey();
    void setDecKey();
    void setMes();
    int* getPublicKey();
    void recievePublicKey(int publicKey[2]);
    int sendMes();
    int decode(int message);
};

class SHAMIR
{
    private:
    int p;
    int privateKeyFirst, privateKeySecond;
    int message;
    int extEucAlg(int a, int b);
    bool isPrime(int number);
    int modCompare(int num, int pow, int mod);
    int NOD(int a, int b);

    public:
    int getMessage();
    void setp();
    void setPrivateKey();
    void setMessage();
    int cipherFirst(int recived);
    int cipherSecond(int recived);
};