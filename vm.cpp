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
	while(vm->instr_ptr < vm->instr_length) {
		Instr instr = vm->instr_buf[vm->instr_ptr];
		Instr_execute(vm, instr);
	}
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

void Vm_dump_stack(Vm * vm) {
	std::cout << "==== Stack Dump ====\n";
	std::cout << "top: " << vm->val_top << "\n";
	std::cout << "len: " << vm->val_len << "\n";
	for(int i = vm->val_top - 1;i >= 0;--i) {
		std::cout << "[" << i << "] {";
		if(vm->val_buf[i].type == TYPE_UINT)
			std::cout << vm->val_buf[i].uint_value;
		else if(vm->val_buf[i].type == TYPE_INT)
			std::cout << vm->val_buf[i].int_value;
		else
			std::cout << vm->val_buf[i].float_value;
		std::cout << ", " <<  ValueTypeToString[vm->val_buf[i].type] << "}" << "\n";
	}
	std::cout << "\n";
}

void Vm_dump_instr(Vm * vm) {
	std::cout << "==== Instruction Dump ====\n";
	std::cout << "instr: " << vm->instr_ptr << "\n";
	for(unsigned int i = 0;i < vm->instr_length; ++i) {
		Instr instr = vm->instr_buf[i];
		std::cout << "{" << InstrToString[instr.op] << ", ";
		if(instr.arg.type == TYPE_UINT)
			std::cout << "{" << instr.arg.uint_value;
		else if(instr.arg.type == TYPE_INT)
			std::cout << "{" << instr.arg.int_value;
		else
			std::cout << "{" << instr.arg.float_value;
		std::cout << ", " <<  ValueTypeToString[instr.arg.type] << "}}";
		if(i == vm->instr_ptr) 
			std::cout << " <--- instr_ptr";
		std::cout << "\n";
	}
	std::cout << "\n";
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

Value Value_and(Value v1, Value v2) {
	return {v1.uint_value && v2.uint_value, TYPE_UINT};
}

Value Value_or(Value v1, Value v2) {
	return {v1.uint_value || v2.uint_value, TYPE_UINT};
}

Value Value_not(Value v) {
	return {!v.uint_value, TYPE_UINT};
}

bool Value_eq(Value v1, Value v2) {
	if(v1.uint_value == v2.uint_value && v1.type == v2.type)
		return true;
	return false;
}

bool Value_neq(Value v1, Value v2) {
	return !Value_eq(v1, v2);
}

bool Value_gt(Value v1, Value v2) {
	if(v1.type != v2.type) {
		// @TODO: error?
		return false;
	}
	if(v1.type == TYPE_UINT)
		return v1.uint_value > v2.uint_value;
	if(v1.type == TYPE_INT)
		return v1.int_value > v2.int_value;
	if(v1.type == TYPE_FLOAT)
		return v1.float_value > v2.float_value;
	return false;
}

bool Value_lt(Value v1, Value v2) {
	if(v1.type != v2.type) {
		// @TODO: error?
		return false;
	}
	if(v1.type == TYPE_UINT)
		return v1.uint_value < v2.uint_value;
	if(v1.type == TYPE_INT)
		return v1.int_value < v2.int_value;
	if(v1.type == TYPE_FLOAT)
		return v1.float_value < v2.float_value;
	return false;
}

bool Value_gteq(Value v1, Value v2) {
	return !Value_lt(v1, v2);
}

bool Value_lteq(Value v1, Value v2) {
	return !Value_gt(v1, v2);
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
			// pops 2 values off stack and conditional jump to argument location
			// @TODO: what if argument is not an address?
			Value addr = instr.arg;
			if(addr.type != TYPE_UINT) {
				std::cout << "not address ?? \n";
				// @TODO: do something, exit ?
			}
			Value arg1 = Vm_pop(vm);
			Value arg2 = Vm_pop(vm);
			if(Value_eq(arg1, arg2))
				vm->instr_ptr = instr.arg.uint_value;
			else
				++vm->instr_ptr;
		} break;
		case JUMP_NEQ: {
			// pops 2 values off stack and conditional jump to argument location
			// @TODO: what if argument is not an address?
			Value addr = instr.arg;
			if(addr.type != TYPE_UINT) {
				std::cout << "not address ?? \n";
				// @TODO: do something, exit ?
			}
			Value arg1 = Vm_pop(vm);
			Value arg2 = Vm_pop(vm);
			if(Value_neq(arg1, arg2))
				vm->instr_ptr = instr.arg.uint_value;
			else
				++vm->instr_ptr;
		} break;
		case JUMP_GTEQ: {
			// pops 2 values off stack and conditional jump to argument location
			// @TODO: what if argument is not an address?
			Value addr = instr.arg;
			if(addr.type != TYPE_UINT) {
				std::cout << "not address ?? \n";
				// @TODO: do something, exit ?
			}
			Value arg1 = Vm_pop(vm);
			Value arg2 = Vm_pop(vm);
			if(Value_gteq(arg1, arg2))
				vm->instr_ptr = instr.arg.uint_value;
			else
				++vm->instr_ptr;
		} break;
		case JUMP_LTEQ: {
			// pops 2 values off stack and conditional jump to argument location
			// @TODO: what if argument is not an address?
			Value addr = instr.arg;
			if(addr.type != TYPE_UINT) {
				std::cout << "not address ?? \n";
				// @TODO: do something, exit ?
			}
			Value arg1 = Vm_pop(vm);
			Value arg2 = Vm_pop(vm);
			if(Value_lteq(arg1, arg2))
				vm->instr_ptr = instr.arg.uint_value;
			else
				++vm->instr_ptr;
		} break;
		case JUMP_GT: {
			// pops 2 values off stack and conditional jump to argument location
			// @TODO: what if argument is not an address?
			Value addr = instr.arg;
			if(addr.type != TYPE_UINT) {
				std::cout << "not address ?? \n";
				// @TODO: do something, exit ?
			}
			Value arg1 = Vm_pop(vm);
			Value arg2 = Vm_pop(vm);
			if(Value_gt(arg1, arg2))
				vm->instr_ptr = instr.arg.uint_value;
			else
				++vm->instr_ptr;
		} break;
		case JUMP_LT: {
			// pops 2 values off stack and conditional jump to argument location
			// @TODO: what if argument is not an address?
			Value addr = instr.arg;
			if(addr.type != TYPE_UINT) {
				std::cout << "not address ?? \n";
				// @TODO: do something, exit ?
			}
			Value arg1 = Vm_pop(vm);
			Value arg2 = Vm_pop(vm);
			if(Value_lt(arg1, arg2))
				vm->instr_ptr = instr.arg.uint_value;
			else
				++vm->instr_ptr;
		} break;
		default: {
			std::cout << "shitty instruction!!\n";
		}
	}
}
