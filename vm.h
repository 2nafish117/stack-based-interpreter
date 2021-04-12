#pragma once

#include <cstdlib>
#include "ops.h"

#define INITIAL_STACK_SIZE 1024

struct Vm;
struct Value;
struct Instr;

struct Vm {
	// execution stack
	Value* val_buf;
	unsigned int val_len;
	// stack top
	int val_top;

	// instruction buffer
	Instr* instr_buf;
	unsigned int instr_length;
	// instruction pointer
	unsigned int instr_ptr;
};

void Vm_init(Vm* vm, Instr* instr, unsigned int instr_len);
void Vm_destroy(Vm* vm);
int Vm_execute(Vm* vm);
void Vm_push(Vm* vm, Value v);
Value Vm_pop(Vm* vm);

enum ValueType {
	TYPE_UINT = 0,
	TYPE_INT,
	TYPE_FLOAT
};

// general value struct, can hold addresses or int, float values
// 0 is NULL and false, non 0 is true (or maybe {0} is NULL and {0, x} is falsey?)
struct Value {
	union {
		unsigned int uint_value;
		int int_value;
		float float_value;
	};
	ValueType type;
};

Value Value_add(Value v1, Value v2);
Value Value_sub(Value v1, Value v2);
Value Value_mul(Value v1, Value v2);
Value Value_div(Value v1, Value v2);

struct Instr {
	Op op;
	Value arg;
};

void Instr_execute(Vm* vm, Instr instr);