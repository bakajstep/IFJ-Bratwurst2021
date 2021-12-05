//
// Created by adam on 29.11.21.
//

#include "code_generator.h"

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

void codeFromToken(token_type_t type, token_t token){
    static int tableLines = TABLE_SIZE;
    static tableItem_t table = NULL;
    static int lastItem = -1;
    //static bool move = false;
    static bool write = false;
    static bool defTerm = false;
    static bool defParams = false;
    static bool defFunc = false;
    static bool assign = false;
    static bool callFunc = false;
    static char* assignId;
    static char* defId;
    static char* callId;
    //static DLList list;
    static char* id;
    static int ifCounter = 0;
    static int whileCounter = 0;
    static int params = 1;
    //static char* varType;
    //static char* tokenVal;

    //TODO smazat
    params = params;
    assign = assign;
    assignId = assignId;
    defFunc = defFunc;

    if(table == NULL){
        table = malloc(tableLines * sizeof(tableItem_t));
    }

    if(lastItem + 1 >= tableLines){
        tableLines += tableLines;
        table = realloc(table, tableLines * sizeof(tableItem_t));
    }

    /*if(list == NULL){
        list = malloc(sizeof(DLList));
        DLL_Init(list);
    }*/

    /*if(token == NULL){
        if(table != NULL){
            free(table);
            table = NULL;

            printf("EXIT int@0\nLABEL $main\nCREATEFRAME\nPUSHFRAME\n");
            printf("JUMP $main$main\n");
        }
    }*/

    switch(type){
        case T_ASSIGN:
            assign = true;
            assignId = id;
            break;

        case T_IDENTIFIER:
            if(strcmp(token.attribute.string, "write") == 0){
                write = true;
            }else if(defTerm){
                defId = token.attribute.string;
                printf("JUMP %s$end\nLABEL %s$body\n", defId, defId);
                defTerm = false;
            }else{
                id = token.attribute.string;
            }
            break;
        case T_RIGHT_BRACKET:
            params = 1;
            if(callFunc){
                printf("CALL %s\n", callId);
                callFunc = false;
            }

            if(write){
                printf("DEFVAR TF@$return\nMOVE TF@$return nil@nil\n");
                write = false;
            }

            if(defParams){
                printf("DEFVAR LF@$return\nCREATEFRAME\nDEFVAR TF@$return\nMOVE TF@$return nil@nil\n");
                defParams = false;
            }

            if(assign){
                printf("MOVE LF@%s TF@$return\n", assignId);
                assign = false;
            }
            break;
        case T_LEFT_BRACKET:
            if(!defFunc) {
                printf("CREATEFRAME\n");
                if (!write) {
                    callId = id;
                    callFunc = true;
                }
            }

            break;
        //pridat moznost ID
        case T_INT:
        case T_DECIMAL:
        case T_STRING:
            {}
            char* str = malloc(sizeof(char) * 50);
            switch(type){
                case T_INT:
                    sprintf(str, "int$%i", token.attribute.integer);
                    break;
                case T_DECIMAL:
                    sprintf(str, "float@%a", token.attribute.decimal);
                    break;
                case T_STRING:
                    sprintf(str, "string@%s", convert_string(token.attribute.string));
                    break;
                default:break;
            }
            if(str == NULL) break;
            else if(write){
                printf("WRITE %s\n", str);
            }else if(defParams){
                printf("MOVE %s LF@%%%i\n", str, params);
            }else{
                printf("DEFVAR TF@%%%i\n", params);
                printf("MOVE TF@%%%i %s\n", params, str);
                params++;
            }
            free(str);
            str = NULL;
            break;
        case T_KEYWORD:
            switch(token.attribute.keyword){
                //nfunc
                case K_FUNCTION:
                    defTerm = true;
                    defFunc = true;
                    defParams = true;
                    break;
                case K_THEN:
                    lastItem++;
                    if(lastItem >= tableLines){
                        tableLines += tableLines;
                        table = realloc(table, tableLines * sizeof(tableItem_t));
                    }
                    table[lastItem].id = ifCounter;
                    table[lastItem].isIf = true;
                    ifCounter++;
                    //kontrola jestli podminka hodila bool

                    printf("JUMPIFNEQ $if$%i$else TF@$return bool@true\nMOVE TF@$return nil@nil", table[tableLines].id);
                    break;
                case K_ELSE:
                    printf("JUMP $if$%i$end\n", table[lastItem].id);
                    printf("LABEL $if$%i$else\nMOVE TF@$return nil@nil\n", table[lastItem].id);
                    break;
                case K_END:
                    if(lastItem >= 0){
                        if(table[lastItem].isIf){
                            printf("LABEL $if$%i$end\n", table[lastItem].id);
                        }else{
                            printf("JUMP $while$%i$start\n", table[lastItem].id);
                            printf("LABEL $while$%i$end\n", table[lastItem].id);

                            printf("CREATEFRAME\nDEFVAR TF@$return\nMOVE TF@$return nil@nil\n");
                        }
                        lastItem--;
                    }else if(defFunc){//je to end funkce
                        printf("MOVE LF@$return TF@$return\nPOPFRAME\nRETURN\nLABEL %s\nPUSHFRAME\n", defId);
                        //TODO uloz funkci z ktere byla volana
                        //printf("JUMP %s$body\nLABEL %s$end\n", defId, defId);
                        defFunc = false;
                    }
                    break;
                case K_WHILE:
                    lastItem++;
                    if(lastItem >= tableLines){
                        tableLines += tableLines;
                        table = realloc(table, tableLines * sizeof(tableItem_t));
                    }
                    table[lastItem].id = whileCounter;
                    table[lastItem].isIf = false;
                    whileCounter++;
                    printf("LABEL $while$%i$start\n", table[lastItem].id);
                    break;
                case K_DO:
                    printf("JUMPIFNEQ $while$%i$end TF@$return bool@true\n", table[lastItem].id);
                    break;
                default:break;
            }
            break;
        default:break;
    }
    //konec radku
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

    //SUB
    //DIV
    //MUL
    //honecna funkce na freecka
