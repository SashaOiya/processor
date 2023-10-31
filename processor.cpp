#include "processor.h"
#include <ctype.h>
#include <assert.h>


int main ()
{
    Vm_t Vm_spu = {};
    Stack_Data_t Stack  = {};
    Register_t Register = {};
$
    Stack.str = StackCtor ( Stack.size_stack );

    FILE *file_f = fopen ( "code.txt", "rb" );
    int file_size = GetFileSize ( file_f ) / 4 + 1;
    Vm_spu.n_comands = ( file_size - 1 ) / 3;

    elem_t *RAM = (elem_t *)calloc(file_size, sizeof ( elem_t ) );
    //fclose ( file_f2 );
    assert ( RAM != nullptr );

    fread ( RAM, sizeof( elem_t ), Vm_spu.n_comands * 3, file_f );
    assert ( RAM != nullptr );
    /*for ( int i = 0; i < Vm_spu.n_comands * 3 ; ++i ) {
        printf ( "%g\n", RAM[i] );
    }  */

    if ( Processor ( Vm_spu, &Stack, file_f, &Register, RAM ) == -1 ) {

        return -1;
    }

    StackDtor ( Stack.str, Stack.size_stack );

    //StackDump ( Stack.str, INFORMATION , Stack.size_stack, Stack.capacity );

    return 0;
}

int GetFileSize ( FILE * f )
{
    int prev = ftell ( f );

    fseek ( f, 0, SEEK_END );
    size_t sizet = ftell ( f );
    fseek ( f, prev, SEEK_SET );

    return sizet;
}

int Processing ( int command, Stack_Data_t *Stack, elem_t *value, int registers, Register_t *Register, int *ip, int arg_indicator )
{
    //int arg_indicator = 0;

    switch ( command ) {
        case POP  : {
            //arg_indicator = ARG_OUTPUT;
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
            //arg_indicator = ARG_INPUT;
            if ( registers == RAX ) {
                StackPush( Stack, Register->rax );
            }
            else if ( registers == RBX ) {
                 StackPush( Stack, Register->rbx );
            }
            else if ( registers == RCX ) {
                 StackPush( Stack, Register->rcx );
            }
            else {
                StackPush( Stack, *value );
            }
            }
            break;
        case HLT  : {
            arg_indicator = ARG_END;
            }
            break;
        case ADD  : {
                //arg_indicator = ARG_OUTPUT;
                elem_t temp = StackPop( Stack->str, &Stack->capacity ) + StackPop( Stack->str, &Stack->capacity );
                StackPush( Stack, temp );
            }
            break;
        case MUL : {
                //arg_indicator = ARG_OUTPUT;
                elem_t temp = StackPop( Stack->str, &Stack->capacity ) * StackPop( Stack->str, &Stack->capacity );
                StackPush( Stack, temp );
            }
            break;
        case SQRT : {
                //arg_indicator = ARG_OUTPUT;
                elem_t temp = StackPop( Stack->str, &Stack->capacity );
                StackPush( Stack, sqrt ( temp ) );
            }
            break;
        case SIN  : {
                //arg_indicator = ARG_OUTPUT;
                elem_t temp = StackPop( Stack->str, &Stack->capacity );
                StackPush( Stack, sin ( temp ) );
            }
            break;
        case COS  : {
                //arg_indicator = ARG_OUTPUT;
                elem_t temp = StackPop( Stack->str, &Stack->capacity );
                StackPush( Stack, cos ( temp ) );
            }
            break;
        case DIV  : {
                //arg_indicator = ARG_OUTPUT;
                elem_t temp = StackPop( Stack->str, &Stack->capacity ) / StackPop( Stack->str, &Stack->capacity );
                StackPush( Stack, temp );
            }
            break;
        case SUB  : {
                //arg_indicator = ARG_OUTPUT;
                elem_t a = StackPop( Stack->str, &Stack->capacity );
                elem_t b = StackPop( Stack->str, &Stack->capacity );
                elem_t temp = b - a;
                StackPush( Stack, temp );
            }
            break;
       case IN   : {
                //arg_indicator = ARG_INPUT_IN;
                elem_t value = 0;
                printf ( "input your value : " );
                scanf ( SPECIFIER, &value );
                StackPush( Stack, value );
            }
            break;
       case OUT  : {
                //arg_indicator = ARG_OUTPUT;
                StackPop( Stack->str, &Stack->capacity );
            }
            break;
       case JMP : {
                *ip = registers;
            }
            break;
        /*case JA : {
                if ( Register->rdx == 0 ) {
                    arg_indicator = ARG_OUTPUT;   //rdx
                }
                else if ( arg_indicator != ARG_FUNC ) {
                    arg_indicator = ARG_FUNC;
                    *ip = (int) (Register->rbx) / 3 + 1;
                    Register->rdx = value - 1 ;
                }
                else {
                    arg_indicator = ARG_FUNC;
                    *ip = (int) (Register->rbx) / 3 + 1;
                    Register->rdx = Register->rdx - 1;
                }
            }
            break;  */
        case RET : {
                if ( *value == 0 ) {
                    *value += 1;
                }
                else {
                    *ip = registers;
                }
            }
            break;
        case CALL : {
                *ip = registers;
            }
            break;
       default :
            arg_indicator = ARG_ERROR;
            break; //error
    }

    return arg_indicator;
}

int Processor ( Vm_t Vm_spu, Stack_Data_t *Stack, FILE * file_f, Register_t *Register, elem_t *RAM )   // return error
{
    for ( int j = 0, arg_indicator = 0; j < Vm_spu.n_comands; ++j ) {

        //printf ( "%g\n", RAM[j*3] );

        arg_indicator = Processing ( RAM[j*3+0], Stack, &RAM[j*3+2], RAM[j*3+1], Register, &j, arg_indicator );

        if ( arg_indicator == ARG_END ) {

            return -1;
        }

        StackDump ( *Stack, INFORMATION );
    }
}
