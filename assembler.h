#ifndef ASM
#define ASM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comand_code.h"
#include "stack.h"

//typedef float char_t;

#ifdef DEBUG
#define $ fprintf (stderr, "%d\n", __LINE__ );
#else
#define $
#endif

struct Line_t {
    char *start  = nullptr;
    float element = 0;
    int registerr = 0;
};

struct Text_t {
    int file_size = 0;
    Line_t * line_array;
    int n_lines = 0;
};

struct Register_t {
    char_t rax =  0;
    char_t rbx =  0;
    char_t rcx =  0;
    char_t rdx = -1;
};

enum Register {
    RAX = 1,
    RBX = 2,
    RCX = 3
};

void Assembler ( );
int Compare ( Comand_Code cc, Line_t line_array, Stack_Data_t *Stack );
int GetFileSize ( FILE * f );
int AsmDtor ( char *buffer, Line_t *line_array, FILE *comand_f );
int Split ( Text_t *Text, char *buffer );

#endif // ASM
