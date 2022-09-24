#ifndef _APP_C_
#define _APP_C_
#include <stdio.h>
#include <string.h>
#include "../card/card.h"
#include "../terminal/terminal.h"
#include "../server/server.h"
#include "app.h"


int fun_return;
ST_cardData_t card_struct;
ST_terminalData_t terminal_struct;
ST_transaction_t server_struct;
EN_cardError_t flag_card;
EN_terminalError_t flag_terminal ;
ST_accountsDB_t account_struct;
EN_serverError_t flag_server;
enum EN_transState_t flag_trans;
void appstart(){
  // first call card function
  //we take the card data from user
  printf("hello in our bank\n");
  fun_return=WRONG_NAME;
  while(fun_return == WRONG_NAME){ 
      fun_return=getCardHolderName(&card_struct);
      if(fun_return == WRONG_NAME)
          printf("you enter invalid name reenter it again\n");
      else
         break;
  }
  fun_return=WRONG_EXP_DATE;
  while(fun_return == WRONG_EXP_DATE){ 
      fun_return=getCardExpiryDate(&card_struct);
      if(fun_return == WRONG_EXP_DATE)
          printf("you enter invalid date reenter it again\n");
      else
         break;
  }
  fun_return=WRONG_PAN;
  while(fun_return == WRONG_PAN){ 
      fun_return=getCardPAN(&card_struct);
      if(fun_return == WRONG_PAN)
          printf("you enter invalid PAN reenter it again\n");
      else
         break;
  }
  ////////////////////////////////////////////////////////////////
  // call funcations of terminal
  //here we get the current date and the tran amount and max trans amount
  // and test if tran amount > max trans amount
  fun_return=WRONG_DATE;
  while(fun_return == WRONG_DATE){ 
      fun_return=getTransactionDate(&terminal_struct);
      if(fun_return == WRONG_DATE)
          printf("you enter invalid date reenter it again\n");
      else
         break;
  }
  fun_return=INVALID_AMOUNT;
  while(fun_return == INVALID_AMOUNT){ 
      fun_return= getTransactionAmount(&terminal_struct);
      if(fun_return == INVALID_AMOUNT)
          printf("you enter invalid amount reenter it again\n");
      else
         break;
  }
  fun_return=INVALID_MAX_AMOUNT;
  while(fun_return == INVALID_MAX_AMOUNT){ 
      fun_return=setMaxAmount(&terminal_struct);
      if(fun_return == INVALID_MAX_AMOUNT)
          printf("you enter invalid amount reenter it again\n");
      else
         break;
  }
  fun_return=EXCEED_MAX_AMOUNT;
  while(fun_return == EXCEED_MAX_AMOUNT){ 
      fun_return=isBelowMaxAmount(&terminal_struct);
      if(fun_return == EXCEED_MAX_AMOUNT){
          printf("you enter invalid amount\n");
          exit(1);
      }
      else{
         break;
      }
  }
  /// call server funcation to valid the card PAN and amount and do operations on DB
  fun_return = isValidCardPAN(&terminal_struct);
  if(fun_return == INVALID_CARD){
    printf("you have enter invalid PAN\n");
    exit(1);
  }
  fun_return=isCardExpired(card_struct,terminal_struct);
  if (fun_return == EXPIRED_CARD )
  {
    printf("you use expired card\n");
    exit(1);
  }
// we assign the structures
server_struct.cardHolderData=card_struct ;
server_struct.terminalData = terminal_struct;
// recieve funcation 
flag_trans=recieveTransactionData(&server_struct);
if (flag_trans == DECLINED_STOLEN_CARD) {
		printf("DECLINED STOLEN CARD/INVALID ACCOUNT\n");
}
else if (flag_trans== DECLINED_INSUFFECIENT_FUND) {
		printf("DECLINED_INSUFFECIENT_FUND\n");
}
else if (flag_trans == APPROVED){
		printf("APPROVED\n");
}
else{
        printf("error\n");
}
// at last save our transaction
fun_return=saveTransaction(&server_struct);
if (fun_return == OK_server)
{
    printf("SAVING TRANSACTION\n");
}
else{
    printf("Failed Saving\n");
}
}

#endif
