/*
 * Terminal.h
 *
 *  Created on: Sep 6, 2022
 *      Author: mohamed karamSS
 */
// Header Guard
#ifndef TERMINAL_TERMINAL_H_
#define TERMINAL_TERMINAL_H_
#include "../Application/Standard_datatypes.h"
#include "../Card/Card.h"


typedef struct ST_terminalData_t
{
float transAmount;
float maxTransAmount;
uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
Card_is_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;


EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);        // Function to get the Transaction Date
EN_terminalError_t isCardExpired(ST_cardData_t*cardData, ST_terminalData_t*termData);   	// Function to check if the card is expired or not
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData);         // Function to check if the card PAN is valid or not
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);	// Function to get the Transaction amount
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);		// Function to check if  the Transaction amount is below max amount
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData);			// This function sets the maximum allowed amount into terminal data.

#endif /* TERMINAL_TERMINAL_H_ */
