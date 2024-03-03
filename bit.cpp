#include <stdio.h>

int main ()
{
    int code = 5;
    int registers = 2;
    int value = 15;

    int indificate = 0;
    indificate = ((((indificate | value ) << 15 ) | registers ) << 5 ) | code ;

    printf ( "%d\n", indificate );

    printf ( "code %d\n", ( indificate >> 0 ) & ~(~0 << 5) );
    printf ( "registers %d\n", (indificate >> 5 ) & ~(~0 << 15) );
    printf ( "value %d\n", (indificate >> 20 ) & ~(~0 << 12) );

    return 0;
}
