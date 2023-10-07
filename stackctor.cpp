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

    //StackDump ( Stack.str, INFORMATION , Stack.size_stack, Stack.capacity );

    //StackHash ( &Stack.canary_left,  &Stack.canary_right );

    return 0;
}   */

// stackResize
char_t * StackCtor ( const int size_stack )   //void enum
{
    char_t *str_begine = (char_t *)calloc ( size_stack + sizeof(long long) * 2, sizeof ( char_t ) );   //free
    // str_begin == nullptr
    // StackRealloc()
    char_t *str = str_begine + sizeof ( long long );

    return str;
$
}
                                       //data
char_t* StackRedistribute ( char_t *str, int size_stack )
{
                                                //#warning no canary
    // int main()
    //realloc
$   char_t *ptr_begine = (char_t *)calloc( size_stack, sizeof ( char_t ) );   //free
    // callloc == nullptr
$   char_t *ptr = ptr_begine;

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
$   for ( int i = 0; i < size_stack; ++i ) {
$       printf ( "\t\tdata[%d] = %d\n", i, stack[i] );
    }
$   printf ( "\t}\n}\n");
}

int StackDtor ( char_t *stack, size_t size_stack )      // plus errors check
{
    assert ( stack != nullptr );

$   memset ( stack, 0, size_stack * sizeof ( char_t ) ) ;

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

char_t StackPop ( const char_t *stack, int *capacity  )
{
    //--str_1;
    char_t temp = *( stack + *capacity );
    --(*capacity);

    return temp;   //errors   // *str_1 // str_1  name
}


// test.cpp
/*void StackCreator ( FILE *f, int *capacity, int *size_stack, char_t *str[], int n_lines  )    // *
{
    char_t c = 0;
    for ( int i = 0; i < n_lines; ++ i ) {
        fscanf ( f, SPECIFIER, &c );
        ++*capacity;
        StackDump ( *str, __PRETTY_FUNCTION__, __FILE__, *size_stack, *capacity );
$       StackPush ( str, c, size_stack, *capacity );
$       //StackPop ( *str + i, *stack_data + i );
    }
}  */

int StackHash ( void *begin_stack, void *end_stack ) // struc Stack
{
    // char * usuc = ( char *)
    int size_stack = (char *)end_stack - (char *)begin_stack;   // sizeof ( stack)
    long long sum  = 0;

    for ( int i = 0; i < size_stack; ++i ) {
        sum += *( (char *)begin_stack + i );
    }

    printf ("%d\n", size_stack);
    printf ("%lld\n", sum );

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



