#include "assembler.h"
//#include "stack.h"

//void Get_Pointer ( char *ref_buffer, Stack_Data_t *Pointer, Text_t *Text, Comand_Code cc );

int main () // argc argv
{
    int n_comands = 0;

    Assembler ();

    return 0;
}

void Assembler ()
{
    FILE *comand_f = fopen ( "start.txt", "rb" );  // file

    Text_t Text    = {};

    Text.file_size = GetFileSize ( comand_f );

    char *buffer = ( char *)calloc ( Text.file_size + 1, sizeof ( char ) );
    // errrrrrr

    fread ( buffer, sizeof( buffer[0] ), Text.file_size, comand_f );    //return value
    // errrr

    buffer[Text.file_size] = '\n';

    Split ( &Text, buffer );  // Assemble() Compile()

    //AsmDtor ( buffer, Text.line_array, code_f );

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
            StackPush( Stack, cc.arr[i].code );
            if ( i == JMP || i == JA || i == JB ) {
                StackPush ( Stack, Pointer[line_array.registerr] );
                //Pointer->capacity += 2; //
            }
            else {
                StackPush ( Stack, line_array.registerr );
            }
            StackPush ( Stack, line_array.element );
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

int Split ( Text_t *Text, char *buffer )   //name FILE*
{
    Stack_Data_t Stack  = {};
    Comand_Code CC = {};
    int error_indificate = 0;
    //Stack_Data_t Pointer  = {};
    int Pointer[10] = {};
$
    Stack.str   = StackCtor ( Stack.size_stack   );
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
$           Pointer[(int)Text->line_array[i].element] = ip;
        }
        else {
            ip += 3 * sizeof ( elem_t );  // 3 == n_elem
        }

        /*if ( strcmp ( Text->line_array[i].start, CC.arr[CALL].str ) == 0 ) {
            Pointer.capacity -= 1;
            int data = Pointer.str[Pointer.capacity];
$           StackPush( &Pointer, i );
            StackPush( &Pointer, data  );
        }*/
    }

    //StackDump ( Pointer, INFORMATION );
    //Pointer.capacity = 1;

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
        Verificator ( &Stack, &error_indificate );

        /*if ( strcmp ( Text->line_array[i].start, CC.arr[START].str ) == 0 ) {
            StackPush( &Stack, ' ' );
            StackPush( &Stack, ' ' );
            StackPush( &Stack, ' ' );
        } */
        if ( strcmp ( Text->line_array[i].start, CC.arr[CALL].str ) == 0 ) {
            StackPush ( &Stack, CC.arr[CALL].code );
            StackPush ( &Stack  , Pointer[(int)Text->line_array[i].element] );
            //Pointer.capacity += 2;
            StackPush ( &Stack, 0 ); //Text->line_array[i].element );
        }
        else if ( strcmp ( Text->line_array[i].start, CC.arr[START].str ) == 0 ) {
            ;
        }
        else {
            Compare ( CC, Text->line_array[i], &Stack, Pointer );
        }
    }

    StackDump ( Stack, INFORMATION );
    fwrite ( Stack.str, sizeof ( elem_t ), ip / sizeof ( elem_t ), code_f );
    // err
            //you should do a lot of work to pass this, you just can give up, but i am syre, that's is not your aim
    StackDtor ( Stack.str, Stack.size_stack );
    fclose ( code_f );

    return error_indificate;
}

/*void Get_Pointer ()
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
$           StackPush( &Pointer, i + 1 );
        }
        if ( strcmp ( Text->line_array[i].start, CC.arr[CALL].str ) == 0 ) {
            Pointer.capacity -= 1;
            int data = Pointer.str[Pointer.capacity];
$           StackPush( &Pointer, i + 1 );
            StackPush( &Pointer, data  );
        }
    }

    StackDump ( Pointer, INFORMATION );
    Pointer.capacity = 1;  */





