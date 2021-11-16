/**
 * Project: Compiler for IFJ21 language
 *
 * Brief:   Symbol table implemented by binary tree
 *
 * Author:  Adam Kankovsky   <xkanko00@stud.fit.vutbr.cz>
 *
 * Date:    12-11-2021
 */

#include "symtable.h"

void symTableInit(symTree_t **tree){

    if(!(*tree)){
        return;
    }
    (*tree) = NULL;
}

T_symData *symTableSearch(symTree_t *tree, char *key){
    while(tree != NULL){

        if(tree->key == key){
            *value = tree->value;
            return true;
        }

        if(tree->key > key){
            tree = tree->left;
        } else if(tree->key < key){
            tree = tree->right;
        }
    }
    return false;
}

T_symData *symTableInsert(symTree_t **tree, char *key, symData_t data){
    if(tree == NULL){
        return;
    }

    while((*tree) != NULL){

        if((*tree)->key == key){
            (*tree)->value = value;
            return;
        }

        if(((*tree)->key) > key){
            tree = &((*tree)->left);
        } else if(((*tree)->key) < key){
            tree = &((*tree)->right);
        }
    }

    (*tree) = (bst_node_t *)malloc(sizeof(bst_node_t));
    if((*tree) == NULL) return;
    (*tree)->key = key;
    (*tree)->value = value;
    (*tree)->left = NULL;
    (*tree)->right = NULL;
}

void symTableDispose(symTree_t **tree){
    if((*tree) != NULL){
        if((*tree)->left != NULL) symTableDispose(&((*tree)->left));
        if((*tree)->right != NULL) symTableDispose(&((*tree)->right));
        free((*tree));
        (*tree) = NULL;
    }
}

