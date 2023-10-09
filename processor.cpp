#include <stdio.h>
#include "comand_code.h"
#include "assembler.h"
#include "stack.h"
#include <cmath>

struct Vm_t {
    int n_comands = 0;    //
};

enum Arg_Indicator {
    ARG_END,
    ARG_INPUT,
    ARG_OUTPUT,
    ARG_INPUT_IN,
    ARG_ERROR
};

int Processing ( int command, Stack_Data_t *Stack );

int main ()
{
    Vm_t vm_spu = {};
    //Arg_Indicator Arg = {};
    Stack_Data_t Stack = {};
$
    Stack.str = StackCtor ( Stack.size_stack );

    StackDump ( Stack.str, INFORMATION , Stack.size_stack, Stack.capacity );

    Assembler ( &vm_spu.n_comands );

    FILE *file_f = fopen ( "code.txt", "r" );

    for ( int i = 0, arg_indicator = 0; i < vm_spu.n_comands * 2; ++i ) {
        if ( i % 2 == 0 ) {
            int command = 0;
            fscanf ( file_f, "%d", &command );
            arg_indicator = Processing ( command, &Stack );
        }
        else if ( i % 2 == 1 && arg_indicator == ARG_END ) {

            return -1;
        }
        else if ( i % 2 == 1 && arg_indicator != ARG_END ) {         // 4 1 -9
            char_t value = 0;
            fscanf ( file_f, SPECIFIER, &value );

            if ( arg_indicator == ARG_INPUT ) {
                StackPush( &Stack.str, value, &Stack.size_stack, &Stack.capacity );
            }
            else if ( arg_indicator == ARG_INPUT_IN ) {
                printf ( "input your value : " );
                scanf ( SPECIFIER, &value );
                StackPush( &Stack.str, value, &Stack.size_stack, &Stack.capacity );
            }
            else if ( arg_indicator == ARG_OUTPUT ) {
                //char_t temp = StackPop( Stack.str, &Stack.capacity ) StackPop( Stack.str, &Stack.capacity );
            }
            arg_indicator = 0;  // const
        }
        else {
            printf ( "Sorry, you are having some errors" );

            return -1;
        }
        StackDump ( Stack.str, INFORMATION , Stack.size_stack, Stack.capacity );
    }


    StackDump ( Stack.str, INFORMATION , Stack.size_stack, Stack.capacity );

    return 0;
}

int Processing ( int command, Stack_Data_t *Stack )
{
    int arg_indicator = 0;

    switch ( command ) {
        case PUSH : {
                arg_indicator = ARG_INPUT; // enum return value
            //StackPush( &Stack->str, value, &Stack.size_stack, Stack.capacity );
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
                char_t temp = (-1) * ( StackPop( Stack->str, &Stack->capacity ) - StackPop( Stack->str, &Stack->capacity ) );
                StackPush( &Stack->str, temp, &Stack->size_stack, &Stack->capacity );
            }
            break;
        case IN   :
            arg_indicator = ARG_INPUT_IN;
            break;
        case OUT  : {
                arg_indicator = ARG_OUTPUT;
                StackPop( Stack->str, &Stack->capacity );
                //printf ??
            }
            break;
        default   :
            arg_indicator = ARG_ERROR;
            break; //error
    }

    return arg_indicator;
}
