//
// Created by adam on 29.11.21.
//

#include "code_generator.h"

void codeFromToken(token_type_t type, token_t token, symTree_t tree){
    static int tableLines = TABLE_SIZE;
    static tableItem_t table = NULL;
    static int lastItem = -1;
    static bool move = false;
    static bool write = false;
    static bool defTerm = false;
    static bool defParams = false;
    static bool defFunc = false;
    static bool assign = false;
    static bool callFunc = false;
    static char* assignId;
    static char* defId;
    static char* callId;
    static DLList list = NULL;
    static char* id;
    static int ifCounter = 0;
    static int whileCounter = 0;
    static int params = 1;
    static char* varType;
    static char* tokenVal;

    if(table == NULL){
        table = malloc(stackSize * sizeof(tableItem_t));
    }

    if(lastItem + 1 >= tableLiness){
        tableLiness += tableLiness;
        table = realloc(table, tableLiness * sizeof(tableItem_t));
    }

    if(list == NULL){
        list = malloc(sizeof(DLList));
        DLL_Init(list);
    }

    switch(type){
        case T_ASSIGN:
            assign = true; //pro výpis move
            assignId = id;
            break;
        case T_IDENTIFIER:
            else if(strcmp(token->attribute->string, "print") == 0){
                write = true;
            }else if(defTerm){
                defID = token->attribute->string;
                printf("JUMP %s$end\nLABEL %s$body\n", defId, defId)
            }else{
                id = token->attribute->string;
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
                callPrint = false;
            }

            if(defParams){
                printf("DEFVAR LF@$return\nCREATEFRAME\nDEFVAR TF@$return\nMOVE TF@$return nil@nil\n");
                defParams = false;
            }
            //nejsem si jistej
            /*if(assign){
                printf("MOVE LF@%s TF@$return\n", assignId);
                assign = false;
            }*/
            break;
        case T_LEFT_BRACKET:
            printf("CREATEFRAME\n");
            if(!write){
                callId = id;
                callFunc = true;
            }
            break;
        case T_INT:
        case T_DECIMAL:
        case T_STRING:

            break;
        case T_KEYWORD:
            switch(token->attribute->keyword){
                case K_FUNCTION:
                    defTerm = true;
                    defFunc = true;
                    defParams = true;
                    break;
                case K_INTEGER:
                    varType = "integer";
                    break;
                case K_NUMBER:
                    varType = "number";
                    break;
                case K_STRING:
                    varType = "string";
                    break;
                case K_NILL:
                    varType = "nill";
                    break;
                case K_THEN:
                    lastItem++;
                    
                    if(lastItem >= tableLines){
                        tableLines += tableLines;
                        table = realloc(table, tableLines * sizeof(tableItem_t));
                    }
                    table[lastItem].id = ifCounter;
                    table[lastItem];isIf = true;
                    ifcounter++;
                    //kontrola jestli podminka hodila bool

                    printf("JUMIFNEQ $if$%i$else TF@$return bool@true\nMOVE TF@$return nil@nil", table[tableLines].id);
                    break;
                case K_ELSE:
                    printf("JUMP $if$%i$end\n", table[lastItem].id);
                    printf("LABEL $if$%i$else\nMOVE TF@$return nil@nil\n", table[lastItem].id))
                    break;
                case K_END:
                    if(lastItem >= 0){
                        if(table[tableLines].isIf){
                            printf("LABEL $if$%i$end\n", table[lastItem].id)
                        }else{
                            printf("JUMP $while$%i$start\n", table[lastItem].id);
                            printf("LABEL $while$%i$end\n", table[lastItem].id);

                            printf("LABEL $if$%i$\nDEFVAR TF@$return\nMOVE TF@$return nil@nil\n");
                        }
                    //end funkce
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
    void operations(char* operationName){
        //operace ADDS...
    }

    //SUB
    //DIV
    //MUL
    //honecna funkce na freecka
}