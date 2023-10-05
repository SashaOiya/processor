#ifndef COMAND_CODE
#define COMAND_CODE

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
    const char *str;
    int code;
};

struct Comand_Code {
    const int n_comands = 11;
    const struct Comand arr[11] = {
                                    { "push", PUSH }, { "HLT" , HLT }, { "add", ADD },
                                    { "mul" , MUL  }, { "sqrt", SQRT}, { "sin", SIN },
                                    { "cos" , COS  }, { "div" , DIV }, { "sub", SUB },
                                    { "in"  , IN   }, { "out" , OUT }
                                  };
};

#endif  // COMAND_CODE
