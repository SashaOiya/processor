#ifndef PROCESSOR
#define PROCESSOR

#include <stdio.h>
#include "comand_code.h"
#include "assembler.h"
#include "stack.h"
#include <cmath>

struct Vm_t {
    int n_comands = 0;    //
};

enum Arg_Indicator {
    ARG_END      = -1,
    ARG_INPUT    = 0,
    ARG_OUTPUT   = 1,
    ARG_INPUT_IN = 2,
    ARG_FUNC     = 3,
    ARG_ERROR    = 4
};

int Processor ( Vm_t Vm_spu, Stack_Data_t *Stack, FILE * file_f, Register_t *Register, elem_t *buffer );
int Processing ( int command, Stack_Data_t *Stack, elem_t *value,
                 int registers, Register_t *Register, int *ip, int arg_indicator );
int GetFileSize ( FILE *f);

#endif // PROCESSOR
