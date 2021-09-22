#include "crypto.h"
#include "sha256.h"

using namespace std;

int main()
{
    FILE *file = fopen("test.txt", "rb");
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
    printf("%s\n", hash);
    Interface().run();
    return 0;
}
