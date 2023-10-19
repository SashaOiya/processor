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
    char_t rax = 0;
    char_t rbx = 0;
    char_t rcx = 0;
};

enum Register {
    RAX = 1,
    RBX = 2,
    RCX = 3
};

int Assembler ( int *n_comands );
int Compare ( char_t *otput_buffer, FILE *code, Comand_Code cc, char *start, float ptr_elements, int registerr );
int GetFileSize ( FILE * f );
int AsmDtor ( char *buffer, Line_t *line_array, FILE *comand_f );
int Split ( Text_t *Text, FILE *code_f, Comand_Code CC, char *buffer );

#endif // ASM
