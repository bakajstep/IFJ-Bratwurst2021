/**
 * Project: Compiler for IFJ21 language
 *
 * Brief:   Symbol table implemented by binary tree
 *
 * Author:  Adam Kankovsky   <xkanko00@stud.fit.vutbr.cz>
 * Author:  David Chocholaty <xchoch09@stud.fit.vutbr.cz>
 *
 * Date:    12-11-2021
 */

#include "symtable.h"
#include <stdlib.h>
#include <string.h>

void symTableInit(symTree_t **tree){

    if(!(*tree)){
        return;
    }
    (*tree) = NULL;
}

void symDataInit(symData_t** data){
    *data = (symData_t*) malloc(sizeof(symData_t));

    if(!(*data)){
        err = E_INTERNAL;
        return;
    }
    (*data)->declared = true;
    (*data)->defined = false;
    (*data)->data_type = NIL;
    (*data)->params_count = 0;
    (*data)->first_param = NULL;
    (*data)->first_ret = NULL;
}

void paramInsert(symData_t* data, data_type_t type, char* param_name){
    function_params_t* newParam = (function_params_t*) malloc(sizeof(function_params_t));

    if(!newParam){
        err = E_INTERNAL;
        return;
    }
    newParam->param_name = param_name;
    newParam->param_type = type;

    if(data->first_param == NULL){
        data->first_param = newParam;
        data->first_param->param_next = NULL;
    }else{
        function_params_t* current;
        current = data->first_param;

        while(current != NULL){
            current = current->param_next;
        }
        current = newParam;
        current->param_next = NULL;
    }
}

void paramTypeInsert(symData_t* data, data_type_t type){
    function_params_t* newParam = (function_params_t*) malloc(sizeof(function_params_t));

    if(!newParam){
        err = E_INTERNAL;
        return;
    }
    newParam->param_type = type;

    if(data->first_param == NULL){
        data->first_param = newParam;
        data->first_param->param_next = NULL;
    }else{
        function_params_t* current;
        current = data->first_param;

        while(current != NULL){
            current = current->param_next;
        }
        current = newParam;
        current->param_next = NULL;
    }
}

void returnInsert(symData_t* data, data_type_t type){
    function_returns_t* newReturn = (function_returns_t*) malloc(sizeof(function_returns_t));

    if(!newReturn){
        err = E_INTERNAL;
        return;
    }
    newReturn->return_type = type;

    if(data->first_ret == NULL){
        data->first_ret = newReturn;
        data->first_ret->ret_next = NULL;
    }else{
        function_returns_t* current;
        current = data->first_ret;

        while(current != NULL){
            current = current->ret_next;
        }
        current = newReturn;
        current->ret_next = NULL;
    }
}

symData_t* symTableSearch(symTree_t* tree, char* key){
    while(tree != NULL){

        if(strcmp(tree->key, key) == 0){
            return tree->data;
        }

        if(strcmp(tree->key, key) > 0){
            tree = tree->nextLeft;
        } else if(strcmp(tree->key, key) < 0){
            tree = tree->nextRight;
        }
    }
    return NULL;
}

void symTableInsert(symTree_t **tree, char* key, symData_t* data){
    if(*tree == NULL){
        return;
    }

    while((*tree) != NULL){

        if(strcmp((*tree)->key, key) == 0){
            err = E_INTERNAL;
            return;
        }

        if(strcmp((*tree)->key, key) > 0){
            tree = &((*tree)->nextLeft);
        } else if(strcmp((*tree)->key, key) < 0){
            tree = &((*tree)->nextRight);
        }
    }

    (*tree) = (symTree_t *)malloc(sizeof(symTree_t));
    if(!(*tree)){
        err = E_INTERNAL;
        return;
    }
    if((*tree) == NULL) return;
    strcpy((*tree)->key, key);
    *(*tree)->data = *data;
    (*tree)->nextLeft = NULL;
    (*tree)->nextRight = NULL;
}

void paramDispose(function_params_t* param){
    if(param != NULL){
        if(param->param_next != NULL) paramDispose(param->param_next);
        free(param);
        param = NULL;
    }
}

void returnDispose(function_returns_t* returns){
    if(returns != NULL){
        if(returns->ret_next != NULL) returnDispose(returns->ret_next);
        free(returns);
        returns = NULL;
    }
}

void symTableDispose(symTree_t **tree){
    if((*tree) != NULL){
        if((*tree)->nextLeft != NULL) symTableDispose(&((*tree)->nextLeft));
        if((*tree)->nextRight != NULL) symTableDispose(&((*tree)->nextRight));
        paramDispose((*tree)->data->first_param);
        returnDispose((*tree)->data->first_ret);
        free((*tree)->data);
        free((*tree));
        (*tree) = NULL;
    }
}

