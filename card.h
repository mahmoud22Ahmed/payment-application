#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED
typedef struct ST_cardData_t
{
char cardHolderName[25];
char primaryAccountNumber[20];
char cardExpirationDate[6];
}ST_cardData_t;
typedef enum EN_cardError_t
{
OK=0, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);
#endif // CARD_H_INCLUDED
