#include "assembler.h"

void Get_Pointer ( int *labels_array, char *buffer, Text_t *Text, Comand_Code CC, int *ip );

int main ( int argc, char* argv[] )
{
    FILE *comand_f = fopen ( argv[1], "rb" );
    assert ( comand_f != nullptr );

    Text_t Text = {};
    Text.file_size = GetFileSize ( comand_f );

    char *buffer = ( char *)calloc ( Text.file_size + 1, sizeof ( char ) );
    assert ( buffer != nullptr );

    int ret_code = fread ( buffer, sizeof( buffer[0] ), Text.file_size, comand_f );
    if ( ret_code != Text.file_size ) {
        if ( feof ( comand_f ) ) {
            printf("Error reading test.bin: unexpected end of file\n");
        }
        else if ( ferror ( comand_f ) ) {
            perror("Error reading test.bin");
        }
    }
    buffer[Text.file_size] = '\n';

    Asm_Compile ( &Text, buffer, argv[2] );

    //AsmDtor ( buffer, Text.line_array, code_f );

    return 0;
}

int GetFileSize ( FILE * f )
{
    int prev = ftell ( f );

    fseek ( f, 0, SEEK_END );
    size_t size_not_blue = ftell ( f );
    fseek ( f, prev, SEEK_SET );

    return size_not_blue;
}

int Compare ( Comand_Code cc, Line_t line_array, Stack_Data_t *Stack, int *Pointer )  //name
{
$   for ( int i = 0; i < cc.n_comands; ++i ) {
$       if ( strcmp ( line_array.start, cc.arr[i].str ) == 0 ) {
            int indificate = 0;
            if ( i == JMP || i == JA || i == JB ) {
                StackPush ( Stack, ((((indificate | line_array.element ) << 15 ) | Pointer[line_array.registerr] ) << 5 ) | cc.arr[i].code );
            }
            else {
                StackPush ( Stack, ((((indificate | line_array.element ) << 15 ) | line_array.registerr ) << 5 ) | cc.arr[i].code );
            }
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

int Asm_Compile ( Text_t *Text, char *buffer, const char *output_file )
{
    Stack_Data_t Stack  = {};
    Comand_Code CC = {};
    int error_indificate = 0;
    //Stack_Data_t Pointer  = {};
    int labels_array[10] = {};
$
    StackCtor ( &Stack );
    //Pointer.str = StackCtor ( Pointer.size_stack );

    char *ref_buffer = ( char *)calloc (  Text->file_size + 1, sizeof ( char ) );
    strcpy ( ref_buffer, buffer );

    for ( int i = 0; i <= Text->file_size; ++i ) {
        if ( *( ref_buffer + i ) == ';' ) {
            *( ref_buffer + i ) = '\0';
        }
    }

    for ( int i = 0; i <= Text->file_size; ++i ) {
        if ( *( buffer + i ) == ';' ) {
            ++(Text->n_lines);
            *( buffer + i ) = '\0';
        }
    }
    FILE *code_f   = fopen ( "code.txt", "wb" );
    // err

    Text->line_array = ( Line_t *)calloc ( Text->n_lines, sizeof ( Line_t) );
    // err

    //Get_Pointer ( ref_buffer, &Pointer, Text, CC );
    //StackDump ( Pointer, INFORMATION );
    int ip = 0;

    for ( int i = 0, j = 0; i < Text->n_lines; ++j, ++i ) {
        int len = 0;
        bool flag = false;
        while ( ref_buffer[j] != '\0' ) {   // flag E space   '\n'
            if ( ref_buffer[j] == ' ' ) {
                if (flag) {
                    printf("ERROR\n");
                }
                ref_buffer[j] = '\0';
                flag = true;
$               Text->line_array[i].start = ref_buffer + j - len;
                Text->line_array[i].element = ( elem_t )atof ( ref_buffer + j + 1 );
            }
            else if (flag == false ) {    //  maybe change this
                ++len;
            }
            ++j;
        }
$       if ( flag == false ) {      // vverh
$           Text->line_array[i].start = ref_buffer + j - len;
        }
$       while ( ref_buffer[j] != '\n' ) {
$           ++j;
        }
        //Verificator ( &Stack, &error_indificate );

$       if ( strcmp ( Text->line_array[i].start, CC.arr[START].str ) == 0 ) {
$           labels_array[(int)Text->line_array[i].element] = ip;
        }
        else {
            ip += 1;//3 * sizeof ( elem_t );  // 3 == n_elem
        }
    }
$

$    for ( int i = 0, j = 0; i < Text->n_lines; ++j, ++i ) {
        int len = 0;
        bool flag = false;
        while ( buffer[j] != '\0' ) {   // flag E space   '\n'
            if ( buffer[j] == ' ' ) {
                if (flag) {
                    printf("ERROR\n");
                }
                buffer[j] = '\0';
                flag = true;
                Text->line_array[i].start = buffer + j - len;
                if ( *( buffer + j + 1 ) == 'r' &&
                     *( buffer + j + 3 ) == 'x' &&
                     *( buffer + j + 4 ) == '\0' ) {
                    Text->line_array[i].registerr = *( buffer + j + 2 ) - ('a' - 1); //
                    Text->line_array[i].element = 0;
                }
                else {
                    Text->line_array[i].registerr = 0;
                    Text->line_array[i].element = ( elem_t )atof ( buffer + j + 1 );
                }
            }
            else if (flag == false ) {    //  maybe change this
                ++len;
            }
            ++j;
        }
        if ( flag == false ) {      // vverh
            Text->line_array[i].start = buffer + j - len;
            Text->line_array[i].registerr = 0;
            Text->line_array[i].element   = 0;  // wtf
        }
        while ( buffer[j] != '\n' ) {
            ++j;
        }
        Verificator ( &Stack );

        if ( strcmp ( Text->line_array[i].start, CC.arr[CALL].str ) == 0 ) {
            int indificate = 0;
            StackPush ( &Stack, ((((indificate | 0 ) << 15 ) | labels_array[(int)Text->line_array[i].element] ) << 5 ) | CC.arr[CALL].code );
            //StackPush ( &Stack, CC.arr[CALL].code );
            //StackPush ( &Stack, labels_array[(int)Text->line_array[i].element] );
            //StackPush ( &Stack, 0 ); //Text->line_array[i].element );
        }
        else if ( strcmp ( Text->line_array[i].start, CC.arr[START].str ) == 0 ) {
            ;
        }
        else {
            Compare ( CC, Text->line_array[i], &Stack, labels_array );
        }
    }

    StackDump ( Stack, INFORMATION );
    fwrite ( Stack.data, sizeof ( elem_t ), ip , code_f );
    // err
            //you should do a lot of work to pass this, you just can give up, but i am syre, that's is not your aim
    StackDtor ( &Stack );
    fclose ( code_f );

    return Text->error_indificate;
}

/*void Get_Pointer ( int *labels_array, char *buffer, Text_t *Text, Comand_Code CC, int *ip )
{
    char *ref_buffer = ( char *)calloc (  Text->file_size + 1, sizeof ( char ) );
    strcpy ( ref_buffer, buffer );

    for ( int i = 0; i <= Text->file_size; ++i ) {
        if ( *( ref_buffer + i ) == ';' ) {
            *( ref_buffer + i ) = '\0';
        }
    }

    for ( int i = 0, j = 0; i < Text->n_lines; ++j, ++i ) {
        int len = 0;
        bool flag = false;
        while ( ref_buffer[j] != '\0' ) {   // flag E space   '\n'
            if ( ref_buffer[j] == ' ' ) {
                if (flag) {
                    printf("ERROR\n");
                }
                ref_buffer[j] = '\0';
                flag = true;
$               Text->line_array[i].start = ref_buffer + j - len;
                Text->line_array[i].element = ( elem_t )atof ( ref_buffer + j + 1 );
            }
            else if (flag == false ) {    //  maybe change this
                ++len;
            }
            ++j;
        }
$       if ( flag == false ) {      // vverh
$           Text->line_array[i].start = ref_buffer + j - len;
        }
$       while ( ref_buffer[j] != '\n' ) {
$           ++j;
        }

$       if ( strcmp ( Text->line_array[i].start, CC.arr[START].str ) == 0 ) {
$           labels_array[(int)Text->line_array[i].element] = *ip;
        }
        else {
            *ip += 3 * sizeof ( elem_t );  // 3 == n_elem
        }
    }
}  */

