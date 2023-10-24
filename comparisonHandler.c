#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "comparisonHandler.h"
#include "operationHandler.h"
#include "node.h"


struct nodeValue* doComparison(struct nodeValue* node1, struct nodeValue* node2, char* operator){
    struct nodeValue* result = (struct nodeValue*)malloc(sizeof(struct nodeValue));

    // two booleana case
    if(node1->type == BOOLEAN_TYPE || node2->type == BOOLEAN_TYPE){
        result = compareBool(node1, node2, operator);
    }
    // two int case
    if((node1->type == INT_TYPE) && (node2->type == INT_TYPE)){
        result = compareIntegers(node1, node2, operator);
    }
    // int or double case
    else if ((node1->type == INT_TYPE || node1->type == DOUBLE_TYPE) && (node2->type == INT_TYPE || node2->type == DOUBLE_TYPE)){
        result = compareDoubles(node1, node2, operator);
    }
    // one is a string
    else if(node1->type == STRING_TYPE || node2->type == STRING_TYPE){
        

        result = compareStrings(node1, node2, operator);
        
    }
    return result;
}

struct nodeValue* compareBool(struct nodeValue* node1, struct nodeValue* node2, char* operator){

    struct nodeValue* result = (struct nodeValue*)malloc(sizeof(struct nodeValue));

    if(node1->type == BOOLEAN_TYPE && node2->type == BOOLEAN_TYPE){

        if(strcmp(operator, "==")){
            result = create_boolean_node(node1->value.boolean == node2->value.boolean);
        }else{
            printf("cannot compare booleans with operator %s\n", operator);
        }

    }
}


struct nodeValue* compareStrings(struct nodeValue* node1, struct nodeValue* node2, char* operator){

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

        result = compareIntegers(node1, node2, operator);
    }

    if(node1->type == STRING_TYPE && node2->type == STRING_TYPE){
        if(strcmp(operator, "==")){
            result = create_boolean_node(strcmp(node1->value.string, node2->value.string));
        }else if(strcmp(operator, "=C=")){
            bool value = stringsAreEqualIgnoreCase(node1->value.string, node2->value.string);
            result = create_boolean_node(value);
        }

    }



    //TODO ERROR handler
    return result;
}


struct nodeValue* compareDoubles(struct nodeValue* node1, struct nodeValue* node2, char* operator){

    struct nodeValue* result = create_boolean_node(true);

    double n1 = 0;
    double n2 = 0;

    if(node1->type == INT_TYPE){
        n1 = node1->value.integer;
    }else{
        n1 = node1->value.decimal;
    }

     if(node1->type == INT_TYPE){
        n2 = node2->value.integer;
    }else{
        n2 = node2->value.decimal;
    }


    if(strcmp(operator, ">") == 0){
        result->value.boolean = n1 > n2;
    }else if(strcmp(operator,"<") == 0){
        result->value.boolean = n1 < n2;
    }else if (strcmp(operator, ">=") == 0){
        result->value.boolean = n1 >= n2;
    }else if(strcmp(operator, "<=") == 0){
        result->value.boolean = n1 <= n2;
    }else if(strcmp(operator, "==") == 0){
        result->value.boolean = n1 == n2;
    }

    

    return result;
}


struct nodeValue* compareIntegers(struct nodeValue* node1, struct nodeValue* node2, char* operator){

    struct nodeValue* result = create_boolean_node(true);




    int n1 = node1->value.integer;
    int n2 = node2->value.integer;

   if(strcmp(operator,">") == 0){
        result->value.boolean = n1 > n2;
    }else if(strcmp(operator, "<") == 0){
        result->value.boolean = n1 < n2;
    }else if (strcmp(operator, ">=") == 0){
        result->value.boolean = n1 >= n2;
    }else if(strcmp(operator, "<=") == 0){
        result->value.boolean = n1 <= n2;
    }else if(strcmp(operator, "==") == 0){
        result->value.boolean = n1 == n2 ? true : false;
    }
    return result;
}

struct nodeValue* isEqualWithTolerance(struct nodeValue* node1, struct nodeValue* node2, double tolerance) {

    struct nodeValue* result = create_boolean_node(true);

    double n1 = 0;
    double n2 = 0;

    if(node1->type == INT_TYPE) n1 = node1->value.integer;
    else if(node1->type == DOUBLE_TYPE) node1->value.decimal;
    else printf("invalid comparison\n");

    if(node2->type == INT_TYPE) n1 = node2->value.integer;
    else if(node2->type == DOUBLE_TYPE) node2->value.decimal;
    else printf("invalid comparison\n");
    

    double diff = fabs(n1 - n2);
    result->value.boolean = diff <= tolerance ? true : false;

    return result;
}

bool stringsAreEqualIgnoreCase(const char* str1, const char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if (len1 != len2) {
        return false; // Strings are not equal in length
    }

    for (int i = 0; i < len1; i++) {
        char ch1 = tolower(str1[i]);
        char ch2 = tolower(str2[i]);

        if (ch1 != ch2) {
            return false; // Characters are not equal
        }
    }

    return true; // Strings are equal
}

