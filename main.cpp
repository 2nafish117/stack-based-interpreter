#include <iostream>

#include "vm.h"

int main() {
	Vm vm;
	Instr instructions[] = {
		{PUSH, 4},
		{PUSH, 2},
		{ADD, NULL}
	};

	Vm_init(&vm, instructions, sizeof(instructions) / sizeof(Instr));
	Vm_execute(&vm);
	Vm_destroy(&vm);

	return 0;
}