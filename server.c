#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../terminal/terminal.h"
#include "../card/card.h"
#include "server.h"
int index_account,fun_feedback,seq_num=0; 
ST_accountsDB_t accountDB[255]={{10000,"4539651279053633"},{50000,"4024007174233162"},{500000,"2720996246877983"},{000000,"5583770862909514"}};
ST_transaction_t savetransDB[255]={0};
enum EN_transState_t recieveTransactionData(ST_transaction_t *transData){
if(isValidAccount(&transData->cardHolderData) ==ACCOUNT_NOT_FOUND){
    return DECLINED_STOLEN_CARD;
 }
 else if (isAmountAvailable(&transData->terminalData) ==LOW_BALANCE)
 {
    return DECLINED_INSUFFECIENT_FUND;
 }
 else if (saveTransaction(&transData) == SAVING_FAILED)
 {
    return INTERNAL_SERVER_ERROR;
 }
 else{
    accountDB[index_account].balance -= transData->terminalData.transAmount;  
    printf("your balance now=%f\n",accountDB[index_account].balance);
    return APPROVED;
 }
}
EN_serverError_t isValidAccount(ST_cardData_t *cardData){
int i,found,j;
for (int i = 0; i<255; i++){
 for ( j = 0; j <= strlen(cardData->primaryAccountNumber); j++)
 {
    if(cardData->primaryAccountNumber[j]==accountDB[i].primaryAccountNumber[j]){
        found = 1;
    }
    else{
        found=0;
        break;
    }  
 }
if (found == 1)
    {
        index_account=i;
        break;
    }
}
/////////////
if (found==1)
{
    return OK_server;
}
else{
    return ACCOUNT_NOT_FOUND;
}
}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData){
int balance;
if (accountDB[index_account].balance>= termData->transAmount)
{
    return OK_server;
}
else{
 return LOW_BALANCE;
}
}
EN_serverError_t saveTransaction(ST_transaction_t *transData){
if (seq_num >= 255)
{
   return SAVING_FAILED;
}
else{
savetransDB[seq_num].cardHolderData=transData->cardHolderData;
savetransDB[seq_num].terminalData=transData->terminalData;
savetransDB[seq_num].transState=transData->transState;
savetransDB[seq_num].transactionSequenceNumber=seq_num;
seq_num++;
return OK_server;
}
}
EN_serverError_t getTransaction(int transactionSequenceNumber, ST_transaction_t *transData){
  for (int i = 0; i < 255; i++)
  {
    if(savetransDB[i].transactionSequenceNumber == transactionSequenceNumber){
        transData=&savetransDB[i];
        return OK_server;
    }
  }
  return TRANSACTION_NOT_FOUND;
}
