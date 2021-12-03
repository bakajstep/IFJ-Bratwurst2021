//
// Created by adam on 03.12.21.
//

#include "code_generator.h"

/*
 * ----------------------USEFULL FUNCTIONS-----------------------
 */

char* convert_string(char* str_toconvert){
    char* string = str_toconvert;
    string_ptr_t string_res = string_init();

    while(*string != '\0'){
        //iteruji přes vstupní string
        if(*string == 92){
            string_append_character(string_res, '\\');
            string_append_character(string_res, '0');
            string_append_character(string_res, '9');
            string_append_character(string_res, '2');
        }else if(*string == 35){
            string_append_character(string_res, '\\');
            string_append_character(string_res, '0');
            string_append_character(string_res, '3');
            string_append_character(string_res, '5');
        }else if(*string <= 32){
            string_append_character(string_res, '\\');
            string_append_character(string_res, '0');
            string_append_character(string_res, ((*string / 10) + 48));
            string_append_character(string_res, ((*string % 10) + 48));
        }else{
            string_append_character(string_res, *string);
        }

        string++;
    }
    return string_res->string;
}

/*
 * ----------------------BUILD IN FUNCTIONS-----------------------
 */

void codeGen_reads(){
    printf("LABEL reads\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("POPS\n");
    printf("DEFVAR TF@out\n");
    printf("READ TF@out string\n");
    printf("PUSHS TF@out\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
}

void codeGen_readi(){
    printf("LABEL readi\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("POPS\n");
    printf("DEFVAR TF@out\n");
    printf("READ TF@out int\n");
    printf("PUSHS TF@out\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
}

void codeGen_readn(){
    printf("LABEL readn\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("POPS\n");
    printf("DEFVAR TF@out\n");
    printf("READ TF@out float\n");
    printf("PUSHS TF@out\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
}

void codeGen_tointeger(){
    printf("LABEL toiteger\n");
    printf("POPS\n");
    printf("FLOAT2INTS\n");
    printf("RETURN\n");
}

void codeGen_substr(){

}

void codeGen_ord(){

}

void codeGen_chr(){

}


/*
 * ----------------------GENERATOR START-----------------------
 */

static int ifCounter = -1;
static int whileCounter = -1;

void codeGen_init(){
    printf(".IFJcode20\n");
    printf("DEFVAR GF@expr\n");
    printf("DEFVAR GF@tmp1\n");
    printf("DEFVAR GF@tmp2\n");
    printf("DEFVAR GF@tmp3\n");
    printf("DEFVAR GF@tmp4\n");
    printf("JUMP main\n");
    printf("LABEL _div_0\n");
    printf("EXIT int@9\n");
}

void generate_build_in_function(){
    codeGen_reads();
    codeGen_readi();
    codeGen_readn();
    codeGen_tointeger();
    codeGen_substr();
    codeGen_ord();
    codeGen_chr();
}

/*
 * ----------------------MAIN-----------------------
 */

void codeGen_main_start(){
    printf("LABEL main\nCREATEFRAME\n");
}

void codeGen_main_end(){
    printf("LABEL main$end");
    printf("CLEARS");
}


/*
 * ----------------------VAR-----------------------
 */

void codeGen_push_var(char* name){
    printf("PUSH TF@%s\n", name);
}

void codeGen_push_string(char* value){
    printf("PUSH string@%s\n", convert_string(value));
}

void codeGen_push_int(int value){
    printf("PUSH int@%d\n", value);
}

void codeGen_push_float(double value){
    printf("PUSH float@%a\n", value);
}

void codeGen_new_var(char* name){
    printf("DEFVAR TF@%s\n", name);
}

void codeGen_assign_var(char* name){
    printf("POPS TF@%s", name);
}

/*
 * ----------------------IF-----------------------
 */

void codeGen_if_start(){
    ifCounter++;
    printf("JUMPIFNEQ if$%d$else GF@expr bool@true\n", ifCounter);

}

void codeGen_if_else(){
    printf("JUMP if$%d$end\n", ifCounter);
    printf("LABEL if$%d$else\n", ifCounter);
}

void codeGen_if_end(){
    printf("LABEL if$%d$end\n", ifCounter);
    ifCounter--;
}

/*
 * ----------------------WHILE-----------------------
 */

void codeGen_while_body_start(){
    whileCounter++;
    printf("LABEL while$%d$start\n", whileCounter);
}

void codeGen_while_start(){
    printf("JUMPIFNEQ while$%d$end GF@expr bool@false\n", whileCounter);
}

void codeGen_while_end(){
    printf("JUMP while$%d$start\n", whileCounter);
    printf("LABEL while$%d$end\n", whileCounter);
    whileCounter--;
}


/*
 * ----------------------FUNC-----------------------
 */

void codeGen_function_start(char* name){
    printf("JUMP %s$end\nLABEL %s\nPUSHFRAME\nCREATEFRAME\n", name, name);
}

void codeGen_function_return(){
    printf("POPFRAME\nRETURN\n");
}

void codeGen_function_end(char* name){
    printf("POPFRAME\nRETURN\nLABEL %s$end\n", name);
}

void codeGen_function_call(char* name, int parameters){
    printf("PUSH int@%i\n", parameters);
    printf("CALL %s\n", name);
}

/*
 * ----------------------STACK OPERATION-----------------------
 */

void generate_operation(psa_rules_enum operation){
    switch (operation){
        case NT_PLUS_NT:
            //rule E -> E + E
            printf("ADDS\n");
            break;
        case NT_MINUS_NT:
            //rule E -> E - E
            printf("SUBS\n");
            break;
        case NT_MUL_NT:
            // rule E -> E * E
            printf("MULS\n");
            break;
        case NT_DIV_NT:
            // rule E -> E / E
            printf("DIVS\n");
            break;
        case NT_IDIV_NT:
            // rule E -> E // E
            printf("IDIVS\n");
            break;
        case NT_CONCAT_NT:
            // rule E -> E .. E
            printf("POPS GF@tmp1\n");
            printf("POPS GF@tmp2\n");
            printf("CONCAT GF@tmp3 GF@tmp1 GF@tmp2\n");
            printf("PUSHS GF@tmp3\n");
            break;
        case NT_EQ_NT:
            // rule E -> E == E
            printf("EQS\n");
            break;
        case NT_NEQ_NT:
            // rule E -> E ~= E
            printf("NOT EQS\n");
            break;
        case NT_LEQ_NT:
            // rule E -> E <= E
            printf("GTS\nNOTS\n");
            break;
        case NT_GEQ_NT:
            // rule E -> E >= E
            printf("LTS\nNOTS\n");
            break;
        case NT_LTN_NT:
            // rule E -> E < E
            printf("LTS\n");
            break;
        case NT_GTN_NT:
            // rule E -> E > E
            printf("GTS\n");
            break;
        case NT_HASHTAG:
            // rule E -> #E
            printf("POPS GF@tmp1\n");
            printf("STRLEN GF@tmp4 GF@tmp1\n");
            printf("PUSHS GF@tmp4");
            break;
        default:break;
    }
}