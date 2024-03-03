#include "stack.h"

int main()
{
    Stack_Data_t Stack = {};

    StackCtor ( &Stack );

    StackPush ( &Stack, 4 );
    StackPush ( &Stack, 7 );
    // if (StackGetStatus( &Stack))
    StackPop  ( &Stack );

    // const Stack*
    StackDump ( Stack, INFORMATION ); // Chooo???

    StackDtor ( &Stack );

    return 0;
}
