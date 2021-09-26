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
    else if (input == "SHA256")
        command = commands::SHA256;
    else if (input == "ENCODE")
        command = commands::ENCODE;
    else if (input == "DECODE")
        command = commands::DECODE;
    else if (input == "EXIT")
        command = commands::EXIT;
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
    case commands::SHA256:
        sha256();
        break;
    case commands::CLEAR:
        std::cout << "clear" << std::endl;
        system("cls");
        break;
    case commands::ENCODE:
        vigenereEncode(1);
        break;
    case commands::DECODE:
        vigenereEncode(-1);
        break;

    default:
        std::cout << "unknoun command" << std::endl;
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

    std::cout << "Alice gets message: " << Alice.decMessage() << std::endl;
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
    std::cout << "Alice get: " << Alice.decode(Bob.sendMes()) << std::endl;
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
    std::cout << "Bob gets: "
              << Bob.cipherSecond(Alice.cipherSecond(firstStage)) << std::endl;
}

void sha256()
{
    char fileName[256];
    std::cin >> fileName;
    FILE *file = fopen(fileName, "rb");
    char buffer[1024];
    size_t size;
    struct sha256_buff buff;
    sha256_init(&buff);
    while (!feof(file))
    {
        // Hash file by 1kb chunks, instead of loading into RAM at once
        size = fread(buffer, 1, 1024, file);
        sha256_update(&buff, buffer, size);
    }
    char hash[65] = {0};
    sha256_finalize(&buff);
    sha256_read_hex(&buff, hash);
    std::cout << hash << std::endl;
    // printf("%s\n", hash);
}

void vigenereEncode(int mode)
{
    std::string fileName;
    std::string key;
    char c;
    int pos = 0;

    std::cin >> fileName;
    std::cin >> key;

    std::fstream file, file_tmp;
    file.open(fileName, std::fstream::in);
    if (!file)
    {
        std::cout << "Error: file can't be opened" << std::endl;
        return;
    }
    file_tmp.open("tmp.txt", std::fstream::out);
    if (!file_tmp)
    {
        std::cout << "Error: can't create tmp files" << std::endl;
        return;
    }

    while (file >> std::noskipws >> c)
    {
        c = c + mode*key[pos%key.length()];
        pos++;
        file_tmp << c;
    }

    file.close();
    file_tmp.close();

    file.open(fileName, std::fstream::out);
    if (!file)
    {
        std::cout << "Error: file can't be opened" << std::endl;
        return;
    }
    file_tmp.open("tmp.txt", std::fstream::in);
    if (!file_tmp)
    {
        std::cout << "Error: can't create tmp files" << std::endl;
        return;
    }

    while (file_tmp >> std::noskipws >> c)
        file << c;

    file.close();
    file_tmp.close();
    std::remove("tmp.txt");
    std::cout << "File '" << fileName << "' " <<  ((mode == 1)?"Encrypted":"Decrypted") << " Successfully!" << std::endl;
}
