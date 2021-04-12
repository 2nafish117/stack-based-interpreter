#pragma once

// All possible ops the VM can execute
enum Op {
	// push and pop from execution stack
	PUSH = 0,
	POP,

	// Arithmatic operations
	ADD,
	SUB,
	MUL,
	DIV,

	// Logical operations
	AND,
	OR,
	NOT,
	XOR,

	// Jump ops
	JUMP,
	JUMP_EQ,
	JUMP_NEQ,
	JUMP_GTEQ,
	JUMP_LTEQ,
	JUMP_GT,
	JUMP_LT,

	NUM_INSTR
};

const char* const InstrToString[NUM_INSTR] = {
	"PUSH",
	"POP",

	// Arithmatic operations
	"ADD",
	"SUB",
	"MUL",
	"DIV",

	// Logical operations
	"AND",
	"OR",
	"NOT",
	"XOR",

	// Jump ops
	"JUMP",
	"JUMP_EQ",
	"JUMP_NEQ",
	"JUMP_GTEQ",
	"JUMP_LTEQ",
	"JUMP_GT",
	"JUMP_LT"
};
