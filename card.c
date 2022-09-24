#include <stdio.h>
#include "card.h"
#include <stdio.h>
#include <string.h>
EN_cardError_t flag ;
EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
printf("enter card holder name: ");
gets(cardData->cardHolderName);
//check its validity
if(strlen(cardData->cardHolderName)>=20 &&strlen(cardData->cardHolderName)<=24){
        flag = OK;
        return flag;
}
else{
    flag = WRONG_NAME;
    return flag;
}
}
////////////////////////////
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
flag = WRONG_EXP_DATE;
printf("enter card expiry date in format MM/YY: ");
gets(cardData->cardExpirationDate);
//check its validity
if(strlen(cardData->cardExpirationDate) ==5){
     if(cardData->cardExpirationDate[2]=='/'){
      if(cardData->cardExpirationDate[0]=='0' || cardData->cardExpirationDate[0]=='1'){
        flag = OK;
        return flag;
      }
    else{
    flag =  WRONG_EXP_DATE;
    return flag;
     }
     }
     else{
    flag =  WRONG_EXP_DATE;
    return flag;
     }
}
else{
    flag =  WRONG_EXP_DATE;
    return flag;
}
}
///////////////////////////////////////
EN_cardError_t getCardPAN(ST_cardData_t *cardData){
flag = WRONG_PAN;
printf("enter card PAN number: ");
gets(cardData->primaryAccountNumber);
//check its validity
if(strlen(cardData->primaryAccountNumber)>=16 &&strlen(cardData->primaryAccountNumber)<=20){
     flag = OK;
     return flag;
}
else{
    return flag;
}
}

