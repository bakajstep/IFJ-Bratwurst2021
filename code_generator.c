//
// Created by adam on 29.11.21.
//

#include "code_generator.h"



void codeFromToken(token_type_t type, token_t token, symTree_t tree){
    static int tableLine = TABLE_SIZE;
    static tableItem_t table = NULL;
    static int lastItem = -1;
    static bool move = false;
    static bool write = false;
    static bool defTerm = false;
    static bool defParams = false;
    static bool defFunc = false;
    static char *defId = false;
    static DLList list = NULL;
    static char* id;
    static int ifCounter = 0;

    if(table == NULL){
        table = malloc(stackSize * sizeof(tableItem_t));
    }

    if(lastItem + 1 >= tableLine){
        tableLine += tableLine;
        table = realloc(table, tableLine * sizeof(tableItem_t));
    }

    if(list == NULL){
        list = malloc(sizeof(DLList));
        DLL_Init(list);
    }

    switch(type){
        case T_IDENTIFIER:
            if(strcmp(token->attribute->string, "print") == 0){
                write = true;
            }else if(defTerm){
                defID = token->attribute->string;
                printf("JUMP %s$end\nLABEL %s$body\n", defId, defId)
            }else{
                id = token->attribute->string;
            }
            break;
        case T_KEYWORD:
            switch(token->attribute->keyword){
                case K_FUNCTION:
                    defTerm = true;
                    defFunc = true;
                    defParams = true;
                    break;
                case K_THEN:
                    tableLine++;
                    //kontrola velikosti tabulky

                    table[tableLine].id = ifCounter;
                    table[tableLine];isIf = true;
                    ifcounter++;
                    //reseni podminky

                    printf("JUMIFNEQ $if$%i$else TF@$return bool@true\nMOVE TF@$return nil@nil", table[tableLine].id);
                    break;
                case K_ELSE:
                    printf("JUMP $if$%i$end\n", table[tableLine].id);
                    printf("LABEL $if$%i$else\nMOVE TF@$return nil@nil\n", table[tableLine].id))
                    break;
                case K_END:
                    break;
                case K_WHILE:
                    break;
                case K_DO:
                    break;
                default:break;
            }
            break;
        default:break;
    }
}