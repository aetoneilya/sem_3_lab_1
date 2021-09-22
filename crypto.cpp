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
    else if (input == "ELGML")
        command = commands::ELGML;
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
        std::cout << "Diffie-Hellman" << std::endl;
        CryptoAlgTest().diffieHellmanTest();
        break;
    case commands::ELGML:
        std::cout << "El-Gamal" << std::endl;
        CryptoAlgTest().elGamalTest();
        break;
    case commands::RSA:
        std::cout << "RSA" << std::endl;
        CryptoAlgTest().RSATest();
        break;
    case commands::SHMR:
        std::cout << "Shamir" << std::endl;
        CryptoAlgTest().SHMRTest();
        break;
    case commands::CLEAR:
        std::cout << "clear" << std::endl;
        break;

    default:
        std::cout << "unknoun" << std::endl;
        break;
    }
}

int CryptoAlgTest::diffieHellmanTest()
{
    DiffieHellman Alice, Bob;

    std::cout << "Enter close key for Alice" << std::endl;
    Alice.setCloseKey();
    Alice.setOpenKey();

    std::cout << "Enter close key for Bob" << std::endl;
    Bob.setCloseKey();
    Bob.setOpenKey();

    Alice.setResKey(Bob.getOpenKey());
    Bob.setResKey(Alice.getOpenKey());

    if (Alice.getResKey() == Bob.getResKey())
    {
        std::cout << "Diffie-Hellman success." << std::endl
                  << "Your secret key is " << Alice.getResKey()
                  << std::endl;
    }
}

int CryptoAlgTest::elGamalTest()
{
    ElGamal Alice, Bob;

    std::cout << "Enter close key for Alice" << std::endl;
    Alice.setPrivateKey();
    Alice.setPublicKey();

    std::cout << "Enter close key for Bob" << std::endl;
    Bob.setPrivateKey();

    std::cout << "Enter message for Bob" << std::endl;
    Bob.setMessage();

    Alice.getMessage(Bob.sendEncMessage(Alice.getPublicKey()));

    std::cout << "Decoded message: " << Alice.decMessage() << std::endl;
}

int CryptoAlgTest::RSATest()
{
    RSA Alice, Bob;

    std::cout << "Enter two prime numbers for Alice" << std::endl;
    Alice.setpq();
    std::cout << "Enter encryption key" << std::endl;
    Alice.setEncKey();
    Alice.setDecKey();

    Bob.recievePublicKey(Alice.getPublicKey());

    std::cout << "Enter Bob's message" << std::endl;
    Bob.setMes();
    std::cout << "Alice get " << Alice.decode(Bob.sendMes()) << std::endl;
}

int CryptoAlgTest::SHMRTest()
{
    SHAMIR Alice, Bob;

    std::cout << "Enter p for Alice" << std::endl;
    Alice.setp();
    std::cout << "Enter p for Bob" << std::endl;
    Bob.setp();

    std::cout << "Enter Alice's private key" << std::endl;
    Alice.setPrivateKey();
    std::cout << "Enter Bob's private key" << std::endl;
    Bob.setPrivateKey();
    std::cout << "Enter Alice's message to Bob" << std::endl;
    Alice.setMessage();

    int firstStage = Bob.cipherFirst(Alice.cipherFirst(Alice.getMessage()));
    std::cout << Bob.cipherSecond(Alice.cipherSecond(firstStage)) << std::endl;
}

void DiffieHellman::setCloseKey()
{
    std::cin >> closeKey;
    while (closeKey <= 2 || closeKey > p - 1)
    {
        std::cout << "ERROR: secret code must be greater than 2 but smaller than "
                  << p - 1 << std::endl
                  << "Please, enter it again: ";
        std::cin >> closeKey;
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
    std::cin >> privateKey;
    while (privateKey <= 2 || privateKey > p - 1)
    {
        std::cout << "ERROR: secret code must be greater than 2 but smaller than "
                  << p - 1 << std::endl
                  << "Please, enter it again: ";
        std::cin >> privateKey;
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

int *ElGamal::sendEncMessage(int friendPublicKey)
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

void RSA::setpq()
{
    std::cin >> p;
    while (!isPrime(p))
    {
        std::cout << "ERROR: p must be prime " << std::endl;
        std::cin >> p;
    }

    std::cin >> q;
    while (!isPrime(q))
    {
        std::cout << "ERROR: q must be prime " << std::endl;
        std::cin >> q;
    }

    mod = p * q;
    len = (p - 1) * (q - 1);
}

void RSA::setEncKey()
{
    std::cin >> encKey;
    while (gcd(encKey, len) != 1 && gcd(encKey, mod) != 1 && encKey < 1 && encKey > len)
    {
        std::cout << "Error: incorect key" << std::endl;
        std::cin >> encKey;
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
        }
        else
        {
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
    std::cin >> p;
    while (!isPrime(p))
    {
        std::cout << "ERROR: p must be prime " << std::endl;
        std::cin >> p;
    }
}

void SHAMIR::setPrivateKey()
{
    std::cin >> privateKeyFirst;
    privateKeySecond = extEucAlg(privateKeyFirst, p - 1);
    std::cout << "private key second " << privateKeySecond << std::endl;
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