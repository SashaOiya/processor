//#define loxxx %c

#include "stack.h"

/*int main()
{
    //printf ("%d\n", sizeof ( long ) );
    Stack_Data_t Stack = {};
    FILE *f = fopen ( "code.txt", "r" );

    Stack.str = StackCtor ( Stack.size_stack );

    //StackHash ( &Stack.canary_left,  &Stack.canary_right );
                                                                      //n_lines * 2
    StackCreator ( f, &Stack.capacity, &Stack.size_stack, &Stack.str, 22  );

    StackDump ( Stack.str, INFORMATION , Stack.size_stack, Stack.capacity );

    //free ( Stack.str );
    StackDtor ( Stack.str, Stack.size_stack );

    StackDump ( Stack.str, INFORMATION , Stack.size_stack, Stack.capacity );

    //StackHash ( &Stack.canary_left,  &Stack.canary_right );

    return 0;
}     */

// stackResize
char_t * StackCtor ( const int size_stack )   //void enum
{
    Stack_Data_t Stack = {};
    char_t *str_begin = (char_t *)calloc ( size_stack + (sizeof(long)/sizeof(char_t)) * 2, sizeof ( char_t ) );   //free
    // str_begin == nullptr
    // StackRealloc()
    if ( sizeof ( char_t) == 4 || sizeof ( char_t) == 8 ) {
        *str_begin = Stack.canary_left;
        *(str_begin + size_stack * sizeof ( char_t) + sizeof(long) ) = Stack.canary_right;
    }
    /*else if ( sizeof(char_t) == 1 ) {
        str_begin[0] = 0xD;
        str_begin[1] = 0xE;
        str_begin[2] = 0xD;
    }  */

    char_t *str = str_begin + sizeof (long );

    return str;
$
}
                                       //data
char_t* StackRedistribute ( char_t *str, int size_stack )
{
                                                //#warning no canary
    // int main()
    //realloc
    // callloc == nullptr
    Stack_Data_t Stack = {};
    char_t *ptr_begin = (char_t *)calloc ( size_stack + (sizeof(long)/sizeof(char_t)) * 2, sizeof ( char_t ) );   //free

    if ( sizeof ( char_t) == 4 || sizeof ( char_t) == 8 ) {
        *ptr_begin = Stack.canary_left;
        *(ptr_begin + size_stack * sizeof ( char_t) + sizeof(long) ) = Stack.canary_right;
    }
$   char_t *ptr = ptr_begin + sizeof ( long );

$   //memset ( ptr, 0, size_stack * sizeof ( char_t ) ); // ptr + capacity

    //strcpy ( ptr, str );
$   memcpy ( ptr, str, size_stack * sizeof ( char_t ) / 2 );

$   return ptr;
}

void StackDump ( const char_t *stack, const char* func_name, const char* file_name,
                 size_t size_stack, const size_t capacity )    // void
{
$   printf ( "Stack [%p] ", stack );
    name_print( stack )
    printf ( " called from%s\n "
             "{\n\t%s  \n\t{ \n "
             " \t\tsize = %d \n "
             " \t\tcapacity = %d \n "
             " \t\tdata [%p]:\n", file_name, func_name, size_stack, capacity, stack  ); // data
$   for ( size_t i = 0; i < size_stack; ++i ) {
$       printf ( "\t\tdata[%d] = ", i );
        printf ( SPECIFIER, stack[i] );
        printf ( "\n" );
    }
$   printf ( "\t}\n}\n");
}

int StackDtor ( char_t *stack, size_t size_stack )      // plus errors check
{
    assert ( stack != nullptr );

$   memset ( stack - sizeof ( long ), 3, size_stack * sizeof ( char_t ) + sizeof( long) * 2 ) ;

    free ( stack );// sizeof ( canary )

    return NO_ERRORS;
}

Errors_t StackPush ( char_t *str[], const char_t value, int * size_stack, int *capacity ) // struct Stack
{

// asserttttttttt!!!!
    ++(*capacity);
$   if ( *capacity == *size_stack ) {
$       *size_stack = 2 * (*size_stack);

$       *str = StackRedistribute ( *str, *size_stack );
$       //printf ("lox inside %p\n", *str );
$   }
$   *( *str + *capacity - 1 ) = value;

    return NO_ERRORS;   //errors
}

char_t StackPop ( char_t *stack, int *capacity  )
{
    //--str_1;
    char_t temp = *( stack + *capacity - 1 );
    --(*capacity);
    *( stack + *capacity ) = 0; // const

    return temp;   //errors   // *str_1 // str_1  name
}


// test.cpp
void StackCreator ( FILE *f, int *capacity, int *size_stack, char_t *str[], int n_lines  )    // *
{
    char_t c = 0;
    for ( int i = 0; ( c = getchar()) != '\n'; ++ i ) {
        ++*capacity;
        StackDump ( *str, __PRETTY_FUNCTION__, __FILE__, *size_stack, *capacity );
$       StackPush ( str, c, size_stack, capacity );
$       //StackPop ( *str + i, *stack_data + i );
    }
}

int StackHash ( void *begin_stack, void *end_stack ) // struc Stack
{
    // char * usuc = ( char *)
    int size_stack = (char *)end_stack - (char *)begin_stack;   // sizeof ( stack)
    long long sum  = 0;

    for ( int i = 0; i < size_stack; ++i ) {
        sum += *( (char *)begin_stack + i );
    }

    /*printf ("%d\n", size_stack);
    printf ("%lld\n", sum );   */

    return sum;
}
                                                                      //switch
int Verificator ( const char_t *str, size_t size_stack,
                  const size_t capacity, int *error_indificate )   // struct
{
    if ( str == nullptr ) {
        (*error_indificate ) | ( (*error_indificate) | 1 << 2 );
    }
    if ( size_stack < 0 || size_stack < capacity ) {
        (*error_indificate ) | ( (*error_indificate) | 1 << 1 );
    }
    if ( capacity < 0 ) {
        (*error_indificate ) | ( (*error_indificate) | 1 << 0 );//enum
    }
}




