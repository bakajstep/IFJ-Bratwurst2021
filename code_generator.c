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
    static char *defId = false;
    static DLList list = NULL;
    static char* id;
    static int ifCounter = 0;
    static int whileCounter = 0;

    if(table == NULL){
        table = malloc(stackSize * sizeof(tableItem_t));
    }

    if(lastItem + 1 >= tableLines){
        tableLines += tableLines;
        table = realloc(table, tableLines * sizeof(tableItem_t));
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
                /*TODO vyresit definici funkce*/
                case K_FUNCTION:
                    defTerm = true;
                    defFunc = true;
                    defParams = true;
                    break;
                case
                case K_THEN:
                    lastItem++;
                    //kontrola velikosti tabulky

                    table[lastItem].id = ifCounter;
                    table[lastItem];isIf = true;
                    ifcounter++;
                    //kontrola jestli podminka hodila bool

                    printf("JUMIFNEQ $if$%i$else TF@$return bool@true\nMOVE TF@$return nil@nil", table[tableLine].id);
                    break;
                case K_ELSE:
                    printf("JUMP $if$%i$end\n", table[lastItem].id);
                    printf("LABEL $if$%i$else\nMOVE TF@$return nil@nil\n", table[lastItem].id))
                    break;
                case K_END:
                    if(lastItem >= 0){
                        if(table[tableLine].isIf){
                            print("LABEL $if$%i$end\n", table[lastItem].id)
                        }else{
                            print("JUMP $while$%i$start\n", table[lastItem].id);
                            print("LABEL $while$%i$end\n", table[lastItem].id);

                            print("LABEL $if$%i$\nDEFVAR TF@$return\nMOVE TF@$return nil@nil\n");
                        }
                    //end funkce
                    }
                    break;
                case K_WHILE:
                    lastItem++;
                    if(lastItem >= tableLine){
                        tableLines += tableLines;
                        table = realloc(table, tableLine * sizeof(tableItem_t));
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
}