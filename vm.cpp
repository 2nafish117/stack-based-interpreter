#include "vm.h"

void Vm_init(Vm* vm, Instr* instr, unsigned int instr_len) {
	vm->val_buf = (Value*) malloc(sizeof(Value) * INITIAL_STACK_SIZE);
	vm->val_len = INITIAL_STACK_SIZE;
	vm->val_top = 0;
	vm->instr_buf = instr;
	vm->instr_length = instr_len;
	vm->instr_ptr = 0;
}

void Vm_destroy(Vm* vm) {
	free(vm->val_buf);
	vm->val_len = 0;
	vm->val_top = 0;
	vm->instr_buf = NULL;
	vm->instr_length = 0;
	vm->instr_ptr = 0;
}

int Vm_execute(Vm* vm) {
	Instr instr = vm->instr_buf[vm->instr_ptr];
	Instr_execute(vm, instr);
	// dont forget to increment or jump the instruction pointer!!
}

void Vm_push(Vm* vm, Value v) {
	//@TODO check bounds
	vm->val_buf[vm->val_top] = v;
	++vm->val_top;
}

Value Vm_pop(Vm* vm) {
	// @TODO: check bounds
	--vm->val_top;
	Value res = vm->val_buf[vm->val_top];
	return res;
}


Value Value_add(Value v1, Value v2) {
	if(v1.type != v2.type)
		return {0};
	if(v1.type == TYPE_UINT)
		return {v1.uint_value + v2.uint_value, TYPE_UINT};
	if(v1.type == TYPE_INT)
		return {v1.int_value + v2.int_value, TYPE_INT};
	if(v1.type == TYPE_FLOAT)
		return {v1.float_value + v2.float_value, TYPE_FLOAT};
	return {0};
}

Value Value_sub(Value v1, Value v2) {
	if(v1.type != v2.type)
		return {0};
	if(v1.type == TYPE_UINT)
		return {v1.uint_value - v2.uint_value, TYPE_UINT};
	if(v1.type == TYPE_INT)
		return {v1.int_value - v2.int_value, TYPE_INT};
	if(v1.type == TYPE_FLOAT)
		return {v1.float_value - v2.float_value, TYPE_FLOAT};
	return {0};
}

Value Value_mul(Value v1, Value v2) {
	if(v1.type != v2.type)
		return {0};
	if(v1.type == TYPE_UINT)
		return {v1.uint_value * v2.uint_value, TYPE_UINT};
	if(v1.type == TYPE_INT)
		return {v1.int_value * v2.int_value, TYPE_INT};
	if(v1.type == TYPE_FLOAT)
		return {v1.float_value * v2.float_value, TYPE_FLOAT};
	return {0};
}

// @TODO: what if denominator is 0?
Value Value_div(Value v1, Value v2) {
	if(v1.type != v2.type)
		return {0};
	if(v1.type == TYPE_UINT)
		return {v1.uint_value / v2.uint_value, TYPE_UINT};
	if(v1.type == TYPE_INT)
		return {v1.int_value / v2.int_value, TYPE_INT};
	if(v1.type == TYPE_FLOAT)
		return {v1.float_value / v2.float_value, TYPE_FLOAT};
	return {0};
}

void Instr_execute(Vm* vm, Instr instr) {
	switch(instr.op) {
		case PUSH: {
			// push a value onto the execution stack
			// requires 1 argument
			Vm_push(vm, instr.arg);
			++vm->instr_ptr;
		} break;
		case POP: {
			// pop a value from the execution stack, and throw it away
			// requires 0 argument
			Vm_pop(vm);
			++vm->instr_ptr;
		} break;
		case ADD: {
			// pop 2 values from stack and pushes the sum onto the stack
			Value arg1 = Vm_pop(vm);
			Value arg2 = Vm_pop(vm);
			Vm_push(vm, Value_add(arg1, arg2));
			++vm->instr_ptr;
		} break;
		case SUB: {
			// pop 2 values from stack and pushes the sub onto the stack
			Value arg1 = Vm_pop(vm);
			Value arg2 = Vm_pop(vm);
			Vm_push(vm, Value_sub(arg1, arg2));
			++vm->instr_ptr;
		} break;
		case MUL: {
			// pop 2 values from stack and pushes the mul onto the stack
			Value arg1 = Vm_pop(vm);
			Value arg2 = Vm_pop(vm);
			Vm_push(vm, Value_mul(arg1, arg2));
			++vm->instr_ptr;
		} break;
		case DIV: {
			// pop 2 values from stack and pushes the div onto the stack
			Value arg1 = Vm_pop(vm);
			Value arg2 = Vm_pop(vm);
			Vm_push(vm, Value_div(arg1, arg2));
			++vm->instr_ptr;
		} break;
		case AND: {
			// pop 2 values from stack and pushes the and onto the stack
			Value arg1 = Vm_pop(vm);
			Value arg2 = Vm_pop(vm);
			Vm_push(vm, Value_and(arg1, arg2));
			++vm->instr_ptr;
		} break;
		case OR: {
			// pop 2 values from stack and pushes the or onto the stack
			Value arg1 = Vm_pop(vm);
			Value arg2 = Vm_pop(vm);
			Vm_push(vm, Value_or(arg1, arg2));
			++vm->instr_ptr;
		} break;
		case NOT: {
			// pop 1 value from stack and pushes the not onto the stack
			Value arg = Vm_pop(vm);
			Vm_push(vm, Value_not(arg));
			++vm->instr_ptr;
		} break;
		case XOR: {
			// @NotImplemented yet
		} break;
		case JUMP: {
			// unconditional jump to argument location
			// @TODO: what if argument is not an address?
			vm->instr_ptr = instr.arg.uint_value;
		} break;
		case JUMP_EQ: {
			// pops a value off stack and conditional jump to argument location
			// @TODO: what if argument is not an address?
			Value arg = Vm_pop(vm);
			if(arg.)
		} break;
		case JUMP_NEQ: {

		} break;
		case JUMP_GTEQ: {

		} break;
		case JUMP_LTEQ: {

		} break;
		case JUMP_GT: {

		} break;
		case JUMP_LT: {

		} break;
		default: {

		}
	}
}
