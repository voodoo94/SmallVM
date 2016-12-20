#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "loader.h"

int program[200];

int parserAndLoad(char[]);
int isInstruction(char*);
int isOperand(char*);
int getOpcode(char*);
int getCode(char*);

extern int execute(void);

int isInstruction(char *str)
{
	int i;

	for (i = 0; i < sizeof(conversion) / sizeof(conversion[0]); i++) {
		if (!strcmp(str, conversion[i].instruction_str))
			return 1;
	}

	return 0;
}

int isOperand(char *str)
{
	int i;

	for (i = 0; i < sizeof(conversion_register) / sizeof(conversion_register[0]); i++) {
		if (!strcmp(str, conversion_register[i].register_str))
			return 1;
	}

	for (i = 0; i < sizeof(conversion_flag) / sizeof(conversion_flag[0]); i++) {
		if (!strcmp(str, conversion_flag[i].flag_str))
			return 1;
	}

	return 0;
}

int getCode(char *str)
{
	int i;

	for (i = 0; i < sizeof(conversion_register) / sizeof(conversion_register[0]); i++) {
		if (!strcmp(str, conversion_register[i].register_str))
			return conversion_register[i].reg;
	}

	return -1;
}

int getOpcode(char *str)
{
	int i;

	for (i = 0; i < sizeof(conversion) / sizeof(conversion[0]); i++) {
		if (!strcmp(str, conversion[i].instruction_str))
			return conversion[i].instruction;
	}

	return -1;
}

int parseAndLoad(char* file_name)
{
	char code[20];

	int loader_pointer;
	int opcode;
	int operand_code;
	int number;
	int error;

	FILE *fp;

	loader_pointer = 0;
	error = 0;

	fp = fopen(file_name, "r");

	do {
		fscanf(fp, "%s", code);
		if (isInstruction(code)) {
			opcode = getOpcode(code);

			if (opcode == -1) {
				error = 1;

				break;
			}

			program[loader_pointer++] = opcode;
		} else if (isOperand(code)) {
			operand_code = getCode(code);

			if (operand_code == -1) {
				error = 1;

				break;
			}

			program[loader_pointer++] = operand_code;
		} else {
			sscanf(code, "%d", &number);
			program[loader_pointer++] = number;
		}
	} while (!feof(fp));

	if (error != 0) {
		return -1;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	char *file_name;

	int return_status;

	if (argc <= 1) {
		printf("Error: Missing file name.\n");

		return 0;
	} 

	return_status = parseAndLoad(argv[1]);

	if (return_status == -1) {
		printf("Error: Syntax error.\n");

		return 0;
	}

	execute();

	return 0;
}