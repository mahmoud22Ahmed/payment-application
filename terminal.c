#include <stdio.h>
#include <stdlib.h>
#include "terminal.h"
#include "../card/card.h"
//ST_terminalData_t terminal_struct;
EN_terminalError_t terminal_enum;

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
    terminal_enum = WRONG_DATE;
    printf("enter the date of transaction: ");
    gets(termData->transactionDate);
    // test its validity
    if(termData->transactionDate[2]=='/' && termData->transactionDate[5]=='/'){
            if(termData->transactionDate[3]=='0' || termData->transactionDate[3]=='1'){
                terminal_enum = OK_terminal;
                return terminal_enum;
            }
            else{
                terminal_enum = WRONG_DATE;
                return terminal_enum;
        
            }
    }
    else{
                terminal_enum = WRONG_DATE;
                return terminal_enum;
    }
}
////////////////////////////////////////
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData){
int parity,i,size,num,sum=0;
size=strlen(cardData->primaryAccountNumber);
if (size%2 == 0)
{
    parity=1;
}
else{
    parity=0;
}
switch (parity)
{
case 1:
for (int i = 0; i < size; i++){
    if (i%2 ==0)
    {
    num= cardData->primaryAccountNumber[i] -'0';
    num *=2;
    if (num >9)
    {
        sum += num%10;
        num /=10;
        sum+=num;
    }
    else{
        sum +=num;
    }
    }
    else{
    num= cardData->primaryAccountNumber[i] -'0';
    sum += num;
    }
    }
    break;
case 0:
for (int i = 0; i < size; i++){
    if (i%2 !=0)
    {
    num= cardData->primaryAccountNumber[i] -'0';
    num *=2;
    if (num >9)
    {
        sum += num%10;
        num /=10;
        sum+=num;
    }
    else{
        sum +=num;
    }
    }
    else{
    num= cardData->primaryAccountNumber[i] -'0';
    sum += num;
    }
    }
    break;
default:
    break;
}
if(sum %10 == 0){
terminal_enum = OK_terminal;
return terminal_enum;
}
else{
terminal_enum = INVALID_CARD;
return terminal_enum;
}
}
////////////////////////////////////////////
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
   terminal_enum = INVALID_AMOUNT;
    printf("enter the transaction amount that you want: ");
    scanf("%f",&termData->transAmount);
    // test the amount 
    if(termData->transAmount <= 0){
        return terminal_enum;
    }
    else{
        terminal_enum = OK_terminal;
        return terminal_enum;
        //break;
    }
   }
//////////////////////////////////////////////////////
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData){
    terminal_enum = INVALID_MAX_AMOUNT;
    printf("enter the max transaction amount : ");
    scanf("%f",&termData->maxTransAmount);
    // test the amount 
    if(termData->maxTransAmount <= 0){
         return terminal_enum;

    }
    else{
        terminal_enum = OK_terminal;
        return terminal_enum;
    }
   }
//////////////////////////////////////////////
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
  terminal_enum = EXCEED_MAX_AMOUNT;
  while (terminal_enum = EXCEED_MAX_AMOUNT)
  {
    if(termData->transAmount > termData->maxTransAmount){
        return terminal_enum;
    }
    else{
        terminal_enum = OK_terminal;
        return terminal_enum;
    }
  }
}
////////////////////////////////////////////////
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData){
char date[6],subdate[3],subexdate[3]; //it will hold the date of transation in format MM/YY
int ex_num,transnum;
    for (int i = 0; i < 2; i++)
    {
        date[i]=termData.transactionDate[i+3];
    }
    date[2]='/';
    for (int i = 3; i < 5; i++)
    {
        date[i]=termData.transactionDate[i+5];
    }
for (int i = 0; i < 2; i++)
{
strncpy(subdate,&date[3-i*3],2);
strncpy(subexdate,&cardData.cardExpirationDate[3-i*3],2);
ex_num = atoi(subexdate);
transnum=atoi(subdate);
if (ex_num>transnum)
{
    return OK_terminal ;
    continue;
}
else if (ex_num<transnum)
{
return EXPIRED_CARD;
break;
}
}
}
