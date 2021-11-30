//
// Created by adam on 29.11.21.
//

#ifndef IFJ_BRATWURST2021_CODE_GENERATOR_H
#define IFJ_BRATWURST2021_CODE_GENERATOR_H

#include <string.h>
#include "scanner.h"
#include "symtable.h"

#define TABLE_SIZE 10;

typedef struct tableItem{
    bool isIf;
    int id;
} *tableItem_t;

#endif //IFJ_BRATWURST2021_CODE_GENERATOR_H
