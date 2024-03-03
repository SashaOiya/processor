#ifndef PROCESSOR
#define PROCESSOR

#include <stdio.h>
#include "comand_code.h"
//#include "assembler.h"
#include "stack.h"
#include <cmath>

struct Vm_t {
    int file_size = 0;
    elem_t *RAM   = {};
};

enum Arg_Indicator {
    ARG_END      = -1,
    ARG_INPUT    = 0,
    ARG_OUTPUT   = 1,
    ARG_INPUT_IN = 2,
    ARG_FUNC     = 3,
    ARG_ERROR    = 4
};

struct Register_t {
    struct reg {
        elem_t rx = 0;
    };
    struct reg arr[3] = {};
};

enum Register {
    RAX = 1,
    RBX = 2,
    RCX = 3
};

int Processor ( Vm_t Vm_spu, Stack_Data_t *Stack, FILE  *file_f, Register_t *Register );
int Processing ( int indificate, int *ip,
                 Stack_Data_t *Stack, Register_t *Register, int arg_indicator,
                 Stack_Data_t *Ret_Stack );
int GetFileSize ( FILE *f);

#endif // PROCESSOR
