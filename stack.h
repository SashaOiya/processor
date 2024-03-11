#ifndef STACK
#define STACK

typedef float char_t;
#define SPECIFIER "%g"

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
struct Stack_Data_t {          // Stack_t
    long canary_left    = 0xDED;
    long canary_right   = 0xDED;
    char_t *str             = 0;             //free
    int capacity            = 0;
    int size_stack          = 2;
};

char_t * StackCtor ( const int size_stack );
char_t* StackRedistribute ( char_t *str, int size_stack );
void StackDump ( const char_t *stack, const char* func_name, const char* file_name,
                 size_t size_stack, const size_t capacity );
int StackDtor ( char_t *stack, size_t size_stack );
Errors_t StackPush ( char_t *str[], const char_t value, int * size_stack, int *capacity );
char_t StackPop ( char_t *stack, int *capacity );
void StackCreator ( FILE *f, int *capacity, int *size_stack, char_t *str[], int n_lines  );
int StackHash ( Stack_Data_t *Stack );
void Verificator ( Stack_Data_t *Stack, int *error_indificate );
int GetFileSize ( FILE * f );

#endif //STACK
