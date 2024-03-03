#include "assembler.h"

// func SkeapSpaces

int main ( int argc, char* argv[] )
{
    FILE *command_f = fopen ( argv[1], "rb" );
    assert ( command_f != nullptr );

    Text_t Text = {};
    Text.file_size = GetFileSize ( command_f );

    char *buffer = ( char *)calloc ( Text.file_size + 1, sizeof ( char ) );
    assert ( buffer != nullptr );

    int ret_code = fread ( buffer, sizeof( buffer[0] ), Text.file_size, command_f );
    if ( ret_code != Text.file_size ) {
        if ( feof ( command_f ) ) {
            printf("Error reading test.bin: unexpected end of file\n");
        }
        else if ( ferror ( command_f ) ) {
            perror("Error reading test.bin");
        }
    }
    buffer[Text.file_size] = '\n';

    FILE *f = fopen ( "code.txt", "wb" );
    assert ( f != nullptr );

    AsmCompile ( &Text, buffer, f ); //

    AsmDtor ( buffer, Text.line_array, command_f );

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
                 // pointer
int AsmCompare ( Line_t line_array, Stack_Data_t *Stack, int *pointer, Stack_Data_t *Pointer )  //name
{
    const int n_commands = sizeof ( arr )/ sizeof ( Command );
$   for ( int i = 0; i < n_commands; ++i ) {
$       if ( strcmp ( line_array.start, arr[i].str ) == 0 ) {
            int indificate = 0;
            if ( i == JMP ) {
                StackPush ( Stack, ((((indificate | line_array.element ) << 15 ) | pointer[line_array.element] ) << 5 ) | arr[i].code );
            }
            else if ( i == JA  || i == JB || i == JAE ||
                      i == JBE || i == JE || i == JNE ) {
                StackPush ( Stack, ((((indificate | line_array.element ) << 15 ) | StackPop ( Pointer ) ) << 5 ) | arr[i].code );
                Pointer->capacity += 2;
            }
            else {
                StackPush ( Stack, ((((indificate | line_array.element ) << 15 ) | line_array.registerr ) << 5 ) | arr[i].code );
            }
$
$           break;
        }
        //else {   error

    }

$   return 0; // error code
}

int AsmDtor ( char *buffer, Line_t *line_array, FILE *comand_f )
{
    free(buffer);
    free(line_array);

    fclose ( comand_f ); //error
}

int AsmCompile ( Text_t *Text, char *buffer, FILE *code_f )
{
    Stack_Data_t Stack    = {};
    Stack_Data_t Pointer  = {};
    int labels_array[10]  = {};  //
$
    StackCtor ( &Stack );
    StackCtor ( &Pointer );

    for ( int i = 0; i <= Text->file_size; ++i ) {
        if ( *( buffer + i ) == ';' ) {
            ++(Text->n_lines);
            *( buffer + i ) = '\0';
        }
    }   // make separate function

    Text->line_array = ( Line_t *)calloc ( Text->n_lines, sizeof ( Line_t ) );
    assert ( Text->line_array != nullptr );

    int ip = 0;        // = 1

$   GetPointer ( labels_array, Text, &ip, buffer, &Pointer );

$   for ( int i = 0, j = 0; i < Text->n_lines; ++j, ++i ) {
        while ( buffer[j] != '\0' ) {
            if ( buffer[j] == ' ' ) {
                buffer[j] = '\0';
                if ( *( buffer + j + 1 ) == 'r' &&
                     *( buffer + j + 3 ) == 'x' &&
                     *( buffer + j + 4 ) == '\0' ) {
                    Text->line_array[i].registerr = *( buffer + j + 2 ) - ( 'a' - 1 );
                    Text->line_array[i].element = 0;
                }
            }
            ++j;
        }
        while ( buffer[j] != '\n' ) {
            ++j;
        }
        Verificator ( &Stack );

        if ( strcmp ( Text->line_array[i].start, arr[CALL].str ) == 0 ) {
            int indificate = 0;
            StackPush ( &Stack, (( indificate | labels_array[(int)Text->line_array[i].element] ) << 5 ) | CALL );
        }
        else if ( strcmp ( Text->line_array[i].start, arr[START].str ) == 0 ) {
            ;
        }
        else {
            AsmCompare ( Text->line_array[i], &Stack, labels_array, &Pointer );
        }
    }

    Verificator ( &Stack );
    StackDump ( Stack, INFORMATION );
    fwrite ( Stack.data, sizeof ( elem_t ), ip , code_f );
    // err
            //you should do a lot of work to pass this, you just can give up, but i am syre, that's is not your aim
    StackDtor ( &Stack );
    StackDtor ( &Pointer );
    fclose ( code_f );

    return Text->error_indificate;
}

void GetPointer ( int *labels_array, Text_t *Text, int *ip,
                  char * ref_buffer, Stack_Data_t *Pointer )
{
    for ( int i = 0, j = 0; i < Text->n_lines; ++j, ++i ) {   // i ???
        int len = 0;
        bool flag = false;    // delete

        Text->line_array[i].start = ref_buffer + j;   //

        while ( ref_buffer[j] != '\0' ) {   // flag E space   '\n'
            if ( ref_buffer[j] == ' ' ) {
                if ( flag ) {
                    printf("ERROR\n");
                }
                flag = true;
$               Text->line_array[i].start = ref_buffer + j - len;
                Text->line_array[i].element = atoi ( ref_buffer + j + 1 );
            }
            else if ( flag == false ) {    //  maybe change this
                ++len;
            }
            ++j;
        }
        Text->line_array[i].line_size = len;

$       while ( ref_buffer[j] != '\n' ) {
$           ++j;
        }
        Verificator ( Pointer );

        char prev_element = *( Text->line_array[i].start + Text->line_array[i].line_size );
        *( Text->line_array[i].start + Text->line_array[i].line_size ) = '\0';

$       if ( strcmp ( Text->line_array[i].start, ":" ) == 0 ) {
$           labels_array[Text->line_array[i].element] = *ip;
            StackPush ( Pointer, *ip - 1 );  // thiiiiiiiiiiiis
        }
        else {
            *ip += 1;  // stroka
        }

        *( Text->line_array[i].start + Text->line_array[i].line_size ) = prev_element;
    }
    Pointer->capacity = 1;
}
