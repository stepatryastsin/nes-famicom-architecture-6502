#pragma warning(disable : 4996)
#include<stdio.h>
#include<stdlib.h>

//////////////////////////////////////////
/*
  Simple Virtual Machine to learn basic VM functions,
  prior to implementing a full-fledged 6502 (NES) architecture VM.
*/

#define MAX_STACK_SIZE 1024    // Maximum stack size

// Error messages
#define STACK_OVERFLOW_ERROR "Error: Stack overflow."
#define STACK_UNDERFLOW_ERROR "Error: Stack underflow."

// Stack and its size
int stack[MAX_STACK_SIZE];
int stack_size = 0;

// VM instruction set
enum Instruction {
    INSTR_ADD,     // Perform addition
    INSTR_SUB,     // Perform subtraction
    INSTR_MUL,     // Perform multiplication
    INSTR_DIV,     // Perform division
    INSTR_MOD,     // Perform modulus operation
    INSTR_PUSH,    // Push a value onto the stack
    INSTR_POP,     // Pop a value off the stack
    INSTR_PRINT,   // Print the top value on the stack
    INSTR_DUP,     // Duplicate the top value on the stack
    INSTR_SWAP     // Swap the top two values
};

// Structure to define an instruction
struct Instr_s {
    enum Instruction type;    // Instruction type
    int value;                // Operand (if applicable)
};

// Macros for binary operations (pop two values, apply operation, push result)
#define BINARY_OP(op)  { int a = pop(); int b = pop(); push(b op a); }

// Instruction set for the VM program
struct Instr_s program[] = {
    {.type = INSTR_PUSH, .value = 13},   // Push 13 onto the stack
    {.type = INSTR_PUSH, .value = 15},   // Push 15 onto the stack
    {.type = INSTR_MUL},                 // Multiply top two values
    {.type = INSTR_PRINT},               // Print the result
    {.type = INSTR_PUSH, .value = 7},    // Push 7 onto the stack
    {.type = INSTR_ADD},                 // Add top two values
    {.type = INSTR_PRINT},               // Print the result
    {.type = INSTR_DUP},                 // Duplicate the top value
    {.type = INSTR_PRINT},               // Print duplicated value
    {.type = INSTR_SWAP},                // Swap the top two values
    {.type = INSTR_PRINT}                // Print the swapped top value
};

// Function prototypes
int pop();
void push(int a);
void writebinary(const char* file);
struct Instr_s* readbinary(const char* file);

// Main VM loop
int main() {
    writebinary("test.vm");  // Write the program to a binary file

    struct Instr_s* programs = readbinary("test.vm");  // Read the program back from the file

    // Execute each instruction in the read program
    for (int i = 0; i < sizeof(program) / sizeof(program[0]); i++) {
        switch (programs[i].type) {
        case INSTR_PUSH:
            push(programs[i].value);    // Push the value onto the stack
            break;
        case INSTR_PRINT:
            printf("%d\n", pop());      // Print the top value of the stack
            break;
        case INSTR_POP:
            pop();                      // Pop the top value off the stack
            break;
        case INSTR_ADD:
            BINARY_OP(+);               // Pop two values, add, push result
            break;
        case INSTR_SUB:
            BINARY_OP(-);               // Pop two values, subtract, push result
            break;
        case INSTR_MUL:
            BINARY_OP(*);               // Pop two values, multiply, push result
            break;
        case INSTR_DIV:
            BINARY_OP(/ );               // Pop two values, divide, push result
            break;
        case INSTR_MOD:
            BINARY_OP(%);               // Pop two values, mod, push result
            break;
        case INSTR_DUP: {
            int top = pop();            // Duplicate the top value
            push(top);
            push(top);
            break;
        }
        case INSTR_SWAP: {
            int a = pop();              // Swap the top two values
            int b = pop();
            push(a);
            push(b);
            break;
        }
        }
    }

    free(programs);  // Free the allocated memory for programs
}

// Pops a value off the stack
int pop() {
    if (stack_size < 0) {
        fprintf(stderr, STACK_UNDERFLOW_ERROR);
        exit(1);
    }
    return stack[--stack_size];
}

// Pushes a value onto the stack
void push(int a) {
    if (stack_size >= MAX_STACK_SIZE) {
        fprintf(stderr, STACK_OVERFLOW_ERROR);
        exit(1);
    }
    stack[stack_size++] = a;
}

// Writes the program to a binary file
void writebinary(const char* file) {
    FILE* fptr = fopen(file, "wb");
    if (fptr == NULL) {
        fprintf(stderr, "Error: Could not open file for writing.\n");
        exit(1);
    }
    fwrite(program, sizeof(struct Instr_s), sizeof(program) / sizeof(program[0]), fptr);
    fclose(fptr);
}

// Reads the program from a binary file
struct Instr_s* readbinary(const char* file) {
    FILE* fptr = fopen(file, "rb");
    if (fptr == NULL) {
        fprintf(stderr, "Error: Could not open file for reading.\n");
        exit(1);
    }
    // Find file size to allocate the correct amount of memory
    fseek(fptr, 0, SEEK_END);
    long fsize = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    struct Instr_s* inst = malloc(fsize);
    fread(inst, fsize, 1, fptr);
    fclose(fptr);

    return inst;
}
