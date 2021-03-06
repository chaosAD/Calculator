#ifndef Evaluate_H
#define Evaluate_H
#include "StringObject.h"
#include "OperatorToken.h"
#include "NumberToken.h"
#include "Stack.h"
#include "Operator.h"


void verifyAllStacksAreEmpty(Stack *dataStack, Stack *operatorStack);
void tryToPushOperatorAndEvaluate(  Operator *opr, Stack *operatorStack, Stack *dataStack );
void doOperatorStackRewinding ( Stack *dataStack , Stack *operatorStack );
Token *convertToPrefixIfNotAlready(Operator *op);
void evaluatePrefixesAndNumber(Token *token, String *expression, Stack *dataStack, Stack *operatorStack);
void evaluatePostfixesAndInfix(Token *token, String *expression, Stack *dataStack , Stack *operatorStack);
int evaluate(String *expression);


#endif // ShuntingYard_H
