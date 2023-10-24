#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "node.h"
#include "operationHandler.h"

void translateString(char* str, int* res) {
    struct NumberDictionary mappings[] = {
        {"ZERO", 0},
        {"ONE", 1},
        {"TWO", 2},
        {"THREE", 3},
        {"FOUR", 4},
        {"FIVE", 5},
        {"SIX", 6},
        {"SEVEN", 7},
        {"EIGHT", 8},
        {"NINE", 9}
    };

    int numMappings = sizeof(mappings) / sizeof(mappings[0]);

    int i = 0;
    for (i = 0; i < numMappings; i++) {
        if (strcmp(str, mappings[i].str) == 0) {
            *res = mappings[i].number;
            i = numMappings;
        }
    }
}

struct nodeValue* doOperation(struct nodeValue* node1, struct nodeValue* node2, char operator){

    struct nodeValue* result = (struct nodeValue*)malloc(sizeof(struct nodeValue));

    // two booleana case
    if(node1->type == BOOLEAN_TYPE || node2->type == BOOLEAN_TYPE){
        //error handler
    }
    // two int case
    if((node1->type == INT_TYPE) && (node2->type == INT_TYPE)){
        result = handleTwoInteger(node1, node2, operator);
        return result;
    }
    // int or double case
    else if ((node1->type == INT_TYPE || node1->type == DOUBLE_TYPE) && (node2->type == INT_TYPE || node2->type == DOUBLE_TYPE)){
        result = handleIntDouble(node1, node2, operator);
        return result;

    }
    // one is a string
    else if(node1->type == STRING_TYPE || node2->type == STRING_TYPE){
        result = handleStrings(node1, node2, operator);
        return result;

    }
}

struct nodeValue* handleStrings(struct nodeValue* node1, struct nodeValue* node2, char operator){ 
    
 
    struct nodeValue* result = (struct nodeValue*)malloc(sizeof(struct nodeValue)); 
 
    // first one is a string 
    if(node1->type == STRING_TYPE){ 
        int res = -1;
        translateString(format(node1->value.string), &res); 

        if(res != -1){ 
            node1->value.integer = res; 
            node1->type = INT_TYPE; 
        }
    } 
    // second one is a string 
    if(node2->type == STRING_TYPE){ 
        int res = -1;
        translateString(format(node2->value.string), &res); 

        if(res != -1){ 
            node2->value.integer = res; 
            node2->type = INT_TYPE; 
        } 
    } 

    // now with translatede string, we check if both are int 
    if((node1->type == INT_TYPE) && (node2->type == INT_TYPE)){ 
        result = handleTwoInteger(node1, node2, operator); 
        return result;
    }else if((node1->type == INT_TYPE || node1->type == DOUBLE_TYPE) && (node2->type == INT_TYPE || node2->type == DOUBLE_TYPE)){ 
        result = handleIntDouble(node1, node2, operator); 
        return result;
    } 
 
    bool f1 = true, f2 = true; 
    if(operator == '+'){ 
         // if first one is a int
        if (node1->type == INT_TYPE) { 
            int intValue = node1->value.integer; 
            int stringSize = snprintf(NULL, 0, "%d", intValue) + 2; 
            node1->value.string = (char*)malloc(stringSize * sizeof(char)); 
            snprintf(node1->value.string, stringSize, "%d", intValue); 
         
            // Update the type to STRING_TYPE 
            node1->type = STRING_TYPE; 
            f1 = false; 
 
        } else if (node1->type == DOUBLE_TYPE) { 
            double decValue = node1->value.decimal; 
            int stringSize = snprintf(NULL, 0, "%f", decValue) + 2; 
            node1->value.string = (char*)malloc(stringSize * sizeof(char)); 
            snprintf(node1->value.string, stringSize, "%f", decValue); 
         
            // Update the type to STRING_TYPE 
            node1->type = STRING_TYPE; 
            f1 = false; 
        } 
        // if second one is int
        if (node2->type == INT_TYPE) { 
            int intValue = node2->value.integer; 
            int stringSize = snprintf(NULL, 0, "%d", intValue) + 2; 
            node2->value.string = (char*)malloc(stringSize * sizeof(char)); 
            snprintf(node2->value.string, stringSize, "%d", intValue); 
 
            // Update the type to STRING_TYPE 
            node2->type = STRING_TYPE; 
            f2 = false; 
 
        } else if (node2->type == DOUBLE_TYPE) { 
            double intValue = node2->value.integer; 
            int stringSize = snprintf(NULL, 0, "%f", intValue) + 2; 
            node2->value.string = (char*)malloc(stringSize * sizeof(char)); 
            snprintf(node2->value.string, stringSize, "%f", intValue); 
         
            // Update the type to STRING_TYPE 
            node2->type = STRING_TYPE; 
            f2 = false; 
        } 
 
        char* str = (char*)malloc(50 * sizeof(char)); 
        char* str1 = (char*)malloc(50 * sizeof(char)); 
        char* str2 = (char*)malloc(50 * sizeof(char)); 
     
        str1 = node1->value.string;
        str2 = node2->value.string;
 
        if(f1) str1 = format(str1);
        
        if(f2) str2 = format(str2);


        str = strcat(str1, str2); 
        addDoubleQuotes(str);
        result = create_string_node(str);  
     
    } 
    return result; 
}

struct nodeValue* handleIntDouble(struct nodeValue* node1, struct nodeValue* node2, char operator){

    struct nodeValue* result = (struct nodeValue*)malloc(sizeof(struct nodeValue));
    double decimal1 = 0;
    double decimal2 = 0;
    
    if(node1->type == INT_TYPE){
        decimal1 = node1->value.integer;
    }else{
        decimal1 = node1->value.decimal;
    }

    if(node2->type == INT_TYPE){
        decimal2 = node2->value.integer;
    }else{
        decimal2 = node2->value.decimal;
    }

    double res = 0;
    switch (operator){        
    case '+':
        res = decimal1 + decimal2;
        result = create_double_node(res);
        break;
    case '-':
        res = decimal1 - decimal2;
        result = create_double_node(res);
        break;
    case '*':
        res = decimal1 * decimal2;
        result = create_double_node(res);
        break;
    case '/':
        res = decimal1 / decimal2;
        result = create_double_node(res);
        break;    
    case 'p':
        res = pow(decimal1, decimal2);
        result = create_double_node(res);
        break;  
    default:
        break;
    }
    return result;
}


struct nodeValue* handleTwoInteger(struct nodeValue* node1, struct nodeValue* node2, char operator){

    struct nodeValue* result = (struct nodeValue*)malloc(sizeof(struct nodeValue));
    result->type = INT_TYPE;
    int res = 0;
    switch (operator){
    case '+':
        res = node1->value.integer + node2->value.integer;
        result = create_int_node(res);
        break;
    case '-':
        res = node1->value.integer - node2->value.integer;
        result = create_int_node(res);
        break;
    case '*':
        res = node1->value.integer * node2->value.integer;
        result = create_int_node(res);
        break;
    case '/':
        res = node1->value.integer / node2->value.integer;
        result = create_int_node(res);
        break;    
    case 'p':
        res = pow(node1->value.integer, node2->value.integer);
        result = create_int_node(res);
        break;  
    default:
        break;
    }
    return result;
}
