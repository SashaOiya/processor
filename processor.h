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
    ARG_END     ,
    ARG_INPUT   ,
    ARG_OUTPUT  ,
    ARG_INPUT_IN,
    ARG_ERROR
};

int Processor ( Vm_t Vm_spu, Stack_Data_t *Stack, FILE * file_f, Register_t *Register, char_t *buffer );
int Processing ( int command, Stack_Data_t *Stack, char_t value, int registers, Register_t *Register, int *ip );

#endif // PROCESSOR
