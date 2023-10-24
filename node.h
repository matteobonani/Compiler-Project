#ifndef NODE_H
#define NODE_H

#include <stdbool.h>


// variable types 
enum valueType {
    INT_TYPE,
    DOUBLE_TYPE,
    STRING_TYPE,
    BOOLEAN_TYPE,   
};

union nodeData {
    int integer;
    double decimal;
    char* string;
    bool boolean;
};


// object that contains the value and its type
struct nodeValue {
    enum valueType type;
    union nodeData value;
    
};


struct nodeValue* create_node(struct nodeValue* node, char type) ;

struct nodeValue* create_int_node(int value) ;

struct nodeValue* create_double_node(double value);

struct nodeValue* create_string_node(char* value);

struct nodeValue* create_boolean_node(bool value);

char* format(char* str) ;

void addDoubleQuotes(char* str) ;



#endif