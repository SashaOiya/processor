#include <stdio.h>
#include <stdlib.h>

int main()
{
    int file_size = 50;
    FILE *file_f = fopen ( "code.txt", "rb" );
    char *buffer = ( char *)calloc(file_size, sizeof ( char ));  //
    fread ( buffer, sizeof( char ), file_size, file_f );
    for ( int i = 0; i < file_size ; ++i ) {
        printf ( "%c\n", buffer[i] );
    }
}
