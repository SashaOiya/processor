#include "processor.h"
#include <ctype.h>


int main ()
{
    Vm_t Vm_spu = {};
    Stack_Data_t Stack  = {};
    Register_t Register = {};
$
    Stack.str = StackCtor ( Stack.size_stack );

    StackDump ( Stack.str, INFORMATION , Stack.size_stack, Stack.capacity );

    int file_size  = Assembler ( &Vm_spu.n_comands );

    FILE *file_f = fopen ( "code.txt", "rb" );
    char_t *RAM = (char_t*)calloc(file_size, sizeof ( char_t));

    for ( int j = 0; j < Vm_spu.n_comands * 2; ++j ) {
        fscanf ( file_f, "%g", &RAM[j*3+0] );        //error
        fscanf ( file_f, "%g", &RAM[j*3+1] );
        fscanf ( file_f, SPECIFIER, &RAM[j*3+2] );
    }
    /*for ( int i = 0; i < Vm_spu.n_comands * 3 ; ++i ) {
        printf ( "%g\n", RAM[i] );
    } */

    if ( Processor ( Vm_spu, &Stack, file_f, &Register, RAM ) == -1 ) {

        return -1;
    }

    StackDtor ( Stack.str, Stack.size_stack );

    //StackDump ( Stack.str, INFORMATION , Stack.size_stack, Stack.capacity );

    return 0;
}

int Processing ( int command, Stack_Data_t *Stack, char_t value, int registers, Register_t *Register, int *ip )
{
    int arg_indicator = 0;

    switch ( command ) {
        case POP  : {
            arg_indicator = ARG_OUTPUT;
            if ( registers == RAX ) {
                Register->rax = StackPop( Stack->str, &Stack->capacity );
            }
            else if ( registers == RBX ) {
                Register->rbx = StackPop( Stack->str, &Stack->capacity );
            }
            else if ( registers == RCX ) {
                Register->rcx = StackPop( Stack->str, &Stack->capacity );
            }
            }
            break;
        case PUSH : {
            arg_indicator = ARG_INPUT;
            if ( registers == RAX ) {
                StackPush( &Stack->str, Register->rax, &Stack->size_stack, &Stack->capacity );
            }
            else if ( registers == RBX ) {
                 StackPush( &Stack->str, Register->rbx, &Stack->size_stack, &Stack->capacity );
            }
            else if ( registers == RCX ) {
                 StackPush( &Stack->str, Register->rcx, &Stack->size_stack, &Stack->capacity );
            }
            else {
                StackPush( &Stack->str, value, &Stack->size_stack, &Stack->capacity );
            }
            }
            break;
        case HLT  :
            arg_indicator = ARG_END;
            break;
        case ADD  : {
                arg_indicator = ARG_OUTPUT;
                char_t temp = StackPop( Stack->str, &Stack->capacity ) + StackPop( Stack->str, &Stack->capacity );
                StackPush( &Stack->str, temp, &Stack->size_stack, &Stack->capacity );
            }
            break;
        case MUL : {
                arg_indicator = ARG_OUTPUT;
                char_t temp = StackPop( Stack->str, &Stack->capacity ) * StackPop( Stack->str, &Stack->capacity );
                StackPush( &Stack->str, temp, &Stack->size_stack, &Stack->capacity );
            }
            break;
        case SQRT : {
                arg_indicator = ARG_OUTPUT;
                char_t temp = StackPop( Stack->str, &Stack->capacity );
                StackPush( &Stack->str, sqrt ( temp ), &Stack->size_stack, &Stack->capacity );
            }
            break;
        case SIN  : {
                arg_indicator = ARG_OUTPUT;
                char_t temp = StackPop( Stack->str, &Stack->capacity );
                StackPush( &Stack->str, sin ( temp ), &Stack->size_stack, &Stack->capacity );
            }
            break;
        case COS  : {
                arg_indicator = ARG_OUTPUT;
                char_t temp = StackPop( Stack->str, &Stack->capacity );
                StackPush( &Stack->str, cos ( temp ), &Stack->size_stack, &Stack->capacity );
            }
            break;
        case DIV  : {
                arg_indicator = ARG_OUTPUT;
                char_t temp = StackPop( Stack->str, &Stack->capacity ) / StackPop( Stack->str, &Stack->capacity );
                StackPush( &Stack->str, temp, &Stack->size_stack, &Stack->capacity );
            }
            break;
        case SUB  : {
                arg_indicator = ARG_OUTPUT;
                char_t a = StackPop( Stack->str, &Stack->capacity );
                char_t b = StackPop( Stack->str, &Stack->capacity );
                char_t temp = b - a;
                StackPush( &Stack->str, temp, &Stack->size_stack, &Stack->capacity );
            }
            break;
       case IN   : {
                arg_indicator = ARG_INPUT_IN;
                char_t value = 0;
                printf ( "input your value : " );
                scanf ( SPECIFIER, &value );
                StackPush( &Stack->str, value, &Stack->size_stack, &Stack->capacity );
            }
            break;
       case OUT  : {
                arg_indicator = ARG_OUTPUT;
                StackPop( Stack->str, &Stack->capacity );
                //printf ??
            }
            break;
       case START: {
        //printf ( "ip %d\n", *ip );
                arg_indicator = ARG_OUTPUT;
                Register->rbx = (*ip + 1 ) * 3;//
                //printf ( "%g\n", Register->rbx );
            }
           break;
       case JMP : {
               arg_indicator = ARG_OUTPUT;
                *ip = (int) (Register->rbx) / 3;
            }
            break;
       default :
            arg_indicator = ARG_ERROR;
            break; //error
    }

    return arg_indicator;
}

int Processor ( Vm_t Vm_spu, Stack_Data_t *Stack, FILE * file_f, Register_t *Register, char_t *RAM )   // return error
{
    for ( int j = 0, arg_indicator = 0; j < Vm_spu.n_comands * 2; ++j ) {

        //printf ( "%g\n", RAM[j*3] );

        arg_indicator = Processing ( RAM[j*3+0], Stack, RAM[j*3+2], RAM[j*3+1], Register, &j );

        if ( arg_indicator == ARG_END ) {

            return -1;
        }

        StackDump ( Stack->str, INFORMATION , Stack->size_stack, Stack->capacity );
    }
}
