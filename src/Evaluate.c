#include <stdio.h>
#include "Evaluate.h"
#include "Token.h"
#include "TokenDebug.h"
#include <malloc.h>
#include "Stack.h"
#include "OperatorToken.h"
#include "NumberToken.h"
#include "Operator.h"
#include "ErrorCode.h"


#define STACK_LENGTH 100
	


void ChooseTheOperation(  Operator *opr, Stack *dataStack ){

 

	switch(opr->info->id)
	{	
		case  ADD_OP:
		executeAdd(dataStack);
		break;
		
		case  SUB_OP:
		executeSub(dataStack);
		break;
		
		case  MUL_OP:
		executeMul(dataStack);
		break;
		
		case  DIV_OP:
		executeDiv(dataStack);
		break;
		
		case  NPERCENT_OP:
		executeModulo(dataStack);
		break;
		
		case  OR_OP:
		executeOr(dataStack);
		break;
		
		default:
		{
			Throw(ERR_UNKNOWN_OPERATOR);
		}
		
	}
}

void tryToPushOperatorAndEvaluate( Operator *opr, Stack *operatorStack,  Stack *dataStack ){
		
	Operator *ptrOpr;   // pointer to operator	
	
	ptrOpr = (Operator *)stackPeep(operatorStack);
	if(  (ptrOpr == NULL)  || (opr->info->precedence > ptrOpr->info->precedence)  ) 
	{	
		stackPush( operatorStack , opr );
	
	}
	else if  (opr->info->precedence <= ptrOpr->info->precedence || opr == NULL )
	{ 
	
		Operator *oprNew = stackPop( operatorStack);
		ChooseTheOperation(  oprNew , dataStack );
       
	}

}

int evaluate(String *expression){

	int Result;
	Token *token;
	Stack *dataStack     = stackNew(STACK_LENGTH);
	Stack *operatorStack = stackNew(STACK_LENGTH);

		do {
			token =getToken(expression);
	
				if ( token!=NULL)    
				{
	
					//token dump function
					if ( token->type == NUMBER_TOKEN)
					{
						Number *num = (Number*)token;	
						stackPush( dataStack   , &num );
					}
	
					else if ( token->type == OPERATOR_TOKEN)
					{
						Operator *opr = (Operator*)token;
						tryToPushOperatorAndEvaluate ( opr, operatorStack , dataStack  );
					}
					//token dump function
			
				}
			} while (token !=NULL);

	Number *ans = (Number *)stackPop( dataStack );
	Result = ans->value;
	
	return Result;

}




