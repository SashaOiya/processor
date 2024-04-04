#include "processor.h"

int main ( const int argc, const char* argv[] )
{
    Vm_t vm_spu = {};

    if ( ( vm_spu.ret_error = Processor_Ctor ( &vm_spu, argv[1] ) ) == NO_ERR ) {
        if ( (  vm_spu.ret_error = Processor ( &vm_spu ) ) != NO_ERR ) {
            // verificator
            Stack_Dtor ( &(vm_spu.stack) );

            return -1;
        }
    }

    return 0;
}

Error_t Processor_Ctor ( struct Vm_t *vm_spu, const char *encode_file )
{
    assert ( vm_spu != nullptr );
    assert ( encode_file != nullptr );

    Stack_Ctor ( &(vm_spu->stack) );

    FILE *code_f = fopen ( encode_file, "rb" );
    if ( !code_f ) {
        perror ( "File opening failed" );
        Stack_Dtor ( &(vm_spu->stack) );

        return F_OPEN_ERR;
    }

    vm_spu->file_size = GetFileSize ( code_f ) / sizeof ( elem_t ) + 1; // !?

    vm_spu->RAM = (elem_t *)calloc ( vm_spu->file_size, sizeof ( elem_t ) );
    if ( !vm_spu->RAM ) {

        return MEMMORY_ERR;
    }
    int ret_code = fread ( vm_spu->RAM, sizeof ( elem_t ), vm_spu->file_size, code_f );
    if ( ret_code != vm_spu->file_size ) {
        if ( feof ( code_f ) ) {
            printf ( "Error reading %s: unexpected end of file\n", encode_file );
        }
        else if ( ferror ( code_f ) ) {
            perror ( "Error reading command_file\n" );
        }
        fclose ( code_f );

        return F_READ_ERR;
    }
    fclose ( code_f );

    return NO_ERR;
}


//FIXME separate file
//int Processing ( int indificate, int *ip, Stack_t *Stack, Register_t *Register,
//                 int arg_indicator, Stack_t *Ret_Stack )
//arg_indicator = Processing ( vm_spu->RAM[ip], &ip,
//                                    &(vm_spu->stack), &(vm_spu->registers), arg_indicator, &new_stack );
int Processing ( struct Vm_t *vm_spu, int *ip, int arg_indicator, Stack_t *Ret_Stack )
{
    assert ( Ret_Stack != nullptr );

    int command   = ( vm_spu->RAM[*ip] >> 0  ) & ~( ~0 << 5  ); // 0b11111; //FIXME command mask
    int registers = ( vm_spu->RAM[*ip] >> 5  ) & ~( ~0 << 15 );
    elem_t value  = ( vm_spu->RAM[*ip] >> 20 ) & ~( ~0 << 15 ); // why 12

    // command -> value -> reg
    switch ( command ) {
        case POP  : {
            Register->arr[registers].rx = Stack_Pop( Stack );
            break;
        }
        case PUSH : {
            if ( registers != 0 ) { //
                Stack_Push( Stack, Register->arr[registers].rx );
            }
            else {
                Stack_Push( Stack, value );
            }
            break;
        }
        case HLT  : {
            arg_indicator = ARG_END;
            }
            break;
        case ADD  : {
                elem_t temp = Stack_Pop( Stack ) + Stack_Pop( Stack );
                Stack_Push( Stack, temp );
            }
            break;
        case MUL : {
                elem_t temp = Stack_Pop( Stack ) * Stack_Pop( Stack );
                Stack_Push( Stack, temp );
            }
            break;
        case SQRT : {
                elem_t temp = Stack_Pop( Stack );
                Stack_Push( Stack, sqrt ( temp ) );
            }
            break;
        case SIN  : {
                elem_t temp = Stack_Pop( Stack );
                Stack_Push( Stack, sin ( temp ) );
            }
            break;
        case COS  : {
                elem_t temp = Stack_Pop( Stack );
                Stack_Push( Stack, cos ( temp ) );
            }
            break;
        case DIV  : {
                elem_t temp = Stack_Pop( Stack ) / Stack_Pop( Stack ); // div 0
                Stack_Push( Stack, temp );
            }
            break;
        case SUB  : {
                elem_t a = Stack_Pop( Stack );
                elem_t b = Stack_Pop( Stack );
                elem_t temp = a - b;
                Stack_Push( Stack, temp );
            }
            break;
       case IN   : {
                elem_t temp = 0;
                printf ( "input your value : " );
                scanf ( SPECIFIER, &temp );
                Stack_Push( Stack, temp );
            }
            break;
       case OUT  : {
                Stack_Pop( Stack );
            }
            break;
       case JMP : {
                printf ( "registers %d", registers );
                *ip = registers; // -1
            }
            break;
        case JA : {
                elem_t temp_1 = Stack_Pop ( Stack );
                elem_t temp_2 = Stack_Pop ( Stack );
                if ( temp_1 > temp_2 ) {
                    *ip = registers - 1;
                }
            }
            break;
        case JAE : {
                elem_t temp_1 = Stack_Pop( Stack );
                elem_t temp_2 = Stack_Pop ( Stack );
                if ( temp_1 >= temp_2 ) {
                    *ip = registers - 1;
                }
            }
            break;
        case JNE : {
                elem_t temp_1 = Stack_Pop( Stack );
                elem_t temp_2 = Stack_Pop ( Stack );
                if ( temp_1 != temp_2 ) {
                    *ip = registers - 1;
                }
            }
            break;
        case JE : {
                elem_t temp_1 = Stack_Pop( Stack );
                elem_t temp_2 = Stack_Pop ( Stack );
                if ( temp_1 == temp_2 ) {
                    *ip = registers - 1;
                }
            }
            break;
        case JB : {
                elem_t temp_1 = Stack_Pop ( Stack );
                elem_t temp_2 = Stack_Pop ( Stack );
                if ( temp_1 < temp_2 ) {
                    *ip = registers - 1;
                }
            }
            break;
        case JBE : {
                elem_t temp_1 = Stack_Pop( Stack );
                elem_t temp_2 = Stack_Pop ( Stack );
                if ( temp_1 <= temp_2 ) {
                    *ip = registers - 1;
                }
            }
            break;
        case RET : {
                *ip = Stack_Pop( Ret_Stack );
                printf ( "%d\n", *ip);
            }
            break;
        case CALL : {
$               Stack_Push( Ret_Stack, *ip );
$               *ip = registers - 1;
            }
            break;
       default : {
            arg_indicator = ARG_ERROR;
            }
            break; //error
    }

    return arg_indicator;
}

Error_t Processor ( struct Vm_t *vm_spu )   // return error
{
    assert ( vm_spu != nullptr );

    int max_ip = vm_spu->file_size * sizeof ( elem_t );

    Stack_t new_stack  = {};
    Stack_Ctor ( &ret_stack );

    for ( int ip = 0, arg_indicator = 0; ip < max_ip; ++ip ) {

        arg_indicator = Processing ( vm_spu->RAM[ip], &ip,
                                    &(vm_spu->stack), &(vm_spu->registers), arg_indicator, &new_stack );
        if ( arg_indicator == ARG_END ) {

            return NO_ERR; // break;
        }
        Stack_Dump ( &(vm_spu->stack), INFORMATION );
    }

    Stack_Dtor ( &new_stack );  // to dtor

    return NO_ERR;
}
