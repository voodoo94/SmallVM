#include <string.h>

typedef enum {
    ADD,
    ADDR,
    CLC,
    CLI,
    CLZ,
    CMC,
    CMPR,
    DEC,
    DIV,
    DIVR,
    INC,
    JMP,
    MOV,
    MUL,
    MULR,
    HLT,
    POP,
    POPR,
    PSH,
    PSHR,
    SET,
    STC,
    STI,
    SUB,
    SUBR
} instruction_set;

const static struct {
    instruction_set instruction;
    const char *instruction_str;
} conversion[] = {
    {ADD, "ADD,"},
    {ADDR, "ADDR,"},
    {CLC, "CLC,"},
    {CLI, "CLI,"},
    {CLZ, "CLZ,"},
    {CMC, "CMC,"},
    {CMPR, "CMPR,"},
    {DEC, "DEC,"},
    {DIV, "DIV,"},
    {DIVR, "DIVR,"},
    {INC, "INC,"},
    {JMP, "JMP,"},
    {MOV, "MOV,"},
    {MUL, "MUL,"},
    {MULR, "MULR,"},
    {HLT, "HLT,"},
    {POP, "POP,"},
    {POPR, "POPR,"},
    {PSH, "PSH,"},
    {PSHR, "PSHR,"},
    {SET, "SET,"},
    {STC, "STC,"},
    {STI, "STI,"},
    {SUB, "SUB,"},
    {SUBR, "SUBR,"},
    {ADD, "ADD"},
    {ADDR, "ADDR"},
    {CLC, "CLC"},
    {CLI, "CLI"},
    {CLZ, "CLZ"},
    {CMC, "CMC"},
    {CMPR, "CMPR"},
    {DEC, "DEC"},
    {DIV, "DIV"},
    {DIVR, "DIVR"},
    {INC, "INC"},
    {JMP, "JMP"},
    {MOV, "MOV"},
    {MUL, "MUL"},
    {MULR, "MULR"},
    {HLT, "HLT"},
    {POP, "POP"},
    {POPR, "POPR"},
    {PSH, "PSH"},
    {PSHR, "PSHR"},
    {SET, "SET"},
    {STC, "STC"},
    {STI, "STI"},
    {SUB, "SUB"},
    {SUBR, "SUBR"}
};

typedef enum {
    A,
    B, 
    C,
    D,
    E,
    F,
    IP,
    SP,
    NUM_REGISTERS
} registers_set;

const static struct {
    registers_set reg;
    const char *register_str;
} conversion_register[] = {
    {A, "A,"},
    {B, "B,"},
    {C, "C,"},
    {D, "D,"},
    {E, "E,"},
    {F, "F,"},
    {IP, "IP,"},
    {SP, "SP,"},
    {A, "A"},
    {B, "B"},
    {C, "C"},
    {D, "D"},
    {E, "E"},
    {F, "F"},
    {IP, "IP"},
    {SP, "SP"}
};

typedef enum {
    IF,
    TF,
    SF,
    ZF,
    CF,
    NUM_FLAGS
} flag_registers;

const static struct {
    flag_registers flag;
    const char *flag_str;
} conversion_flag[] = {
    {IF, "IF,"},
    {TF, "TF,"},
    {SF, "SF,"},
    {ZF, "ZF,"},
    {CF, "CF,"},
    {IF, "IF"},
    {TF, "TF"},
    {SF, "SF"},
    {ZF, "ZF"},
    {CF, "CF"}
};

int program[200];