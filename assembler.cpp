#include "assembler.h"
#include "my_program.h"

//you should do a lot of work to pass this, you just can give up, but i am sure, that's is not your aim

Error_t Assembler_Ctor ( Text_t *text, const char *command_file )
{
    assert ( text != nullptr );
    assert ( command_file != nullptr );

    FILE *command_f = fopen ( command_file, "rb" );
    if ( !command_f ) {
        perror ( "File opening failed" );

        return F_OPEN_ERR;
    }

    text->file_size = GetFileSize ( command_f );

    text->data = ( char *)calloc ( text->file_size + 1, sizeof ( char ) );
    if ( !text->data ) {

        return MEMMORY_ERR;
    }

    int ret_code = fread ( text->data, sizeof ( text->data[0] ), text->file_size, command_f );
    if ( ret_code != text->file_size ) {
        if ( feof ( command_f ) ) {
            printf ( "Error reading %s: unexpected end of file\n", command_file );
        }
        else if ( ferror ( command_f ) ) {
            perror ( "Error reading command_file\n" );
        }
        fclose ( command_f );

        return F_READ_ERR;
    }
    fclose ( command_f );

    Error_t ret_err = Text_Skip_Spaces ( text );
    if ( ret_err != NO_ERR ) {

        return ret_err;
    }

    text->line_array = ( Line_t *)calloc ( text->n_lines, sizeof ( Line_t ) );
    if ( !text->line_array ) {

        return MEMMORY_ERR;
    }

    return NO_ERR;
}

Error_t Assembler_Compile ( struct Asm_t *assembler, const char *encode_file )
{
    assert ( assembler != nullptr );
    assert ( encode_file != nullptr );

    int ip = 0;

$   Split_Data_Into_Lines ( assembler, &ip );

$   for ( int i = 0, j = 0; i < assembler->text.n_lines; ++j, ++i ) {
        if ( strcmp ( text->line_array[i].start, command_arr[CALL].str ) == 0 ) {
                                /*---------------------MACRO-------------------------------------*/ //FIXME
            StackPush ( stack, ( ( assembler->labels_array[(int)text->line_array[i].element] ) << 5 ) | CALL );
        }
        else if ( strcmp ( assembler->text.line_array[i].start, command_arr[COLON].str ) == 0 ) {
            ;
        }
        else {
            Assembler_Compare ( text->line_array[i], stack, labels_array );
        }
    }
    Verificator ( stack );
    StackDump ( *stack, INFORMATION );

    return Wtite_Code_To_File ( stack->data, ip, encode_file );
}
//FIXME not skip spaces, better: remove commnets or something like that
void Split_Data_Into_Lines ( struct Asm_t *assembler, int *ip )
{
    assert ( assembler != nullptr );
    assert ( ip != nullptr );

    for ( int i = 0, j = 0; i < assembler->text.n_lines; ++j, ++i ) {   // i ???
        int len = 0;
        assembler->text.line_array[i].start = assembler->text.data + j;   //

        while ( assembler->text.data[j] != '\0' ) {
            if ( assembler->text.data[j] == ' ' ) {
                assembler->text.data[j] = '\0';
$               assembler->text.line_array[i].start = assembler->text.data + j - len; //
                assembler->text.line_array[i].element = atoi ( assembler->text.data + j + distance_command_element ); // strtod

                // skip_spaces
                if ( assembler->text.data[j + 1] == 'r' &&
                     assembler->text.data[j + 3] == 'x' &&
                     assembler->text.data[j + 4] == '\0' ) {
                    assembler->text.data[i].registerr = *( assembler->text.data + j + distance_command_register ) - ( 'a' - distance_command_element );
                    assembler->text.data[i].element = 0;
                }
            }
            else {
                ++len;
            }
            ++j;
        }

$       if ( strcmp ( assembler->text.line_array[i].start, ":" ) == 0 ) {
$           text->labels_array[assembler->text.line_array[i].element] = *ip;
        }
        else {
            *ip += 1;  // stroka // ++*ip;
        }
    }
}

Error_t Assembler_Compare ( Line_t line_array, Stack_Data_t *stack, int * )  //name
{
    // assert ( line_array != nullptr );
    assert ( stack      != nullptr );
    assert ( pointer    != nullptr );

    const int n_commands = sizeof ( command_arr )/ sizeof ( Command_t ); //FIXME bad naming: arr what??? -> command_arr
    const int encode_element = ( line_array.element ) << 15; // FIXME encode

$   for ( int i = 0; i < n_commands; ++i ) {
$       if ( strcmp ( line_array.start, command_arr[i].str ) == 0 ) {
            if ( i == JMP || i == JA || i == JB || i == JAE ||
                 i == JBE || i == JE || i == JNE  ) {
                                    /*-----------------------MACRO----------------------------------------------*/ //FIXME
                StackPush ( stack, ( ( encode_element | labels_array[line_array.element] ) << 5 ) | command_arr[i].code );
            }
            else {
                StackPush ( stack, ( ( encode_element | line_array.registerr ) << 5 ) | command_arr[i].code );
            }
$           break;
        }
    }

$   return NO_ERR;
}

Error_t Wtite_Code_To_File ( elem_t *data, int ip, const char *encode_file )
{
    assert ( data != nullptr );
    assert ( encode_file != nullptr );

    FILE *code_f = fopen ( encode_file, "wb" );
    if ( !code_f ) {
        perror ( "File opening failed" );

        return F_OPEN_ERR;
    }

    int written_objects_n = fwrite ( data, sizeof ( elem_t ), ip , code_f );
    fclose ( code_f );
    if ( written_objects_n < ip ) {
        //printf ( "Write error in the file\n" );
        return F_WRITE_ERR;
    }

    return NO_ERR;
}

void Assembler_Dtor ( Text_t *Text )
{
    assert(Text != nullptr);

    free ( Text->data );
    free ( Text->line_array );
}
