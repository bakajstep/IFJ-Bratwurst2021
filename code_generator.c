//
// Created by adam on 29.11.21.
//

#include "code_generator.h"



void codeFromToken(token_type_t type, token_t token, symTree_t tree){
    static int tableSize = TABLE_SIZE;
    static tableItem_t table = NULL;
    static int lastItem = -1;
    static bool move = false;
    static bool write = false;
    static bool defTerm = false;
    static char *defId = false;

    if(table == NULL){
        table = malloc(stackSize * sizeof(tableItem_t));
    }

    if(lastItem + 1 >= tableSize){
        tableSize += tableSize;
        table = realloc(table, tableSize * sizeof(tableItem_t));
    }

    switch(type){
        case T_IDENTIFIER:
            if(strcmp(token->attribute->string, "print") == 0){
                write = true;
            }else if(defTerm){
                defID = token->data;

            }
            break;

        default:break;
    }
}.
/*TODO built-in functions*/

/*TODO define built-in functions*/

/*TODO generate file header*/

/*TODO define code gen values*/

/*TODO clean code gen values*/

/*TODO main function*/

/*TODO function code*/

/*TODO Variable*/

/*TODO Input */

/*TODO Print*/

/*TODO operator stack*/

/*TODO concat*/

/*TODO Var length*/

/*TODO label*/

/*TODO if*/

/*TODO while*/