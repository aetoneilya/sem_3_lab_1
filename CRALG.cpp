#include "CRALG.h"

int getNum()
{
    int number;
    while (!(std::cin >> number) || (std::cin.peek() != '\n'))
    {
        std::cin.clear();
        while (std::cin.get() != '\n')
            ;
        std::cout << "Error: not a number" << std::endl;
    }
    return number;
}

int ElGamal::modCompare(int num, int pow, int mod)
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

void ElGamal::setPrivateKey()
{
    privateKey = getNum();
    while (privateKey <= 2 || privateKey > p - 1)
    {
        std::cout << "ERROR: secret code must be greater than 2 but smaller than "
                  << p - 1 << std::endl
                  << "Please, enter it again: ";
        privateKey = getNum();
    }
}

void ElGamal::setPublicKey()
{
    publicKey = modCompare(g, privateKey, p);
    std::cout << "Open key is " << publicKey << std::endl;
}

int ElGamal::getPublicKey()
{
    return publicKey;
}

void ElGamal::setMessage()
{
    std::cin >> message;
}

int* ElGamal::sendEncMessage(int friendPublicKey)
{
    encrMessage[0] = modCompare(g, privateKey, p);
    encrMessage[1] = modCompare(friendPublicKey, privateKey, p);
    encrMessage[1] = (encrMessage[1] * message) % p;
    return encrMessage;
}

void ElGamal::getMessage(int message[2])
{
    encrMessage[0] = message[0];
    encrMessage[1] = message[1];
}

int ElGamal::decMessage()
{
    return (encrMessage[1] * modCompare(encrMessage[0], p - 1 - privateKey, p)) % p;
}

void DiffieHellman::setCloseKey()
{
    closeKey = getNum();
    while (closeKey <= 2 || closeKey > p - 1)
    {
        std::cout << "ERROR: secret code must be greater than 2 but smaller than "
                  << p - 1 << std::endl;
        closeKey = getNum();
    }
}

void DiffieHellman::setOpenKey()
{
    openKey = modCompare(g, closeKey, p);
    std::cout << "Open key is " << openKey << std::endl;
}

int DiffieHellman::getOpenKey()
{
    return openKey;
}

void DiffieHellman::setResKey(int friendOpenKey)
{
    resKey = modCompare(friendOpenKey, closeKey, p);
    std::cout << "Result key " << resKey << std::endl;
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

void RSA::setpq()
{
    p = getNum();
    while (!isPrime(p))
    {
        std::cout << "ERROR: p must be prime " << std::endl;
        p = getNum();
    }

    q = getNum();
    while (!isPrime(q))
    {
        std::cout << "ERROR: q must be prime " << std::endl;
        q = getNum();
    }

    mod = p * q;
    len = (p - 1) * (q - 1);
}

void RSA::setEncKey()
{
    encKey = getNum();
    while (gcd(encKey, len) != 1 || gcd(encKey, mod) != 1 
    || encKey < 1 || encKey > len)
    {
        std::cout << "Error: incorect key" << std::endl;
        encKey = getNum();
    }
}

void RSA::setDecKey()
{
    decKey = extEucAlg(encKey, len);
    std::cout << "decKey " << decKey << std::endl;
}

void RSA::setMes()
{
    std::cin >> message;
}

int RSA::sendMes()
{
    int encMes = modCompare(message, publicKey[0], publicKey[1]);
    std::cout << "sending message " << encMes << std::endl;

    return encMes;
}

int RSA::decode(int message)
{
    return modCompare(message, decKey, mod);
}

int *RSA::getPublicKey()
{
    publicKey[0] = encKey;
    publicKey[1] = mod;

    return publicKey;
}

void RSA::recievePublicKey(int r_publicKey[2])
{
    publicKey[0] = r_publicKey[0];
    publicKey[1] = r_publicKey[1];
}

int RSA::extEucAlg(int a, int b)
{
    int mod = b;
    //FIX THIS DOESN'T WORK
    int q, r, nod, x, y;
    int x2 = 1, x1 = 0, y2 = 0, y1 = 1;
    while (b > 0)
    {
        q = a / b;
        r = a - q * b;
        x = x2 - q * x1;
        y = y2 - q * y1;
        a = b;
        b = r;
        x2 = x1;
        x1 = x;
        y2 = y1;
        y1 = y;
    }
    nod = a, x = x2, y = y2;
    if (x < 0)
    {
        x = x + mod;
    }
    return x;
}

bool RSA::isPrime(int number)
{
    if (number < 2)
        return false;
    if (number == 2)
        return true;
    if (number % 2 == 0)
        return false;
    for (int i = 3; (i * i) <= number; i += 2)
    {
        if (number % i == 0)
            return false;
    }
    return true;
}

int RSA::gcd(int a, int b)
{
    while (a != b)
    {
        if (a > b)
        {
            a -= b;
        } else {
            b -= a;
        }
    }
    return a;
}

int RSA::modCompare(int num, int pow, int mod)
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

void SHAMIR::setp()
{
    p = getNum();
    while (!isPrime(p))
    {
        std::cout << "ERROR: p must be prime " << std::endl;
        p = getNum();
    }
}

void SHAMIR::setPrivateKey()
{
    // взаимно простое с  p - 1
    privateKeyFirst = getNum();
    while (NOD(privateKeyFirst, p - 1) != 1)
    {
        std::cout << "Error: private key must be mutual prime with p - 1" << std::endl;
        privateKeyFirst = getNum();
    }
    privateKeySecond = extEucAlg(privateKeyFirst, p - 1);
    std::cout << "private key second " << privateKeySecond << std::endl;
}

int SHAMIR::NOD(int a, int b)
{
    while (a > 0 && b > 0)

        if (a > b)
            a %= b;

        else
            b %= a;

    return a + b;
}
void SHAMIR::setMessage()
{
    std::cin >> message;
    while (message > p)
    {
        std::cout << "ERROR: message must be less then p" << std::endl;
        std::cin >> message;
    }
}

int SHAMIR::cipherFirst(int recived)
{
    int res = modCompare(recived, privateKeyFirst, p);
    std::cout << "first " << res << std::endl;
    return res;
}

int SHAMIR::cipherSecond(int recived)
{
    int res = modCompare(recived, privateKeySecond, p);
    std::cout << "second " << res << std::endl;
    return res;
}

int SHAMIR::getMessage()
{
    return message;
}

int SHAMIR::extEucAlg(int a, int b)
{
    int mod = b;
    int q, r, nod, x, y;
    int x2 = 1, x1 = 0, y2 = 0, y1 = 1;
    while (b > 0)
    {
        q = a / b;
        r = a - q * b;
        x = x2 - q * x1;
        y = y2 - q * y1;
        a = b;
        b = r;
        x2 = x1;
        x1 = x;
        y2 = y1;
        y1 = y;
    }
    nod = a, x = x2, y = y2;
    if (x < 0)
    {
        x = x + mod;
    }
    return x;
}

bool SHAMIR::isPrime(int number)
{
    if (number < 2)
        return false;
    if (number == 2)
        return true;
    if (number % 2 == 0)
        return false;
    for (int i = 3; (i * i) <= number; i += 2)
    {
        if (number % i == 0)
            return false;
    }
    return true;
}

int SHAMIR::modCompare(int num, int pow, int mod)
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