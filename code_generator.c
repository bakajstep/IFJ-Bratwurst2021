/**
 * Project: IFJ21 imperative language compiler
 * 
 * Brief:   Code Generator for IFJ21 compiler
 * 
 * Author:  Adam Kankovsky   <xkanko00>
 * Author:  Stepan Bakaj     <xbakaj00>
 * Author:  Radek Serejch    <xserej00> 
 * 
 */

#include <ctype.h>
#include <stdlib.h>
#include <limits.h>


#include "code_generator.h"

#define DEF 2

/*
 * ----------------------USEFUL FUNCTIONS-----------------------
 */

int numPlaces (int n) {    
    int r = 1;
    if (n < 0) n = (n == INT_MIN) ? INT_MAX: -n;
    while (n > 9) {
        n /= 10;
        r++;
    }
    return r;
}

char* convert_string(char* str_toconvert){
    if (str_toconvert == NULL)
    {
        return NULL;
    }
    
    char* string = str_toconvert;

    if (string[0] == '\0')
    {
        return "";
    }


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

    string_append_character(string_res, '\0');

    return string_res->string;
}

shadowStack_t* shStackPush(shadowStack_t* shade, char* name, int scale, int function){
    shadowStack_t* newNode = malloc(sizeof(struct shadowStack));
    if(newNode == NULL){
        err = E_INTERNAL;
        return NULL;
    }
    newNode->name = malloc(strlen(name)+1);
    if(newNode->name == NULL){
        err = E_INTERNAL;
        return NULL;
    }
    strcpy(newNode->name, name);
    newNode->scale = scale;
    newNode->inicialized = 0;
    newNode->nameScale = malloc(strlen(name) + numPlaces(scale) + 1);
    if(newNode->nameScale == NULL){
        err = E_INTERNAL;
        return NULL;
    }
    char funCnt[function+1];
    for(int i = 0; i < function; i++){
        funCnt[i] = '$';
    }
    funCnt[function] = '\0';
    sprintf(newNode->nameScale, "%s%s$%d", funCnt,  name,  scale);
    newNode->next = shade;
    return shade = newNode;
}

shadowStack_t * shStackNameScaleByName(shadowStack_t* shade, char* name){
    shadowStack_t* current = shade;
    while(current != NULL){
        if(strcmp(current->name, name) == 0){
            return current;
        }else{
            current = current->next;
        }
    }
    return NULL;
}

shadowStack_t * shStackNameScaleByNameInitialized(shadowStack_t* shade, char* name){
    shadowStack_t* current = shade;
    while(current != NULL){
        if((strcmp(current->name, name) == 0) && current->inicialized == 1){
            return current;
        }else{
            current = current->next;
        }
    }
    return NULL;
}

shadowStack_t* shStackDelByScale(shadowStack_t* shade, int scale){
    shadowStack_t* del;
    while(shade != NULL){
        if(shade->scale == scale){
            del = shade;
            shade = shade->next;
            free(del->name);
            del->name = NULL;
            free(del->nameScale);
            del->nameScale = NULL;
            free(del);
            del = NULL;
        }else{
            return shade;
        }
    }
    return NULL;
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
    printf("JUMPIFNEQ exprint TF@to_print nil@nil \n");
    printf("PUSHS string@nil\n");
    printf("POPS TF@to_print\n");
    printf("LABEL exprint\n");
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
static int intToFloat1 = -1;
static int intToFloat2 = -1;
static int scale = -1;
static int function = 0;
static int isWhile = 0;
static int isNil = 0;
static int toBool = -1;
DLList* list = NULL;
shadowStack_t* shStack = NULL;

void codeGen_init(){
    stack = malloc(sizeof(int) * stackSize);
    if(stack == NULL){
        err = E_INTERNAL;
        return;
    }
    list = malloc(sizeof(DLList));
    if(list == NULL){
        err = E_INTERNAL;
        return;
    }
    DLL_Init(list);
    shStack = NULL;
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
    shadowStack_t* current = shStackNameScaleByNameInitialized(shStack, name);
    if(current == NULL){
        err = E_INTERNAL;
        return;
    }

    if(isWhile == 0){
        printf("PUSHS TF@%s\n", current->nameScale);
    }else{
        char* str = (char*)malloc(12 + strlen(current->nameScale) + 1);
        sprintf(str, "PUSHS TF@%s\n", current->nameScale);
        DLL_InsertLast(list, str);
        free(str);
        str = NULL;
    }
}

void codeGen_push_string(char* value){
    if(isWhile == 0){
        printf("PUSHS string@%s\n", convert_string(value));
    }else{
        char* str = (char*)malloc(15 + strlen(convert_string(value)) + 1);
        sprintf(str, "PUSHS string@%s\n", convert_string(value));
        DLL_InsertLast(list, str);
        free(str);
        str = NULL;
    }

}

void codeGen_push_int(int value){
    if(isWhile == 0){
        printf("PUSHS int@%d\n", value);
    }else{
        char* str = (char*)malloc(INST_LEN + numPlaces(value) + 1);
        sprintf(str, "PUSHS int@%d\n", value);
        DLL_InsertLast(list, str);
        free(str);
        str = NULL;
    }

}

void codeGen_push_float(double value){
    if(isWhile == 0){
        printf("PUSHS float@%a\n", value);
    }else{
        char* str = (char*)malloc(INST_LEN + 30 + 1);
        sprintf(str, "PUSHS float@%a\n", value);
        DLL_InsertLast(list, str);
        free(str);
        str = NULL;
    }

}

void codeGen_push_nil(){
    isNil = 1;
    if(isWhile == 0){
        printf("PUSHS nil@nil\n");
    }else{
        char* str = (char*)malloc(INST_LEN + 1);
        sprintf(str, "PUSHS nil@nil\n");
        DLL_InsertLast(list, str);
        free(str);
        str = NULL;
    }

}

void codeGen_new_var(char* name){
    shStack = shStackPush(shStack, name, scale, function);
    if(shStack == NULL){
        err = E_INTERNAL;
        return;
    }
    
    //printf("\nname scale AA\n");
    printf("DEFVAR TF@%s\n", shStack->nameScale);
}

void codeGen_assign_var(char* name, unsigned nil){
    shadowStack_t* current = shStackNameScaleByName(shStack, name);
    if (nil == DEF)
    {
        current->inicialized = 1;        
    }
    else
    {
        if(current == NULL){
            err = E_INTERNAL;
            return;
        }
        if(nil == 0){
            current->inicialized = 1;
        }
        if(isWhile == 0){
            printf("POPS TF@%s\n", current->nameScale);
        }else{
            char* str = (char*)malloc(INST_LEN + strlen(current->nameScale) + 1);
            sprintf(str, "POPS TF@%s\n", current->nameScale);
            DLL_InsertLast(list, str);
            free(str);
            str = NULL;
        }
    }        
}

/*
 * ----------------------IF-----------------------
 */

void codeGen_if_start(){
    stackTop++;
    scale++;
    if(stackTop >= stackSize){
        stackSize += stackSize;
        stack = realloc(stack, sizeof(int) * stackSize);
    }
    stack[stackTop] = ifCounter;
    ifCounter++;
    if(isWhile == 0){
        printf("POPS GF@expr\n");
        printf("JUMPIFNEQ if$%d$else GF@expr bool@true\n", stack[stackTop]);
    }else{
        char* str = (char*)malloc(INST_LEN + 1);
        sprintf(str, "POPS GF@expr\n");
        DLL_InsertLast(list, str);
        free(str);
        str = NULL;
        char* str2 = (char*)malloc(INST_LEN + numPlaces(stack[stackTop]) + 1);
        sprintf(str2, "JUMPIFNEQ if$%d$else GF@expr bool@true\n", stack[stackTop]);
        DLL_InsertLast(list, str2);
        free(str2);
        str2 = NULL;
    }
}

void codeGen_if_else(){
    if(isWhile == 0) {
        printf("JUMP if$%d$end\n", stack[stackTop]);
        printf("LABEL if$%d$else\n", stack[stackTop]);
    }else{
        char* str = (char*)malloc(INST_LEN + numPlaces(stack[stackTop]) + 1);
        sprintf(str, "JUMP if$%d$end\n", stack[stackTop]);
        DLL_InsertLast(list, str);
        free(str);
        str = NULL;
        char* str2 = (char*)malloc(INST_LEN + numPlaces(stack[stackTop]) + 1);
        sprintf(str2, "LABEL if$%d$else\n", stack[stackTop]);
        DLL_InsertLast(list, str2);
        free(str2);
        str2 = NULL;
    }
}

void codeGen_if_end(){
    if(isWhile == 0){
        printf("LABEL if$%d$end\n", stack[stackTop]);
    }else{
        char* str = (char*)malloc(INST_LEN + numPlaces(stack[stackTop]) + 1);
        sprintf(str, "LABEL if$%d$end\n", stack[stackTop]);
        DLL_InsertLast(list, str);
        free(str);
        str = NULL;
    }
    shStack = shStackDelByScale(shStack, scale);
    stackTop--;
    scale--;
}

/*
 * ----------------------WHILE-----------------------
 */

void codeGen_while_body_start(){
    stackTop++;
    scale++;
    isWhile = 1;
    if(stackTop >= stackSize){
        stackSize += stackSize;
        stack = realloc(stack, sizeof(int) * stackSize);
    }
    stack[stackTop] = whileCounter;
    whileCounter++;
    char* str = (char*)malloc(INST_LEN + numPlaces(stack[stackTop]) + 1);
    sprintf(str, "LABEL while$%d$start\n", stack[stackTop]);    
    DLL_InsertLast(list, str);
    free(str);
    str = NULL;
}

void codeGen_while_start(){
    if(isWhile == 0) {
        printf("POPS GF@expr\n");
        printf("JUMPIFNEQ while$%d$end GF@expr bool@true\n", stack[stackTop]);
    }else{
        DLL_InsertLast(list, "POPS GF@expr\n");
        char* str2 = (char*)malloc(INST_LEN + numPlaces(stack[stackTop]) + 1);
        sprintf(str2, "JUMPIFNEQ while$%d$end GF@expr bool@true\n", stack[stackTop]);
        DLL_InsertLast(list, str2);
        free(str2);
        str2 = NULL;
    }
}

void codeGen_while_end(){
    DLL_PrintAll(list);
    DLL_Dispose(list);
    printf("JUMP while$%d$start\n", stack[stackTop]);
    printf("LABEL while$%d$end\n", stack[stackTop]);
    isWhile = 0;
    stackTop--;
    scale--;
}


/*
 * ----------------------FUNC-----------------------
 */

void codeGen_function_start(char* name){
    scale++;
    function++;
    printf("#----FUN-%s----\n", name);
    printf("JUMP %s$end\nLABEL %s\nPUSHFRAME\nCREATEFRAME\n", name, name);
    printf("POPS GF@trash\n");
}

void codeGen_function_return(){
    if(isWhile == 0){
        printf("POPFRAME\nRETURN\n");
    }else{
        DLL_InsertLast(list, "POPFRAME\nRETURN\n");
    }
}

void codeGen_function_end(char* name){
    printf("POPFRAME\nRETURN\nLABEL %s$end\n", name);

    shStack = shStackDelByScale(shStack, scale);
    scale--;
}

void codeGen_function_call(char* name, unsigned parameters){
    if(isWhile == 0){
        printf("PUSHS int@%i\n", parameters);
        printf("CALL %s\n", name);
    }else{
        char* str = (char*)malloc(INST_LEN + numPlaces(parameters) + 1);
        sprintf(str, "PUSHS int@%i\n", parameters);
        DLL_InsertLast(list, str);
        free(str);
        str = NULL;
        char* str2 = (char*)malloc(INST_LEN + strlen(name) + 1);
        sprintf(str2, "CALL %s\n", name);
        DLL_InsertLast(list, str2);
        free(str2);
        str2 = NULL;
    }
}

/*
 * ----------------------STACK OPERATION-----------------------
 */

void generate_IntToFloat1(){
    if(isWhile == 0){
        printf("POPS GF@tmp1\n");
        printf("JUMPIFEQ nope%d GF@tmp1 nil@nil\n",++intToFloat1);
        printf("PUSHS GF@tmp1\n");
        printf("INT2FLOATS\n");
        printf("LABEL nope%d\n",intToFloat1);
    }else{
        DLL_InsertLast(list, "POPS GF@tmp1\n");
        char* str = (char*)malloc(INST_LEN + numPlaces(++intToFloat1) + 1);
        sprintf(str, "JUMPIFEQ nope%d GF@tmp1 nil@nil\n", intToFloat1);
        DLL_InsertLast(list, str);
        free(str);
        str = NULL;
        DLL_InsertLast(list, "PUSHS GF@tmp1\n");
        DLL_InsertLast(list, "INT2FLOATS\n");
        char* str2 = (char*)malloc(INST_LEN + numPlaces(intToFloat1) + 1);
        sprintf(str2, "LABEL nope%d\n", intToFloat1);
        DLL_InsertLast(list, str2);
        free(str2);
        str2 = NULL;
    }
}

void generate_IntToFloat2(){
    if(isWhile == 0){
        printf("POPS GF@tmp3\n");
        printf("POPS GF@tmp2\n");
        printf("JUMPIFEQ no%d GF@tmp2 nil@nil\n",++intToFloat2);
        printf("INT2FLOAT GF@tmp2 GF@tmp2\n");
        printf("LABEL no%d\n",intToFloat2);
        printf("PUSHS GF@tmp2\n");
        printf("PUSHS GF@tmp3\n");
    }else{
        DLL_InsertLast(list, "POPS GF@tmp3\n");
        DLL_InsertLast(list, "POPS GF@tmp2\n");
        char* str = (char*)malloc(INST_LEN + numPlaces(++intToFloat2) + 1);
        sprintf(str, "JUMPIFEQ no%d GF@tmp2 nil@nil\n", intToFloat2);
        DLL_InsertLast(list, str);
        free(str);
        str = NULL;
        DLL_InsertLast(list, "INT2FLOAT GF@tmp2 GF@tmp2\n");
        char* str2 = (char*)malloc(INST_LEN + numPlaces(intToFloat2) + 1);
        sprintf(str2, "LABEL no%d\n", intToFloat2);
        DLL_InsertLast(list, str2);
        free(str2);
        str2 = NULL;
        DLL_InsertLast(list, "PUSHS GF@tmp2\n");
        DLL_InsertLast(list, "PUSHS GF@tmp3\n");
    }
}

void generate_checkifNIL2ops(){
    if(isWhile == 0){
        printf("POPS GF@tmp1\n");
        printf("POPS GF@tmp2\n");
        printf("JUMPIFEQ ERR8 GF@tmp1 nil@nil\n");
        printf("JUMPIFEQ ERR8 GF@tmp2 nil@nil\n");
        printf("PUSHS GF@tmp2\n");
        printf("PUSHS GF@tmp1\n");
    }else{
        DLL_InsertLast(list, "POPS GF@tmp1\n");
        DLL_InsertLast(list, "POPS GF@tmp2\n");
        DLL_InsertLast(list, "JUMPIFEQ ERR8 GF@tmp1 nil@nil\n");
        DLL_InsertLast(list, "JUMPIFEQ ERR8 GF@tmp2 nil@nil\n");
        DLL_InsertLast(list, "PUSHS GF@tmp2\n");
        DLL_InsertLast(list, "PUSHS GF@tmp1\n");
    }
}
void generate_checkifNIL1op(){
    if(isWhile == 0){
        printf("POPS GF@tmp1\n");
        printf("JUMPIFEQ ERR8 GF@tmp1 nil@nil\n");
        printf("PUSHS GF@tmp1\n");
    }else{
        DLL_InsertLast(list, "POPS GF@tmp1\n");
        DLL_InsertLast(list, "JUMPIFEQ ERR8 GF@tmp1 nil@nil\n");
        DLL_InsertLast(list, "PUSHS GF@tmp1\n");
    }
}

void generate_errorOp(){
    printf("JUMP errorOp_End\n");
    printf("LABEL ERR9\n");
    printf("EXIT int@9\n");
    printf("JUMP errorOp_End\n");
    printf("LABEL ERR8\n");
    printf("EXIT int@8\n");
    printf("LABEL errorOp_End\n");
    free(list);
    list = NULL;
    free(stack);
    stack = NULL;
}

void generate_operation(psa_rules_enum operation){
    switch (operation){
        case NT_PLUS_NT:
            //rule E -> E + E
            generate_checkifNIL2ops();
            if(isWhile == 0){
                printf("ADDS\n");
            }else{
                DLL_InsertLast(list, "ADDS\n");
            }
            break;
        case NT_MINUS_NT:
            //rule E -> E - E
            generate_checkifNIL2ops();
            if(isWhile == 0){
                printf("SUBS\n");
            }else{
                DLL_InsertLast(list, "SUBS\n");
            }
            break;
        case NT_MUL_NT:
            // rule E -> E * E
            generate_checkifNIL2ops();
            if(isWhile == 0){
                printf("MULS\n");
            }else{
                DLL_InsertLast(list, "MULS\n");
            }
            break;
        case NT_DIV_NT:
            // rule E -> E / E
            generate_checkifNIL2ops();
            if(isWhile == 0){
                printf("POPS GF@tmp1\n");
                printf("POPS GF@tmp2\n");
                printf("JUMPIFEQ ERR9 GF@tmp1 float@0x0p+0\n");
                printf("DIV GF@tmp1 GF@tmp2 GF@tmp1\n");
                printf("PUSHS GF@tmp1\n");
            }else{
                DLL_InsertLast(list, "POPS GF@tmp1\n");
                DLL_InsertLast(list, "POPS GF@tmp2\n");
                DLL_InsertLast(list, "JUMPIFEQ ERR9 GF@tmp1 float@0x0p+0\n");
                DLL_InsertLast(list, "DIV GF@tmp1 GF@tmp2 GF@tmp1\n");
                DLL_InsertLast(list, "PUSHS GF@tmp1\n");
            }

            break;
        case NT_IDIV_NT:
            // rule E -> E // E
            generate_checkifNIL2ops();
            if(isWhile == 0){
                printf("POPS GF@tmp1\n");
                printf("POPS GF@tmp2\n");
                printf("JUMPIFNEQ ERR9 GF@tmp1 int@0\n");
                printf("IDIV GF@tmp1 GF@tmp2 GF@tmp1\n");
                printf("PUSHS GF@tmp1\n");
            }else{
                DLL_InsertLast(list, "POPS GF@tmp1\n");
                DLL_InsertLast(list, "POPS GF@tmp2\n");
                DLL_InsertLast(list, "JUMPIFNEQ ERR9 GF@tmp1 int@0\n");
                DLL_InsertLast(list, "IDIV GF@tmp1 GF@tmp2 GF@tmp1\n");
                DLL_InsertLast(list, "PUSHS GF@tmp1\n");
            }
            break;
        case NT_CONCAT_NT:
            // rule E -> E .. E
            generate_checkifNIL2ops();
            if(isWhile == 0){
                printf("POPS GF@tmp1\n");
                printf("POPS GF@tmp2\n");
                printf("CONCAT GF@tmp1 GF@tmp2 GF@tmp1\n");
                printf("PUSHS GF@tmp1\n");
            }else{
                DLL_InsertLast(list, "POPS GF@tmp1\n");
                DLL_InsertLast(list, "POPS GF@tmp2\n");
                DLL_InsertLast(list, "CONCAT GF@tmp1 GF@tmp2 GF@tmp1\n");
                DLL_InsertLast(list, "PUSHS GF@tmp1\n");
            }
            break;
        case NT_EQ_NT:
            // rule E -> E == E
            if(isWhile == 0){
                printf("EQS\n");
            }else{
                DLL_InsertLast(list, "EQS\n");
            }
            break;
        case NT_NEQ_NT:
            // rule E -> E ~= E
            if(isWhile == 0){
                printf("EQS\nNOTS\n");
            }else{
                DLL_InsertLast(list, "EQS\nNOTS\n");
            }
            break;
        case NT_LEQ_NT:
            // rule E -> E <= E
            generate_checkifNIL2ops();
            if(isWhile == 0){
                printf("GTS\nNOTS\n");
            }else{
                DLL_InsertLast(list, "GTS\nNOTS\n");
            }
            break;
        case NT_GEQ_NT:
            // rule E -> E >= E
            generate_checkifNIL2ops();
            if(isWhile == 0){
                printf("LTS\nNOTS\n");
            }else{
                DLL_InsertLast(list, "LTS\nNOTS\n");
            }
            break;
        case NT_LTN_NT:
            // rule E -> E < E
            generate_checkifNIL2ops();
            if(isWhile == 0){
                printf("LTS\n");
            }else{
                DLL_InsertLast(list, "LTS\n");
            }
            break;
        case NT_GTN_NT:
            // rule E -> E > E
            generate_checkifNIL2ops();
            if(isWhile == 0){
                printf("GTS\n");
            }else{
                DLL_InsertLast(list, "GTS\n");
            }
            break;
        case NT_HASHTAG:
            // rule E -> #E
            generate_checkifNIL1op();
            if(isWhile == 0){
                printf("POPS GF@tmp1\n");
                printf("STRLEN GF@tmp4 GF@tmp1\n");
                printf("PUSHS GF@tmp4\n");
            }else{
                DLL_InsertLast(list, "POPS GF@tmp1\n");
                DLL_InsertLast(list, "STRLEN GF@tmp4 GF@tmp1\n");
                DLL_InsertLast(list, "PUSHS GF@tmp4\n");
            }
            break;
        default:break;
    }
}

void generate_toBool() {
    if(isWhile == 0){
        printf("POPS GF@tmp1\n");
        printf("JUMPIFEQ toBoolTru%d GF@tmp1 nil@nil\n",++toBool);
        printf("PUSHS bool@true\n");
        printf("JUMP toBoolFalse%d\n",toBool);
        printf("LABEL toBoolTru%d\n",toBool);
        printf("PUSHS bool@false\n");
        printf("LABEL toBoolFalse%d\n",toBool);
    }else{
        DLL_InsertLast(list, "POPS GF@tmp1\n");
        char* str = (char*)malloc(INST_LEN + numPlaces(++toBool) + 1);
        sprintf(str, "JUMPIFEQ toBoolTru%d GF@tmp1 nil@nil\n", toBool);
        DLL_InsertLast(list, str);
        free(str);
        str = NULL;
        DLL_InsertLast(list, "PUSHS bool@true\n");
        char* str2 = (char*)malloc(INST_LEN + numPlaces(toBool) + 1);
        sprintf(str2, "JUMP toBoolFalse%d\n", toBool);
        DLL_InsertLast(list, str2);
        free(str2);
        str2 = NULL;        
        char* str3 = (char*)malloc(INST_LEN + numPlaces(toBool) + 1);
        sprintf(str3, "LABEL toBoolTru%d\n", toBool);        
        DLL_InsertLast(list, str3);
        free(str3);
        str3 = NULL;
        DLL_InsertLast(list, "PUSHS bool@false\n");
        char* str4 = (char*)malloc(INST_LEN + numPlaces(toBool) + 1);
        sprintf(str4, "LABEL toBoolFalse%d\n", toBool);
        DLL_InsertLast(list, str4);
        free(str4);
        str4 = NULL;
    }
}