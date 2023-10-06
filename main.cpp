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
    float *arg_array = ( float *)calloc ( vm_spu.n_comands * 2, sizeof ( float ) );

    for ( int i = 0, arg_indicator = 0, j = 0; i < vm_spu.n_comands * 2; ++i ) {
        if ( i % 2 == 0 ) {
            float command = 0;
            fscanf ( file_f, "%g", &command );
            printf ("%g\t%d\n", command, i );
            /*++Stack.capacity;
            //printf ( "capacity %d\n", Stack.capacity );
            //arg_indicator = Processing ( command, &Stack );   // arg flag
            //StackPush ( ( void **)&Stack.str, command, &Stack.size_stack, Stack.capacity, sizeof ( float ) );
            if ( Stack.capacity == Stack.size_stack ) {

                Stack.size_stack = 2 * (Stack.size_stack);

                float *ptr_begine = (float *)calloc ( Stack.size_stack * sizeof ( float ) + sizeof(long long) * 2, sizeof ( float ) );   //free

                float *ptr = ptr_begine + sizeof ( long long );

                memset ( ptr, 0, Stack.size_stack * sizeof ( float ) ); // ptr + capacity

                memcpy ( ptr, Stack.str, i * sizeof ( float ) );

                Stack.str = ptr;
$           }
$           *( Stack.str + i * sizeof ( float ) ) = command; */
        }
        else if ( i % 2 == 1 && arg_indicator != ARG_END ) {
            float value = 0;   // const
            fscanf ( file_f, "%g\n", &value );

            if ( arg_indicator == ARG_INPUT ) {
                //StackPush ( ( void **)&Stack.str, value, &Stack.size_stack, Stack.capacity, sizeof ( float ) );
            }
            else if ( arg_indicator == ARG_OUTPUT ) {
                //StackPop( );
            }
            arg_indicator = 0;  // const
        }
        //printf ( "%g\n", arg_array[i] );
    }
    StackDump ( Stack.str, INFORMATION , Stack.size_stack, Stack.capacity );

    return 0;
}

int Processing ( int command, Stack_Data_t *Stack )
{
    int arg_indicator = 0;

    switch ( command ) {
        case PUSH :
            arg_indicator = ARG_INPUT; // enum return value
            //Push();
            break;
        case HLT  :
            arg_indicator = ARG_END;
            break;
        case ADD  :
            arg_indicator = ARG_OUTPUT;
            break;
        case MUL  :
            arg_indicator = ARG_OUTPUT;
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
