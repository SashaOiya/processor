#include "processor.h"
#include <ctype.h>
#include <assert.h>


int main ( int argc, char* argv[] )
{
    Vm_t Vm_spu = {};
    Stack_Data_t Stack  = {};
    Register_t Register = {};
$
    StackCtor ( &Stack );

    FILE *file_f = fopen ( argv[1], "rb" );
    // err

    Vm_spu.file_size = GetFileSize ( file_f ) / sizeof ( elem_t ) + 1; // !?

    Vm_spu.RAM = (elem_t *)calloc( Vm_spu.file_size, sizeof ( elem_t ) );
    // err not enough memory
    assert ( Vm_spu.RAM != nullptr );

    fread ( Vm_spu.RAM, sizeof ( elem_t ), Vm_spu.file_size, file_f );
    assert ( Vm_spu.RAM != nullptr );
    // err

    if ( Processor ( Vm_spu, &Stack, file_f, &Register ) == -1 ) { // magic numberr

        StackDtor ( &Stack );

        return 0; // what?
    }
    //error

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

int Processing ( int command, int registers, elem_t *value, int *ip,
                 Stack_Data_t *Stack, Register_t *Register, int arg_indicator,
                 Stack_Data_t *Ret_Stack )
{
    assert ( Ret_Stack != nullptr );
    switch ( command ) {
        case POP  : {
            //arg_indicator = ARG_OUTPUT;
            if ( registers == RAX ) {
                Register->rax = StackPop( Stack );
            }
            else if ( registers == RBX ) {
                Register->rbx = StackPop( Stack );
            }
            else if ( registers == RCX ) {
                Register->rcx = StackPop( Stack );
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
                elem_t temp = StackPop( Stack ) + StackPop( Stack );
                StackPush( Stack, temp );
            }
            break;
        case MUL : {
                //arg_indicator = ARG_OUTPUT;
                elem_t temp = StackPop( Stack ) * StackPop( Stack );
                StackPush( Stack, temp );
            }
            break;
        case SQRT : {
                //arg_indicator = ARG_OUTPUT;
                elem_t temp = StackPop( Stack );
                StackPush( Stack, sqrt ( temp ) );
            }
            break;
        case SIN  : {
                //arg_indicator = ARG_OUTPUT;
                elem_t temp = StackPop( Stack );
                StackPush( Stack, sin ( temp ) );
            }
            break;
        case COS  : {
                //arg_indicator = ARG_OUTPUT;
                elem_t temp = StackPop( Stack );
                StackPush( Stack, cos ( temp ) );
            }
            break;
        case DIV  : {
                //arg_indicator = ARG_OUTPUT;
                elem_t temp = StackPop( Stack ) / StackPop( Stack );
                StackPush( Stack, temp );
            }
            break;
        case SUB  : {
                //arg_indicator = ARG_OUTPUT;
                elem_t a = StackPop( Stack );
                elem_t b = StackPop( Stack );
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
                StackPop( Stack );
            }
            break;
       case JMP : {
                *ip = registers - 3 * sizeof(elem_t);
            }
            break;
        case JA : {
                elem_t temp = StackPop( Stack );
                StackPush( Stack, temp );
                if ( temp > *value ) {
                    *ip = registers;
                }
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
                *ip = StackPop( Ret_Stack );
                printf ( "%d\n", *ip);
            }
            break;
        case CALL : {
$               StackPush( Ret_Stack, *ip );
                printf ( "PUSH %d\n", *ip );
$               *ip = registers - 3 * sizeof ( elem_t );
            }
            break;
       default :
            arg_indicator = ARG_ERROR;
            break; //error
    }

    return arg_indicator;
}

int Processor ( Vm_t Vm_spu, Stack_Data_t *Stack, FILE * file_f, Register_t *Register )   // return error
{
    int end_ip = Vm_spu.file_size * sizeof ( elem_t );

    Stack_Data_t Ret_Stack  = {};
    StackCtor ( &Ret_Stack );


    for ( int ip = 0, arg_indicator = 0; ip < end_ip;  ) {

        arg_indicator = Processing ( Vm_spu.RAM[ip/sizeof(elem_t)    ],
                                     Vm_spu.RAM[ip/sizeof(elem_t) + 1],
                                    &Vm_spu.RAM[ip/sizeof(elem_t) + 2], &ip,
                                    Stack, Register, arg_indicator, &Ret_Stack );
        //int arr[10];

        //ip = 8
        //(char*)arr + ip
        //arr[ip] = *(arr + ip) = ip[arr]
        // �������� ����������
        if ( arg_indicator == ARG_END ) {

            return -1; // magic numberr
        }
        ip += 3 * sizeof ( elem_t ); // magic numberr

        StackDump ( *Stack, INFORMATION );
    }

    StackDtor ( &Ret_Stack );
}
