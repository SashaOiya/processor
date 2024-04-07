#include "assembler.h"

int main ( const int argc, const char* argv[] )
{
    struct Asm_t assembler = {};
    Stack_Ctor ( &assembler.stack );

    Error_t err_code = Assembler_Ctor ( &assembler.text, argv[1] );

    if ( err_code == NO_ERR ) {
        err_code = Assembler_Compile ( &assembler, argv[2] ); // extern write
    }

    // error handling

    Stack_Dtor ( &(assembler.stack) ); // to asm dtor
    Assembler_Dtor ( &(assembler.text) );

    return 0;
}
