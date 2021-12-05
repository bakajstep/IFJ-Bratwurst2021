//
// Created by adam on 03.12.21.
//

#include <ctype.h>

#include "code_generator.h"

/*
 * ----------------------USEFULL FUNCTIONS-----------------------
 */

char* convert_string(char* str_toconvert){
    char* string = str_toconvert;
    //char digits_buf[DIGITS_CNT];
    string_ptr_t string_res = string_init();


    while(*string != '\0'){
        //iteruji přes vstupní string
/*
        if (*string == '#' ||
            *string == '\\' ||            
            !isprint(*string))
        {
            if (*(string+1) != 0)
            {
                string_append_character(string_res, '\\');
                sprintf(digits_buf, "%03d", *(string));            
                
                for (int i = 0; i < DIGITS_CNT - 1; i++)
                {
                    string_append_character(string_res, digits_buf[i]);
                }                                            
            }
            else
            {
                string_append_character(string_res, *string);
            }                                          
        }
        else if (*string <= 32)
        {
            string_append_character(string_res, '\\');
            string_append_character(string_res, '0');
            string_append_character(string_res, ((*string / 10) + 48));
            string_append_character(string_res, ((*string % 10) + 48));
        }        
        else
        {
            string_append_character(string_res, *string);
        }
  */      
        
        if(*string == 92){                        
            string_append_character(string_res, '\\');
            
            if (!isdigit(*(string+1)))
            {
                string++;

                switch (*string)
                {
                case 'a':                    
                    string_append_character(string_res, '0');
                    string_append_character(string_res, '0');
                    string_append_character(string_res, '7');
                    break;

                case 'b':
                    string_append_character(string_res, '0');
                    string_append_character(string_res, '0');
                    string_append_character(string_res, '8');
                    break;
                
                case 'f':
                    string_append_character(string_res, '0');
                    string_append_character(string_res, '1');
                    string_append_character(string_res, '2');
                    break;
                
                case 'n':
                    string_append_character(string_res, '0');
                    string_append_character(string_res, '1');
                    string_append_character(string_res, '0');
                    break;

                case 'r':
                    string_append_character(string_res, '0');
                    string_append_character(string_res, '1');
                    string_append_character(string_res, '3');
                    break;

                case 't':
                    string_append_character(string_res, '0');
                    string_append_character(string_res, '0');
                    string_append_character(string_res, '9');
                    break;

                case 'v':
                    string_append_character(string_res, '0');
                    string_append_character(string_res, '1');
                    string_append_character(string_res, '1');
                    break;

                case '\\':
                    string_append_character(string_res, '0');
                    string_append_character(string_res, '9');
                    string_append_character(string_res, '2');
                    break;

                case '"':
                    string_append_character(string_res, '0');
                    string_append_character(string_res, '3');
                    string_append_character(string_res, '4');
                    break;

                case '\'':
                    string_append_character(string_res, '0');
                    string_append_character(string_res, '3');
                    string_append_character(string_res, '9');
                    break;                

                default:
                    break;
                }                                       
            }
            
            /*
            if (*(string+1) == 'n')
            {
                string_append_character(string_res, '\\');
                string_append_character(string_res, '0');
                string_append_character(string_res, '1');
                string_append_character(string_res, '0');
                string++;
            }
            else if (*(string+1) == '0')
            {
                string_append_character(string_res, *string);
            }                
            else
            {
                
                string_append_character(string_res, '0');
                string_append_character(string_res, '9');
                string_append_character(string_res, '2');
            }     
            */       
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

void codeGen_write(){
    printf("#----FUN-write----\n");
    printf("JUMP write$end\n");
    printf("LABEL write\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("DEFVAR TF@cnt_of_parameter\n");
    printf("DEFVAR TF@to_print\n");
    printf("DEFVAR TF@cnt\n");
    printf("POPS TF@cnt_of_parameter\n");
    printf("MOVE TF@cnt int@0\n");
    printf("LABEL _print_while_start\n");
    printf("LT GF@expr TF@cnt TF@cnt_of_parameter\n");
    printf("JUMPIFNEQ _print_while_end GF@expr bool@true\n");
    printf("POPS TF@to_print\n");
    printf("WRITE TF@to_print\n");
    printf("ADD TF@cnt TF@cnt int@1\n");
    printf("JUMP _print_while_start\n");
    printf("LABEL _print_while_end\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
    printf("LABEL write$end\n");
}

void codeGen_reads(){
    printf("#----FUN-reads----\n");
    printf("JUMP reads$end\n");
    printf("LABEL reads\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("POPS GF@trash\n");
    printf("DEFVAR TF@out\n");
    printf("READ TF@out string\n");
    printf("PUSHS TF@out\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
    printf("LABEL reads$end\n");
}

void codeGen_readi(){
    printf("#----FUN-readi----\n");
    printf("JUMP readi$end\n");
    printf("LABEL readi\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("POPS GF@trash\n");
    printf("DEFVAR TF@out\n");
    printf("READ TF@out int\n");
    printf("PUSHS TF@out\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
    printf("LABEL readi$end\n");
}

void codeGen_readn(){
    printf("#----FUN-readn----\n");
    printf("JUMP readn$end\n");
    printf("LABEL readn\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("POPS GF@trash\n");
    printf("DEFVAR TF@out\n");
    printf("READ TF@out float\n");
    printf("PUSHS TF@out\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
    printf("LABEL readn$end\n");
}

void codeGen_tointeger(){
    printf("#----FUN-tointeger----\n");
    printf("JUMP tointeger$end\n");
    printf("LABEL tointeger\n");
    printf("POPS GF@trash\n");
    printf("FLOAT2INTS\n");
    printf("RETURN\n");
    printf("LABEL tointeger$end\n");
}

void codeGen_substr(){
    printf("#----FUN-substr----\n");
    printf("JUMP substr$end\n");
    printf("LABEL substr\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("POPS GF@trash\n");
    printf("DEFVAR TF@ret_str\n");
    printf("MOVE TF@ret_str string@\n");
    printf("DEFVAR TF@s\n");
    printf("POPS TF@s\n");
    printf("DEFVAR TF@i\n");
    printf("POPS TF@i\n");
    printf("SUB TF@i TF@i int@1\n");
    printf("DEFVAR TF@n\n");
    printf("POPS TF@n\n");
    printf("DEFVAR TF@char\n");
    printf("MOVE TF@char string@\n");
    printf("DEFVAR TF@str_len\n");
    printf("DEFVAR TF@l_limit\n");
    printf("DEFVAR TF@r_limit\n");
    printf("STRLEN TF@str_len TF@s\n");
    printf("LT TF@l_limit TF@i int@0\n");
    printf("NOT TF@l_limit TF@l_limit\n");
    printf("GT TF@r_limit TF@i TF@str_len\n");
    printf("NOT TF@r_limit TF@r_limit\n");
    printf("AND TF@l_limit TF@l_limit TF@r_limit\n");
    printf("LT TF@r_limit TF@n int@0\n");
    printf("NOT TF@r_limit TF@r_limit\n");
    printf("AND TF@l_limit TF@l_limit TF@r_limit\n");
    printf("JUMPIFNEQ _sub_end TF@l_limit bool@true\n");
    printf("DEFVAR TF@cnt_of_loaded\n");
    printf("MOVE TF@cnt_of_loaded TF@i\n");
    printf("LABEL _sub_while\n");
    printf("LT TF@l_limit TF@i TF@str_len\n");
    printf("LT TF@r_limit TF@cnt_of_loaded TF@n\n");
    printf("AND TF@l_limit TF@l_limit TF@r_limit\n");
    printf("JUMPIFNEQ _sub_end TF@l_limit bool@true\n");
    printf("GETCHAR TF@char TF@s TF@i\n");
    printf("CONCAT TF@ret_str TF@ret_str TF@char\n");
    printf("ADD TF@cnt_of_loaded TF@cnt_of_loaded int@1\n");
    printf("ADD TF@i TF@i int@1\n");
    printf("JUMP _sub_while\n");
    printf("LABEL _sub_end\n");
    printf("PUSHS TF@ret_str\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
    printf("LABEL substr$end\n");
}

void codeGen_ord(){
    printf("#----FUN-ord----\n");
    printf("JUMP ord$end\n");
    printf("LABEL ord\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("POPS GF@trash\n");
    printf("DEFVAR TF@ascii\n");
    printf("DEFVAR TF@err\n");
    printf("MOVE TF@ascii string@\n");
    printf("MOVE TF@err int@1\n");
    printf("DEFVAR TF@l_limit\n");
    printf("DEFVAR TF@r_limit\n");
    printf("DEFVAR TF@string\n");
    printf("DEFVAR TF@i\n");
    printf("POPS TF@string\n");
    printf("POPS TF@i\n");
    printf("DEFVAR TF@str_len\n");
    printf("MOVE TF@str_len int@0\n");
    printf("STRLEN TF@str_len TF@string\n");
    printf("SUB TF@str_len TF@str_len int@1\n");
    printf("LT TF@l_limit TF@i int@0\n");
    printf("NOT TF@l_limit TF@l_limit\n");
    printf("GT TF@r_limit TF@i TF@str_len\n");
    printf("NOT TF@r_limit TF@r_limit\n");
    printf("AND TF@l_limit TF@l_limit TF@r_limit\n");
    printf("JUMPIFNEQ _ord_end TF@l_limit bool@true\n");
    printf("MOVE TF@err int@0\n");
    printf("STRI2INT TF@ascii TF@string TF@i\n");
    printf("LABEL _ord_end\n");
    printf("PUSHS TF@ascii\n");
    printf("PUSHS TF@err\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
    printf("LABEL ord$end\n");

}

void codeGen_chr(){
    printf("#----FUN-chr----\n");
    printf("JUMP chr$end\n");
    printf("LABEL chr\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("POPS GF@trash\n");
    printf("DEFVAR TF@ret_str\n");
    printf("MOVE TF@ret_str string@\n");
    printf("DEFVAR TF@err\n");
    printf("MOVE TF@err int@1\n");
    printf("DEFVAR TF@l_limit\n");
    printf("DEFVAR TF@r_limit\n");
    printf("DEFVAR TF@i\n");
    printf("POPS TF@i\n");
    printf("LT TF@l_limit TF@i int@0\n");
    printf("NOT TF@l_limit TF@l_limit\n");
    printf("GT TF@r_limit TF@i int@255\n");
    printf("NOT TF@r_limit TF@r_limit\n");
    printf("AND TF@l_limit TF@l_limit TF@r_limit\n");
    printf("JUMPIFNEQ _chr_end TF@l_limit bool@true\n");
    printf("MOVE TF@err int@0\n");
    printf("INT2CHAR TF@ret_str TF@i\n");
    printf("LABEL _chr_end\n");
    printf("PUSHS TF@ret_str\n");
    printf("PUSHS TF@err\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
    printf("LABEL chr$end\n");
}


/*
 * ----------------------GENERATOR START-----------------------
 */

static int ifCounter = 0;
static int whileCounter = 0;
static int stackTop = -1;
static int stackSize = TABLE_SIZE;
static int* stack;

void codeGen_init(){
    stack = malloc(sizeof(int) * stackSize);
    printf(".IFJcode21\n");
    printf("DEFVAR GF@expr\n");
    printf("DEFVAR GF@tmp1\n");
    printf("DEFVAR GF@tmp2\n");
    printf("DEFVAR GF@tmp3\n");
    printf("DEFVAR GF@tmp4\n");
    printf("DEFVAR GF@trash\n");
    printf("CREATEFRAME\n");
}

void codeGen_built_in_function(){
    codeGen_write();
    codeGen_reads();
    codeGen_readi();
    codeGen_readn();
    codeGen_tointeger();
    codeGen_substr();
    codeGen_ord();
    codeGen_chr();
}

/*
 * ----------------------VAR-----------------------
 */

void codeGen_push_var(char* name){
    printf("PUSHS TF@%s\n", name);
}

void codeGen_push_string(char* value){
    printf("PUSHS string@%s\n", convert_string(value));
}

void codeGen_push_int(int value){
    printf("PUSHS int@%d\n", value);
}

void codeGen_push_float(double value){
    printf("PUSHS float@%a\n", value);
}

void codeGen_push_nil(){
    printf("PUSHS nil@nil\n");
}

void codeGen_new_var(char* name){
    printf("DEFVAR TF@%s\n", name);
}

void codeGen_assign_var(char* name){
    printf("POPS TF@%s\n", name);
}

/*
 * ----------------------IF-----------------------
 */

void codeGen_if_start(){
    stackTop++;
    if(stackTop >= stackSize){
        stackSize += stackSize;
        stack = realloc(stack, sizeof(int) * stackSize);
    }
    stack[stackTop] = ifCounter;
    ifCounter++;
    printf("POPS GF@expr\n");
    printf("JUMPIFNEQ if$%d$else GF@expr bool@true\n", stack[stackTop]);

}

void codeGen_if_else(){
    printf("JUMP if$%d$end\n", stack[stackTop]);
    printf("LABEL if$%d$else\n", stack[stackTop]);
}

void codeGen_if_end(){
    printf("LABEL if$%d$end\n", stack[stackTop]);
    stackTop--;
}

/*
 * ----------------------WHILE-----------------------
 */

void codeGen_while_body_start(){
    stackTop++;
    if(stackTop >= stackSize){
        stackSize += stackSize;
        stack = realloc(stack, sizeof(int) * stackSize);
    }
    stack[stackTop] = whileCounter;
    whileCounter++;
    printf("LABEL while$%d$start\n", stack[stackTop]);
}

void codeGen_while_start(){
    printf("POPS GF@expr\n");
    printf("JUMPIFNEQ while$%d$end GF@expr bool@true\n", stack[stackTop]);
}

void codeGen_while_end(){
    printf("JUMP while$%d$start\n", stack[stackTop]);
    printf("LABEL while$%d$end\n", stack[stackTop]);
    stackTop--;
}


/*
 * ----------------------FUNC-----------------------
 */

void codeGen_function_start(char* name){
    printf("#----FUN-%s----\n", name);
    printf("JUMP %s$end\nLABEL %s\nPUSHFRAME\nCREATEFRAME\n", name, name);
    printf("POPS GF@trash\n");
}

void codeGen_function_return(){
    printf("POPFRAME\nRETURN\n");
}

void codeGen_function_end(char* name){
    printf("POPFRAME\nRETURN\nLABEL %s$end\n", name);
}

void codeGen_function_call(char* name, unsigned parameters){
    printf("PUSHS int@%i\n", parameters);
    printf("CALL %s\n", name);
}

/*
 * ----------------------STACK OPERATION-----------------------
 */

void generate_IntToFloat1(){
    printf("INT2FLOATS\n");
}

void generate_IntToFloat2(){
    printf("POPS GF@tmp3\n");
    printf("INT2FLOATS\n");
    printf("PUSHS GF@tmp3\n");
}

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
            printf("POPS GF@tmp1\n");
            printf("POPS GF@tmp2\n");
            printf("JUMPIFNEQ notZero GF@tmp1 float@0x0p+0\n");
            printf("EXIT int@9\n");
            printf("LABEL notZero\n");
            printf("DIV GF@tmp1 GF@tmp2 GF@tmp1\n");
            printf("PUSHS GF@tmp1\n");
            break;
        case NT_IDIV_NT:
            // rule E -> E // E
            printf("POPS GF@tmp1\n");
            printf("POPS GF@tmp2\n");
            printf("JUMPIFNEQ notZero GF@tmp1 int@0\n");
            printf("EXIT int@9\n");
            printf("LABEL notZero\n");
            printf("IDIV GF@tmp1 GF@tmp2 GF@tmp1\n");
            printf("PUSHS GF@tmp1\n");
            break;
        case NT_CONCAT_NT:
            // rule E -> E .. E
            printf("POPS GF@tmp1\n");
            printf("POPS GF@tmp2\n");
            printf("CONCAT GF@tmp1 GF@tmp2 GF@tmp1\n");
            printf("PUSHS GF@tmp1\n");
            break;
        case NT_EQ_NT:
            // rule E -> E == E
            printf("EQS\n");
            break;
        case NT_NEQ_NT:
            // rule E -> E ~= E
            printf("EQS\nNOTS\n");
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
            printf("PUSHS GF@tmp4\n");
            break;
        default:break;
    }
}