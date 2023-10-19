#include "processor.h"

int main ()
{
    Vm_t Vm_spu = {};
    Stack_Data_t Stack  = {};
    Register_t Register = {};
$
    Stack.str = StackCtor ( Stack.size_stack );

    StackDump ( Stack.str, INFORMATION , Stack.size_stack, Stack.capacity );

    const int file_size = Assembler ( &Vm_spu.n_comands );     //
    int sum_start = StackHash ( &Stack );

    char_t *buffer = (char_t*)calloc(file_size, sizeof ( char_t));  //
    FILE *file_f = fopen ( "code.txt", "r" );
    /*fread ( buffer, sizeof( buffer[0] ), file_size, file_f );    //return value

    for ( int i = 0; i < Vm_spu.n_comands * 3; ++ i ) {
        printf ( SPECIFIER, buffer[i] );
    }   */
    //buffer[file_size] = '\n';

    if ( Processor ( Vm_spu, &Stack, buffer, &Register, &sum_start, file_f ) == -1 ) {   // - sum-start

        return -1;
    }

    StackDtor ( Stack.str, Stack.size_stack );

    //StackDump ( Stack.str, INFORMATION , Stack.size_stack, Stack.capacity );

    return 0;
}

int Processing ( int command, Stack_Data_t *Stack, char_t value, int registers, Register_t *Register )
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

int Processor ( Vm_t Vm_spu, Stack_Data_t *Stack, char_t *buffer, Register_t *Register, int *sum_start, FILE * file_f )   // return error
{
    int error_indicator = 0;

    //int sum = StackHash ( Stack );

    for ( int i = 0, arg_indicator = 0, command = 0, registers = 0; i < Vm_spu.n_comands * 2; ++i ) {
        //Verificator ( Stack, &error_indicator, &sum );

        char_t value = 0;
        fscanf ( file_f, "%d", &command );        //error
        //command = ((int*)buffer)[i+0];
        printf ( "%d\n", command );
        fscanf ( file_f, "%d", &registers );
        //registers = buffer[i+1];
        fscanf ( file_f, SPECIFIER, &value );
        //value = buffer[i+2];

        arg_indicator = Processing ( command, Stack, value, registers, Register );

        if ( arg_indicator == ARG_END ) {

            return -1;
        }

        //StackDump ( Stack->str, INFORMATION , Stack->size_stack, Stack->capacity );
    }

    return 0;//
}
