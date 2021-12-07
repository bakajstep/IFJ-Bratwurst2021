/**
 * Project: IFJ21 imperative language compilter
 * 
 * Brief:   Data types for IFJ21 compiler
 * 
 * Author:  Adam Kankovsky   <xkanko00>
 * Author:  Stepan Bakaj     <xbakaj00>
 * Author:  Radek Serejch    <xserej00> 
 * 
 */

#ifndef IFJ_BRATWURST2021_DATA_TYPES_H
#define IFJ_BRATWURST2021_DATA_TYPES_H

typedef enum e_data_type{
    INT,
    NUMBER,
    STR,
    NIL,
    OP,
    ELSE,
    DERR
} data_type_t;

#endif //IFJ_BRATWURST2021_DATA_TYPES_H
