//////////////////////////////////////////
/*
  Simple Virtual Machine to learn basic VM functions,
  prior to implementing a full-fledged 6502 (NES) architecture VM.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_STACK_SIZE 1024  // Maximum size of the stack
#define BINARY_OP(VM, op)  { int a = pop(VM); int b = pop(VM); push(VM, b op a); }

// Enumeration for the instruction set
typedef enum {
    INST_PUSH,
    INST_POP,
    INST_DUP,
    INST_SWAP,
    INST_ADD,
    INST_SUB,
    INST_MUL,
    INST_DIV,
    INST_PRINT,
} InstructionType;

// Structure to represent an instruction
typedef struct {
    InstructionType type;
    int value;  // Value (only relevant for push instruction)
} Instruction;

// Structure to represent the virtual machine
typedef struct {
    int stack[MAX_STACK_SIZE];   // Stack to store values
    int stack_size;              // Current size of the stack
    size_t program_size;         // Number of instructions in the program
    Instruction* instructions;   // Array of instructions (the program)
} VirtualMachine;

// Macros to define different instructions
#define DEF_INST_PUSH(value) {.type = INST_PUSH, .value = value}
#define DEF_INST_POP()       {.type = INST_POP}
#define DEF_INST_DUP()       {.type = INST_DUP}
#define DEF_INST_SWAP()      {.type = INST_SWAP}
#define DEF_INST_ADD()       {.type = INST_ADD}
#define DEF_INST_SUB()       {.type = INST_SUB}
#define DEF_INST_MUL()       {.type = INST_MUL}
#define DEF_INST_DIV()       {.type = INST_DIV}
#define DEF_INST_PRINT()     {.type = INST_PRINT}

// Program to be executed by the virtual machine
Instruction program[] = {
   {.type = INST_PUSH, .value = 13},
   {.type = INST_PUSH, .value = 14},
   { .type = INST_MUL },
   { .type = INST_PRINT }
};
#define PROGRAM_SIZE (sizeof(program) / sizeof(program[0]))

// Function to push a value onto the stack
void push(VirtualMachine* vm, int value) {
    if (vm->stack_size >= MAX_STACK_SIZE) {
        fprintf(stderr, "ERROR: Stack Overflow\n");
        exit(1);
    }
    vm->stack[vm->stack_size++] = value;
}

// Function to pop a value from the stack
int pop(VirtualMachine* vm) {
    if (vm->stack_size <= 0) {
        fprintf(stderr, "ERROR: Stack Underflow\n");
        exit(1);
    }
    return vm->stack[--vm->stack_size];
}

// Function to print the current stack
void print_stack(VirtualMachine* vm) {
    for (int i = vm->stack_size - 1; i >= 0; i--) {
        printf("%d\n", vm->stack[i]);
    }
}

// Function to write the program to a binary file
void write_program_to_file(VirtualMachine* vm, const char* file_path) {
    FILE* file = fopen(file_path, "wb");
    if (file == NULL) {
        fprintf(stderr, "ERROR: Could not open file for writing: %s\n", file_path);
        exit(1);
    }
    fwrite(vm->instructions, sizeof(vm->instructions[0]), PROGRAM_SIZE, file);
    fclose(file);
}

// Function to read the program from a binary file
VirtualMachine* read_program_from_file(VirtualMachine* vm, const char* file_path) {
    FILE* file = fopen(file_path, "rb");
    if (file == NULL) {
        fprintf(stderr, "ERROR: Could not open file for reading: %s\n", file_path);
        exit(1);
    }

    // Allocate memory for instructions
    Instruction* instructions = malloc(sizeof(Instruction) * MAX_STACK_SIZE);
    if (instructions == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed for instructions\n");
        exit(1);
    }

    // Determine file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Read instructions from file
    fread(instructions, sizeof(Instruction), file_size / sizeof(Instruction), file);
    vm->program_size = file_size / sizeof(Instruction);
    vm->instructions = instructions;

    fclose(file);
    return vm;
}

// Main function to run the virtual machine
int main() {
    // Initialize the virtual machine
    VirtualMachine* vm = malloc(sizeof(VirtualMachine));
    if (vm == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed for virtual machine\n");
        exit(1);
    }

    vm->instructions = program;
    vm->stack_size = 0;

    // Write the program to a binary file
    write_program_to_file(vm, "program.bin");

    // Read the program back from the binary file
    vm = read_program_from_file(vm, "program.bin");

    // Execute the instructions in the program
    for (size_t instruction_pointer = 0; instruction_pointer < vm->program_size; instruction_pointer++) {
        Instruction current_instruction = vm->instructions[instruction_pointer];

        switch (current_instruction.type) {
        case INST_PUSH:
            push(vm, current_instruction.value);
            break;
        case INST_POP:
            pop(vm);
            break;
        case INST_DUP: {
            int value = pop(vm);
            push(vm, value);
            push(vm, value);
            break;
        }
        case INST_SWAP: {
            int first_operand = pop(vm);
            int second_operand = pop(vm);
            push(vm, first_operand);
            push(vm, second_operand);
            break;
        }
        case INST_ADD:
            BINARY_OP(vm, +);
            break;
        case INST_SUB:
            BINARY_OP(vm, -);
            break;
        case INST_MUL:
            BINARY_OP(vm, *);
            break;
        case INST_DIV: {
            int a = pop(vm);
            int b = pop(vm);
            if (a == 0) {
                fprintf(stderr, "ERROR: Division by zero\n");
                exit(1);
            }
            push(vm, b / a);
            break;
        }
        case INST_PRINT:
            printf("Top of stack: %d\n", pop(vm));
            break;
        default:
            fprintf(stderr, "ERROR: Unknown instruction\n");
            exit(1);
        }
    }

    // Clean up
    free(vm->instructions);
    free(vm);

    return 0;
}