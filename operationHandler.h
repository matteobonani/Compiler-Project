#ifndef OPERATIONHANDLER_H
#define OPERATIONHANDLER_H
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "node.h"


struct NumberDictionary{
    char str[10];
    int number;
};  



void translateString(char* s, int* res) ;

struct nodeValue* doOperation(struct nodeValue* node1, struct nodeValue* node2, char operator);

struct nodeValue* handleStrings(struct nodeValue* node1, struct nodeValue* node2, char operator);

struct nodeValue* handleIntDouble(struct nodeValue* node1, struct nodeValue* node2, char operator);

struct nodeValue* handleTwoInteger(struct nodeValue* node1, struct nodeValue* node2, char operator);


#endif 