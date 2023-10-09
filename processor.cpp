#include "processor.h"

int main ()
{
    Vm_t Vm_spu = {};
    Stack_Data_t Stack = {};
$
    Stack.str = StackCtor ( Stack.size_stack );

    StackDump ( Stack.str, INFORMATION , Stack.size_stack, Stack.capacity );

    Assembler ( &Vm_spu.n_comands );

    FILE *file_f = fopen ( "code.txt", "r" );

    if ( Processor ( Vm_spu, &Stack, file_f ) == -1 ) {

        return -1;
    }

    StackDtor ( Stack.str, Stack.size_stack );

    StackDump ( Stack.str, INFORMATION , Stack.size_stack, Stack.capacity );

    return 0;
}

int Processing ( int command, Stack_Data_t *Stack, char_t value )
{
    int arg_indicator = 0;

    switch ( command ) {
        case PUSH : {
                arg_indicator = ARG_INPUT;
                StackPush( &Stack->str, value, &Stack->size_stack, &Stack->capacity );
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
        default   :
            arg_indicator = ARG_ERROR;
            break; //error
    }

    return arg_indicator;
}

int Processor ( Vm_t Vm_spu, Stack_Data_t *Stack, FILE * file_f )   // return error
{
    for ( int i = 0, arg_indicator = 0, command = 0; i < Vm_spu.n_comands * 2; ++i ) {
        char_t value = 0;
        fscanf ( file_f, "%d", &command );        //error
        fscanf ( file_f, SPECIFIER, &value );

        arg_indicator = Processing ( command, Stack, value );

        if ( arg_indicator == ARG_END ) {

            return -1;
        }

        StackDump ( Stack->str, INFORMATION , Stack->size_stack, Stack->capacity );
    }
}
