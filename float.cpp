#include <stdio.h>
#include <assert.h>

int main()
{
    printf( "Hello!\n");


    float* buffer = (float*)calloc( 6, sizeof( float));

    buffer[0] =

    float x = 16;    // papa lexi
    FILE* file = fopen( "cat.bin", "wb");
    assert( file != nullptr );

    fwrite( &x, sizeof(x), 1, file);

    fclose( file);


    file = fopen( "cat.bin", "rb");

    fread( buffer, sizeof( float), 1, file);

    printf( "%f\n", x);

    fclose( file);
    free( buffer);

    return 0;
}
