
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolTable.h"
#include "node.h"



int globalLevel = 0;
struct Node* head = NULL;

struct Node* getHead() {
    return head;
}

void printSymbolTable() {    
    struct Node* currentNode = getHead();    
    
    if(currentNode == NULL) printf("no variables have been initialized");

    else {
        printf("___________________________________\n");
        while (currentNode != NULL) 
        {        
            struct nodeValue* value = currentNode->nodeValue;
            switch (value->type) 
            {
                case INT_TYPE:                
                    printf("Name: %s, Type: INT, Value: %d\n",currentNode->name, value->value.integer);
                    break;            
                case DOUBLE_TYPE:
                    printf("Name: %s, Type: DOUBLE, Value: %f\n",currentNode->name, value->value.decimal);   
                    break;
                case STRING_TYPE:                
                    printf("Name: %s, Type: STRING, Value: %s\n",currentNode->name, value->value.string);
                    break;     
                case BOOLEAN_TYPE:
                    printf("Name: %s, Type: BOOLEAN, Value: %s\n", currentNode->name, value->value.boolean ? "true" : "false");   
                    break;
            }
            currentNode = currentNode->next; 
        }
        printf("___________________________________\n");
    }
}



void insertAtBeginning(struct nodeValue* nodeValue, char* name) {

    // check if there is a variable with the same name
    struct nodeValue* node = searchNode( name);
    if(node != NULL){
        printf("already defined a variable with that name");
    }else{
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->nodeValue = nodeValue;
        newNode->name = name;
        newNode->level = globalLevel;
        newNode->next = head;
        head = newNode;
    }
}

void increaseLevel() {
    globalLevel++;
}

void decreaseLevel() {
    struct Node* currentNode = head;
    struct Node* prevNode = NULL;
    globalLevel--;


    while (currentNode != NULL) {
        if (currentNode->level > globalLevel) {
            if (prevNode == NULL) {
                // If the node to be deleted is the head node
                head = currentNode->next;
                free(currentNode);
                currentNode = head;
            } else {
                prevNode->next = currentNode->next;
                free(currentNode);
                currentNode = prevNode->next;
            }
        } else {
            prevNode = currentNode;
            currentNode = currentNode->next;
        }
    }
}

struct nodeValue* searchNode(char* name) {
    struct Node* currentNode = getHead();

    while (currentNode != NULL) {
        if (strcmp(currentNode->name, name) == 0) {
            return currentNode->nodeValue;
        }
        currentNode = currentNode->next;
    }

    // printf("variable %s not defined\n", name);
    return NULL;
    // exit(1);
      // Node with the specified name was not found
}

void updateNode(struct nodeValue* value, char* name){
    struct nodeValue* node = searchNode(name);

    if(node == NULL){
        printf("variable %s not defined\n", name);
    }else{
    switch (node->type) {
        case INT_TYPE:                
            node->value.integer = value->value.integer;
            break;            
        case DOUBLE_TYPE:
            node->value.decimal = value->value.decimal;   
            break;
        case STRING_TYPE:                
            node->value.string = value->value.string;
            break;     
        case BOOLEAN_TYPE:
            node->value.boolean = value->value.boolean;   
            break;
        }

    }
}
