#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"




void errorHand(char* string){
    printf("%s\n",string);
    exit(1);
}

struct nodeValue* create_node(struct nodeValue* node, char type) {

    struct nodeValue* result = NULL;

    switch(node->type){

        case INT_TYPE:
            if(type == 'i') result = create_int_node(node->value.integer);
            else errorHand("invalid type.\nrequired int");
            break;
        case DOUBLE_TYPE:
            if(type == 'd') result = create_double_node(node->value.decimal);
            else errorHand("invalid type.\nrequired dec");
            break;
        case STRING_TYPE:
            if(type == 's') result = create_string_node(node->value.string);
            else errorHand("invalid type.\nrequired string");
            break;
    }

    return result;

}



char* format(char* str) {
    if (str == NULL || str[0] == '\0') {
        return NULL;  // Handle null or empty string
    }

    size_t length = strlen(str);
    char* newStr = malloc(length);  // Allocate memory for the new string
    if (newStr == NULL) {
        return NULL;  // Failed to allocate memory
    }

    // Copy the string starting from the second character
    memmove(newStr, str + 1, length - 2);
    newStr[length - 1] = '\0';  // Null-terminate the new string

    return newStr;
}

void addDoubleQuotes(char* str) {
    size_t length = strlen(str);
    memmove(str + 1, str, length);
    str[0] = '"';
    str[length + 1] = '"';
    str[length + 2] = '\0';
}

struct nodeValue* create_int_node(int value) {
    
    struct nodeValue* node = (struct nodeValue*)malloc(sizeof(struct nodeValue));
    node->type = INT_TYPE;
    node->value.integer = value;
    return node;
}

struct nodeValue* create_double_node(double value) {
    struct nodeValue* node = (struct nodeValue*)malloc(sizeof(struct nodeValue));
    node->type = DOUBLE_TYPE;
    node->value.decimal = value;
    return node;
}

struct nodeValue* create_string_node(char* value) {
    struct nodeValue* node = (struct nodeValue*)malloc(sizeof(struct nodeValue));
    node->type = STRING_TYPE;
    node->value.string = value;
    return node;
}

struct nodeValue* create_boolean_node(bool value) {
    struct nodeValue* node = (struct nodeValue*)malloc(sizeof(struct nodeValue));
    node->type = BOOLEAN_TYPE;
    node->value.boolean = value;
    return node;
}


