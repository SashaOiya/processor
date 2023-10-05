#include "compil.h"

FILE* assembler ()
{
    FILE *comand_f = fopen ( "start.txt", "r" );
    FILE *code_f   = fopen ( "code.txt", "w" );

    Comand_Code CC = {};
    Text_t Text    = {};

    Text.file_size = GetFileSize ( comand_f );

    char *buffer = ( char *)calloc ( Text.file_size + 1, sizeof ( char ) );
    fread ( buffer, sizeof( buffer[0] ), Text.file_size, comand_f );    //return value
    buffer[Text.file_size] = '\n';

    int n_lines = 0;

    for ( int i = 0; i <= Text.file_size; ++i ) {
        if ( *( buffer + i ) == '\n' ) {
            ++n_lines;
            *( buffer + i ) = '\0';
        }
    }

    char **start = (char **)calloc ( n_lines, sizeof ( char *) );
    float *ptr_elements = (float *)calloc ( n_lines, sizeof ( float ) );

    for ( int i = 0, j = 0; i < n_lines; ++j, ++i ) {
        int len = 0;
        bool flag = false;
        while ( buffer[j] != '\0' ) {   // flag E space   '\n'
            if ( buffer[j] == ' ' ) {
                buffer[j] = '\0';
                flag = true;
                start[i] = buffer + j - len;
                ptr_elements[i] = ( float )atof ( buffer + j + 1 );
            }
            else if ( buffer[j] != ' ' && flag == false ) {
                ++len;
            }
            ++j;
        }
        if ( flag == false ) {
            start[i] = buffer + j - len;
        }
        Compare ( code_f, CC, start[i], ptr_elements[i] );
    }

    free(buffer);
    free(start);
    free(ptr_elements);

    fclose ( comand_f );

    return code_f;
}

int GetFileSize ( FILE * f )
{
    int prev = ftell ( f );

    fseek ( f, 0, SEEK_END );
    size_t sizet = ftell ( f );
    fseek ( f, prev, SEEK_SET );

    return sizet;
}

int Compare ( FILE *code, Comand_Code cc, char *start, float ptr_elements )
{
$   for ( int i = 0; i < cc.n_comands; ++i ) {
$       if ( strcmp ( start, cc.arr[i].str ) == 0 ) {
$           fprintf ( code, "%d ", cc.arr[i].code );
            fprintf ( code, "%g\n", ptr_elements );
$
$           break;
        }
    }

$   return 0; // error code
}

int AsmCtor ()
{

}
