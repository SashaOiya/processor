#include <stdio.h>
#include <assert.h>

int main()
{
    int value = 0xff;

    char opcode = 0x1;
    FILE* file = fopen("test.out", "wb");
    assert(file);

    //calloc
    //
    fwrite(&opcode, sizeof(opcode), 1, file);
    fwrite(&value, sizeof(value), 1, file);
    value = 0x11;
    opcode = 0x2;
    fwrite(&opcode, sizeof(opcode), 1, file);
    fwrite(&value, sizeof(value), 1, file);
    value = 0x10;
    opcode = 0x03;
    fwrite(&opcode, sizeof(opcode), 1, file);
    fwrite(&value, sizeof(value), 1, file);

    fclose(file);
    file = fopen("test.out", "rb");
    assert(file);


    char buf[3 * (sizeof(opcode) + sizeof(value))] = {0};

    fread(buf, 1, sizeof(buf), file);

    opcode = buf[0];
    char *fr = buf + 1;
    value = *(int*)(fr);

    printf( "opcode = 0x%x\n", opcode);
    printf( "valuee = 0x%x\n", value);
    //fread();

    return 0;
}
