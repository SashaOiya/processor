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
    OUT ,
    POP
};

struct Comand {
    const char *str;
    int code;
};

struct Comand_Code { // remove    // this is krivo!!!
    const int n_comands = 12;
    const struct Comand arr[12] = {
                                    { "push", PUSH }, { "HLT" , HLT }, { "add", ADD },
                                    { "mul" , MUL  }, { "sqrt", SQRT}, { "sin", SIN },
                                    { "cos" , COS  }, { "div" , DIV }, { "sub", SUB },
                                    { "in"  , IN   }, { "out" , OUT }, { "pop", POP }
                                  };
};                            // remove

#endif  // COMAND_CODE
