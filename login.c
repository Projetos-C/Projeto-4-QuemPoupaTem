#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

Value login(Conta contas[], int *pos, int *user){
    printf("Login");
    return OK;
}; 
Value cadastro(Conta contas[], int *pos, int *user){
    printf("cadastro");
    return OK;
}; 

Value hash(char senha[], int *pos){
     printf("hash");
}
Value hash_compare(char hash[], char senha[], int *pos){
     printf("compare");
}