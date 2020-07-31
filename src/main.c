#include <stdlib.h>
#include <stdio.h>
#include "disassembler.h"

int main(int argc, char const *argv[])
{
    FILE *f = fopen(argv[1], "rb");
    if (f == NULL)
    {
        printf("Error - couldn't open %s\n", argv[1]);
        exit(1);
    }

    fseek(f, 0L, SEEK_END);
    int fsize = ftell(f);
    fseek(f, 0L, SEEK_SET);

    unsigned char *buffer = malloc(fsize);

    int r = fread(buffer, fsize, 1, f);
    fclose(f);

    int pc = 0;

    while (pc < fsize)
    {
        pc += disassemble8080Op(buffer, pc);
    }

    return 0;
}
