#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "loader.h"

// Global Variables.
int running = 1;
int stack[256];
int registers[NUM_REGISTERS];
int flags[NUM_FLAGS];

// Function Prototypes.
int fetch(void);
int get_index_of(int);
void set_register(int, int);
void set_flags(int, int);
void evaluate(int);
int execute(void);

void set_register(int REG, int value) 
{
    registers[REG] = value;
    printf("The register %d set to %d\n", REG, registers[REG]);
}

void set_flags(int FLAG, int value)
{
    flags[FLAG] = value;
    printf("The flag %d set to %d\n", FLAG, value);
}

int fetch(void) 
{
    return program[registers[IP]];
}

void evaluate(int instr)
{
    switch (instr) {
        case HLT: {
            running = 0;

            break;
        }
        case PSH: {
            registers[SP]++;
            stack[registers[SP]] = program[++registers[IP]];

            break;
        }
        case PSHR: {
            int value = registers[program[++registers[IP]]];

            stack[++registers[SP]] = value;

            break;
        }
        case POP: {
            printf("The value popped is %d\n", stack[registers[SP]]);
            registers[SP]--;

            break;
        }
        case POPR: {
            int reg = program[++registers[IP]];
            int value = stack[registers[SP]--];

            set_register(reg, value);

            break;
        }
        case ADD: {
            int operand1 = stack[registers[SP]--];
            int operand2 = stack[registers[SP]--];
            int result = operand1 + operand2;

            registers[SP]++;
            stack[registers[SP]] = result;

            break;
        }
        case ADDR: {
            int reg1 = program[++registers[IP]];
            int reg2 = program[++registers[IP]];

            int sum = registers[reg1] + registers[reg2];

            set_register(reg1, sum);

            break;
        }
        case CMPR:{
            int value1 = registers[program[++registers[IP]]];
            int value2 = registers[program[++registers[IP]]];

            if (value1 == value2) 
                set_flags(ZF, 1);
            else 
                set_flags(ZF, 0);

            break;
        }
        case CMC: {
            int value = flags[CF];

            if (value) 
                set_flags(CF, 0);
            else
                set_flags(CF, 1);

            break;
        }
        case CLI: {
            set_flags(IF, 0);

            break;
        }
        case CLC: {
            set_flags(CF, 0);

            break;
        }
        case CLZ: {
            set_flags(ZF, 0);

            break;
        }
        case DEC: {
            registers[program[++registers[IP]]]--;

            break;
        }
        case DIV: {
            int operand1 = stack[registers[SP]--];
            int operand2 = stack[registers[SP]--];

            int result = operand1 / operand2;

            // TODO: implement interrupts.

            stack[++registers[SP]] = result;

            break;
        }
        case DIVR: {
            int reg1 = program[++registers[IP]];
            int reg2 = program[++registers[IP]];
            
            int result = registers[reg1] / registers[reg2];

            // TODO: implement interrupts.
            
            set_register(reg1, result);

            break;
        }
        case INC: {
            registers[program[++registers[IP]]]++;

            break;
        }
        case JMP: {
            set_register(IP, stack[registers[SP]--]);

            break;
        }              
        case MOV: {
            int reg = program[++registers[IP]];
            int value = registers[program[++registers[IP]]];

            set_register(reg, value);

            break;
        }
        case MUL: {
            int value1 = stack[registers[SP]--];
            int value2 = stack[registers[SP]--];

            int result = value1 * value2;

            stack[++registers[SP]] = result;

            break;
        }
        case MULR: {
            int reg1 = program[++registers[IP]];
            int reg2 = program[++registers[IP]];

            int result = registers[reg1] * registers[reg2];

            set_register(reg1, result);

            break;
        }
        case SET: {
            int reg = program[++registers[IP]];
            int value = program[++registers[IP]];

            set_register(reg, value);

            break;
        }
        case STC: {
            set_register(CF, 1);

            break;
        }
        case STI: {
            set_register(IF, 1);

            break;
        }
        case SUB: {
            int operand1 = stack[registers[SP]--];
            int operand2 = stack[registers[SP]--];

            int result = operand1 - operand2;

            stack[++registers[SP]] = result;

            break;
        }
        case SUBR: {
            int reg1 = program[++registers[IP]];
            int reg2 = program[++registers[IP]];

            int result = registers[reg1] - registers[reg2];

            set_register(reg1, result);

            break;
        }
    }
}

int execute(void)
{
    registers[SP] = -1;
    registers[IP] = 0;

    while (running) {
        evaluate(fetch());

        registers[IP]++;
    }

    return 0;
}
