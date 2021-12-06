//
// Created by adam on 29.11.21.
//

#ifndef IFJ_BRATWURST2021_CODE_GENERATOR_H
#define IFJ_BRATWURST2021_CODE_GENERATOR_H

#include <stdio.h>
#include <string.h>
#include "scanner.h"
#include "symtable.h"
#include "error.h"
#include "dll.h"
#include "string.h"
#include "psa.h"

#define TABLE_SIZE 10
#define INST_LEN 100

typedef struct shadowStack{
    char* nameScale;
    int scale;
    char* name;
    int inicialized;
    struct shadowStack* next;
} shadowStack_t;

void generate_errorOp();
void generate_operation(psa_rules_enum operation);
void generate_IntToFloat1();
void generate_IntToFloat2();
void codeGen_init();
void codeGen_built_in_function();
void codeGen_main_start();
void codeGen_main_end();
void codeGen_push_var(char* name);
void codeGen_push_string(char* value);
void codeGen_push_int(int value);
void codeGen_push_float(double value);
void codeGen_push_nil();
void codeGen_new_var(char* name);
void codeGen_assign_var(char* name);
void codeGen_if_start();
void codeGen_if_else();
void codeGen_if_end();
void codeGen_while_body_start();
void codeGen_while_start();
void codeGen_while_end();
void codeGen_function_start(char* name);
void codeGen_function_return();
void codeGen_function_end(char* name);
void codeGen_function_call(char* name, unsigned parameters);

#endif //IFJ_BRATWURST2021_CODE_GENERATOR_H
