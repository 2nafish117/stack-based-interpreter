#pragma once

#include <cstdlib>
#include <iostream>
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
void Vm_dump_stack(Vm * vm);
void Vm_dump_instr(Vm * vm);

enum ValueType {
	TYPE_UINT = 0,
	TYPE_INT,
	TYPE_FLOAT
};

const char* const ValueTypeToString[] = {
	"TYPE_UINT",
	"TYPE_INT",
	"TYPE_FLOAT"
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

#define VM_NULL {0, TYPE_UINT}

Value Value_add(Value v1, Value v2);
Value Value_sub(Value v1, Value v2);
Value Value_mul(Value v1, Value v2);
Value Value_div(Value v1, Value v2);
Value Value_and(Value v1, Value v2);
Value Value_or(Value v1, Value v2);
Value Value_not(Value v);
bool Value_eq(Value v1, Value v2);
bool Value_neq(Value v1, Value v2);
bool Value_gt(Value v1, Value v2);
bool Value_lt(Value v1, Value v2);
bool Value_gteq(Value v1, Value v2);
bool Value_lteq(Value v1, Value v2);

struct Instr {
	Op op;
	Value arg;
};

void Instr_execute(Vm* vm, Instr instr);