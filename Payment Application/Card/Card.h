/*
 * Card.h
 *
 *  Created on: Sep 6, 2022
 *      Author: mohamed KaramS
 */
// Header Guard
#ifndef CARD_CARD_H_
#define CARD_CARD_H_
#include "../Application/Standard_datatypes.h"

typedef struct ST_cardData_t
{
uint8_t cardHolderName[25];
uint8_t primaryAccountNumber[20];
uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
  CARD_IS_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;
 //        Functions prototype
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);  // Function to enter the Card Holder Name.
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);  // Function to get the Card expired date.
EN_cardError_t getCardPAN(ST_cardData_t *cardData);         //Function to get the Card PAN.

#endif /* CARD_CARD_H_ */
