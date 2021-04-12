#include <iostream>

#include "vm.h"

int main() {
	Vm vm;
	Instr instructions[] = {
		{PUSH, {3, TYPE_INT}},
		{PUSH, {3, TYPE_INT}},
		{ADD, VM_NULL}
	};

	Vm_init(&vm, instructions, sizeof(instructions) / sizeof(Instr));
	Vm_dump_stack(&vm);
	Vm_dump_instr(&vm);

	Vm_execute(&vm);
	Vm_dump_stack(&vm);
	Vm_dump_instr(&vm);

	Vm_destroy(&vm);
	return 0;
}