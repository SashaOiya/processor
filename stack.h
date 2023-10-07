#ifndef STACK
#define STACK

typedef int char_t;
#define SPECIFIER "%d"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cassert>

#ifdef DEBUGG
#define $ printf ( "function <%s> line <%d>\n ", __PRETTY_FUNCTION__, __LINE__ );
#else
#define $
#endif

#define INFORMATION __PRETTY_FUNCTION__, __FILE__
#define name_print(a) printf ( #a " = %s\n", a );

enum Errors_t {
    NO_ERRORS = 1,
    ERROR     = 2
};

struct Error_t {        // typedef
    int ERROR = 0;
};

typedef long long canary_t;

// #ifdef CANARY_PROTECTION
struct Stack_Data_t {
#ifdef CANARY
    long long canary_left   = 0xDED0F;
#endif
    char_t *str_begine        = 0;
    char_t *str               = 0;             //free
    int capacity            = 0;
    int size_stack          = 2;
    long long canary_right  = 0xDED0F;
};

char_t * StackCtor ( const int size_stack );
char_t* StackRedistribute ( char_t *str, int size_stack );
void StackDump ( const char_t *stack, const char* func_name, const char* file_name,
                 size_t size_stack, const size_t capacity );
int StackDtor ( char_t *stack, size_t size_stack );
Errors_t StackPush ( char_t *str[], const char_t value, int * size_stack, int *capacity );
char_t StackPop ( const char_t *str_1, char_t *str_2 );
void StackCreator ( FILE *f, int *capacity, int *size_stack, char_t *str[], int n_lines  );
int StackHash ( void *begin_stack, void *end_stack );
int Verificator ( const char_t *str, size_t size_stack,
                  const size_t capacity, int *error_indificate );

#endif //STACK
