#include "stack.h"

/* int main()
{
    //printf ("%d\n", sizeof ( long ) );
    Stack_Data_t Stack = {};
$
    Stack.str = (float *)StackCtor ( Stack.size_stack, sizeof ( float) );

    //StackHash ( &Stack.canary_left,  &Stack.canary_right );

    //StackCreator ( &Stack.capacity, &Stack.size_stack, (void **)&Stack.str  );

    StackDump ( Stack.str, INFORMATION , Stack.size_stack, Stack.capacity, sizeof (float) );

    //free ( Stack.str );
    StackDtor ( Stack.str, Stack.size_stack, sizeof ( float) );

    StackDump ( Stack.str, INFORMATION , Stack.size_stack, Stack.capacity, sizeof (float) );

    //StackHash ( &Stack.canary_left,  &Stack.canary_right );

    return 0;
}    */

// stackResize
void * StackCtor ( const int size_stack, size_t size )   //void enum
{
    void *str_begine = calloc ( size_stack * size + sizeof(long long) * 2, size );   //free
    // str_begin == nullptr

    // StackRealloc()
    void *str = ( float *)str_begine + sizeof ( long long );

    return str;
$
}
                                       //data
void* StackRedistribute ( void *stack, int size_stack, size_t size )
{
                                                //#warning no canary
    // int main()
    //realloc
    void *ptr_begine = realloc ( stack, size_stack * size + sizeof(long long) * 2 );   //free
    // callloc == nullptr
    void *ptr = (float *)ptr_begine + sizeof ( long long );  //canary

    //memset ( ptr, 0, size_stack * size ); // ptr + capacity

    //strcpy ( ptr, stack );

$   return ptr;
}

void StackDump ( const void *stack, const char* func_name, const char* file_name,
                 size_t size_stack, const size_t capacity, size_t size )    // void
{
$   printf ( "Stack [%p] ", stack );
    //name_print( (float *)stack )
    printf ( " called from%s\n "
             "{\n\t%s  \n\t{ \n "
             " \t\tsize = %d \n "
             " \t\tcapacity = %d \n "
             " \t\tdata [%p]:\n", file_name, func_name, size_stack, capacity, stack  ); // data
$   for ( size_t i = 0; i < size_stack; ++i ) {
$       printf ( "\t\tdata[%d] = %g \n", i, *( (const float *)stack + i * size ) );
    }
$   printf ( "\t}\n}\n");
}

int StackDtor ( void *stack, size_t size_stack, size_t size )      // plus errors check
{
    assert ( stack != nullptr );

// 3?
$   memset ( (float *)stack - 8 , 3, size_stack * size + 2 * sizeof ( canary_t ) ) ;

    free ( (float *)stack - 8 );// sizeof ( canary )

    return NO_ERRORS;
}

Errors_t StackPush ( void *stack[], float value, int * size_stack, const int capacity, size_t size ) // struct Stack
{

// asserttttttttt!!!!
    if ( capacity == *size_stack ) {
        *size_stack = 2 * (*size_stack);

        *(float **)stack = (float *)StackRedistribute ( *stack, *size_stack, size );
$   }
$   *( *(float **)stack + capacity - 1 ) = value;

    return NO_ERRORS;   //errors
}

void StackPop ( const void *stack, void *temp_array, size_t size )
{
    //--str_1;
    //void value = *stack;
    *(float *)temp_array = *(float *)stack;
    //--Stack;

    //return value;   //errors   // *str_1 // str_1  name
}


// test.cpp
void StackCreator ( int *capacity, int *size_stack, void *stack[], size_t size  )    // *
{
    char c = 0;
    for ( int i = 0; ( c = getchar() ) != '\n'; ++ i ) {
        ++*capacity;
        StackDump ( *stack, __PRETTY_FUNCTION__, __FILE__, *size_stack, *capacity, size );
$       StackPush ( stack, c, size_stack, *capacity, size );
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

    printf ("%d\n", size_stack);
    printf ("%lld\n", sum );

    return sum;
}
                                                                      //switch
int Verificator ( const void *stack, size_t size_stack,
                  const size_t capacity, int *error_indificate )   // struct
{
    if ( stack == nullptr ) {
        (*error_indificate ) | ( (*error_indificate) | 1 << 2 );
    }
    if ( size_stack < 0 || size_stack < capacity ) {
        (*error_indificate ) | ( (*error_indificate) | 1 << 1 );
    }
    if ( capacity < 0 ) {
        (*error_indificate ) | ( (*error_indificate) | 1 << 0 );//enum
    }
}


