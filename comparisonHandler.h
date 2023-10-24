#include "node.h"
#include <stdbool.h>


struct nodeValue* doComparison(struct nodeValue* node1, struct nodeValue* node2, char* operator);

struct nodeValue* compareBool(struct nodeValue* node1, struct nodeValue* node2, char* operator);

struct nodeValue* compareStrings(struct nodeValue* node1, struct nodeValue* node2, char* operator);

struct nodeValue* compareDoubles(struct nodeValue* node1, struct nodeValue* node2, char* operator);

struct nodeValue* compareIntegers(struct nodeValue* node1, struct nodeValue* node2, char* operator);

struct nodeValue* isEqualWithTolerance(struct nodeValue* node1, struct nodeValue* node2, double tolerance) ;

bool stringsAreEqualIgnoreCase(const char* str1, const char* str2);