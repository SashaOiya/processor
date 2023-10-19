#include "assembler.h"
#include "stack.h"

// 3 programs (.exe)
// argc argv
// binary



/*int main ()
{
    int n_comands = 0;

    Assembler ( &n_comands );

    return 0;
}     */

int Assembler ( int *n_comands )
{
    FILE *comand_f = fopen ( "start.txt", "r" );
    FILE *code_f   = fopen ( "code.txt", "wb" );

    Comand_Code CC = {};
    Text_t Text    = {};

    Text.file_size = GetFileSize ( comand_f );

    char *buffer = ( char *)calloc ( Text.file_size + 1, sizeof ( char ) );
    fread ( buffer, sizeof( buffer[0] ), Text.file_size, comand_f );    //return value
    buffer[Text.file_size] = '\n';

$   Split ( &Text, code_f, CC, buffer );

$   *n_comands = Text.n_lines;

    //AsmDtor ( buffer, Text.line_array, code_f );

    return Text.file_size;
}

int GetFileSize ( FILE * f )
{
    int prev = ftell ( f );

    fseek ( f, 0, SEEK_END );
    size_t sizet = ftell ( f );
    fseek ( f, prev, SEEK_SET );

    return sizet;
}

int Compare ( char_t *output_buffer, FILE *code, Comand_Code cc, char *start, float ptr_elements, int registerr )
{
$   for ( int i = 0; i < cc.n_comands; ++i ) {
$       if ( strcmp ( start, cc.arr[i].str ) == 0 ) {
$           fprintf ( code, "%d ", cc.arr[i].code );
            fprintf ( code, "%d ", registerr );
            fprintf ( code, "%g\n", ptr_elements );
            //output_buffer[0] = cc.arr[i].code;
$           //output_buffer[1] = registerr;
$           //output_buffer[2] = ptr_elements;
$
$           break;
        }
    }

$   return 0; // error code
}

int AsmDtor ( char *buffer, Line_t *line_array, FILE *comand_f )
{
    free(buffer);
    free(line_array);

    fclose ( comand_f ); //error
}

int Split ( Text_t *Text, FILE *code_f, Comand_Code CC, char *buffer )
{
    for ( int i = 0; i <= Text->file_size; ++i ) {
        if ( *( buffer + i ) == ';' || *( buffer + i ) == ':' ) {
            ++(Text->n_lines);
            *( buffer + i ) = '\0';
        }
    }

    Text->line_array = ( Line_t *)calloc ( Text->n_lines, sizeof ( Line_t) );
    char_t *output_buffer = ( char_t *)calloc( 3 *(Text->n_lines ), sizeof(char_t) );

    for ( int i = 0, j = 0; i < Text->n_lines; ++j, ++i ) {
        int len = 0;
        bool flag = false;
        while ( buffer[j] != '\0' ) {   // flag E space   '\n'
            if ( buffer[j] == ' ' ) {
                buffer[j] = '\0';
                flag = true;
                Text->line_array[i].start = buffer + j - len;
                if ( *( buffer + j + 1 ) == 'r' &&
                     *( buffer + j + 3 ) == 'x' &&
                     *( buffer + j + 4 ) == '\0' ) {
                    Text->line_array[i].registerr = *( buffer + j + 2 ) - 96;
                    Text->line_array[i].element = 0;
                }
                else {
                    Text->line_array[i].registerr = 0;
                    Text->line_array[i].element = ( char_t )atof ( buffer + j + 1 );
                }
            }
            else if ( buffer[j] != ' ' && flag == false ) {
                ++len;
            }
            ++j;
        }
        //buffer[j] = '\0';
        if ( flag == false ) {
            Text->line_array[i].start = buffer + j - len;
            Text->line_array[i].registerr = 0;
            Text->line_array[i].element = 0;  // wtf
        }
        while ( buffer[j] != '\n' ) {
            ++j;
        }
        Compare ( &output_buffer[i*3], code_f, CC, Text->line_array[i].start, Text->line_array[i].element, Text->line_array[i].registerr );
    }
    /*for ( int i = 0; i < Text->n_lines * 3; ++ i ) {
        printf ( "%g\n", output_buffer[i] );
    } */
    //fwrite ( output_buffer, sizeof(output_buffer[0]), Text->n_lines * 3, code_f );
}
