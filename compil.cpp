#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int GetFileSize ( FILE * f );

#ifdef DEBUG
#define $ printf ( "%d\n", __LINE__ );
#else
#define $
#endif

enum Code {
    PUSH,
    HLT ,
    ADD ,
    MUL ,
    SQRT,
    SIN ,
    COS ,
    DIV ,
    SUB ,
    IN  ,
    OUT
};

struct Comand {
    char *str;
    int code;
};

struct Comand_Code {
    const int n_comands = 11;
    struct Comand arr[11] = {
                              { "push", PUSH }, { "HLT" , HLT }, { "add", ADD },
                              { "mul" , MUL  }, { "sqrt", SQRT}, { "sin", SIN },
                              { "cos" , COS  }, { "div" , DIV }, { "sub", SUB },
                              { "in"  , IN   }, { "out" , OUT }
                            };
};

struct Text_t {
    int file_size = 0;
    char *start = nullptr;
};

int Compare ( FILE *code, Comand_Code cc, char *start, float ptr_elements );

int main ()
{
    FILE *f = fopen ( "start.txt", "r" );
    FILE *code = fopen ( "code.txt", "w" );

    Comand_Code CC = {};
    Text_t Text    = {};

    Text.file_size = GetFileSize ( f );

    char *buffer = ( char *)calloc ( Text.file_size + 1, sizeof ( char ) );
    fread ( buffer, sizeof( buffer[0] ), Text.file_size, f );    //return value
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
        Compare ( code, CC, start[i], ptr_elements[i] );
    }

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
