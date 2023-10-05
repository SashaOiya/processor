#ifndef ASM
#define ASM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comand_code.h"

#ifdef DEBUG
#define $ printf ( "%d\n", __LINE__ );
#else
#define $
#endif

struct Text_t {
    int file_size = 0;
    char *start = nullptr;
};

FILE* assembler ();
int Compare ( FILE *code, Comand_Code cc, char *start, float ptr_elements );
int GetFileSize ( FILE * f );

#endif // ASM
