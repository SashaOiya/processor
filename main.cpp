#include <stdio.h>
#include "comand_code.h"
#include "compil.h"
#include "stack.h"

struct Vm_t {
    int n_comands = 0;
};

enum Arg_Indicator {
    ARG_END,
    ARG_INPUT,
    ARG_OUTPUT,
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
    char_t *arg_array = (char_t *)calloc ( vm_spu.n_comands * 2, sizeof ( char_t ) );

    for ( int i = 0, arg_indicator = 0, j = 0; i < vm_spu.n_comands * 2; ++i ) {
        if ( i % 2 == 0 ) {
            int command = 0;
            fscanf ( file_f, "%d", &command );
            arg_indicator = Processing ( command, &Stack );
        }
        else if ( i % 2 == 1 && arg_indicator != ARG_END ) {
            char_t value = 0;   // const
            fscanf ( file_f, SPECIFIER, &value );

            if ( arg_indicator == ARG_INPUT ) {
                StackPush( &Stack.str, value, &Stack.size_stack, &Stack.capacity );
            }
            else if ( arg_indicator == ARG_OUTPUT ) {
                //char_t temp = StackPop( Stack.str, &Stack.capacity ) StackPop( Stack.str, &Stack.capacity );
            }
            arg_indicator = 0;  // const
        }
        //printf ( "%g\n", arg_array[i] );
        StackDump ( Stack.str, INFORMATION , Stack.size_stack, Stack.capacity );
    }
    StackDump ( Stack.str, INFORMATION , Stack.size_stack, Stack.capacity );

    return 0;
}

char_t Processing ( int command, Stack_Data_t *Stack )
{
    int arg_indicator = 0;

    switch ( command ) {
        case PUSH :
            arg_indicator = ARG_INPUT; // enum return value
            //StackPush( &Stack->str, value, &Stack.size_stack, Stack.capacity );
            break;
        case HLT  :
            arg_indicator = ARG_END;
            break;
        case ADD  :
            arg_indicator = ARG_OUTPUT;
            //--(Stack->capacity);
            //char_t temp = 0;

            break;
        case MUL :
            {
            arg_indicator = ARG_OUTPUT;
            char_t temp = StackPop( Stack->str, &Stack->capacity ) * StackPop( Stack->str, &Stack->capacity );
            StackPush( &Stack->str, temp, &Stack->size_stack, &Stack->capacity );
            }
            break;
        case SQRT :
            arg_indicator = ARG_OUTPUT;
            break;
        case SIN  :
            arg_indicator = ARG_OUTPUT;
            break;
        case COS  :
            arg_indicator = ARG_OUTPUT;
            break;
        case DIV  :
            arg_indicator = ARG_OUTPUT;
            break;
        case SUB  :
            arg_indicator = ARG_OUTPUT;
            break;
        case IN   :
            arg_indicator = ARG_INPUT;
            break;
        case OUT  :
            arg_indicator = ARG_OUTPUT;
            break;
        default :
            arg_indicator = ARG_ERROR;
            break; //error
    }

    return arg_indicator;
}
