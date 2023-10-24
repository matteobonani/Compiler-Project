#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <stdio.h>

struct Node {
    int level;

    char* name;

    struct nodeValue* nodeValue;
    
    struct Node* next;
};

struct Node* getHead() ;

void insertAtBeginning(struct nodeValue* nodeValue, char* name) ;

void printSymbolTable() ;

void increaseLevel() ;

void decreaseLevel() ;

struct nodeValue* searchNode() ;

void updateNode(struct nodeValue* value, char* name) ;

#endif