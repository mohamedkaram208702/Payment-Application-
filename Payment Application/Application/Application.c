/*
 * Application.c
 *
 *  Created on: Sep 6, 2022
 *      Author: moham
 */
#include "Application.h"

uint8_t Num_Of_account;  				//The index of the PAN in the data base

void appStart(void) {
	/*Declaring Card Data*/
	ST_cardData_t cardData;
	EN_cardError_t cardError;


	/*Declaring Terminal Data*/
	ST_terminalData_t terminalData;
	EN_terminalError_t terminalError;
	EN_serverError_t serverError;
	EN_transStat_t transactionError;

	do
	{
		cardError = getCardHolderName(&cardData);
		if (cardError == WRONG_NAME) {
			printf("Wrong Card Name \n \n");
		}
	} while (cardError != CARD_IS_OK);

	do
	{
		cardError = getCardExpiryDate(&cardData);
		if (cardError == WRONG_EXP_DATE) {
			printf("Wrong Expiration Date \n \n");
		}
	} while (cardError != CARD_IS_OK);

	do
	{
		cardError = getCardPAN(&cardData);
		if (cardError == WRONG_PAN) {
			printf("Wrong Primary Account Number \n \n");
		}
	} while (cardError != CARD_IS_OK);

	do {
		terminalError = getTransactionDate(&terminalData);
		if (terminalError == WRONG_DATE) {
			printf("Wrong Transaction Date \n \n");
		}
	} while (terminalError != Card_is_OK);

	terminalError = isCardExpired(&cardData, &terminalData);
	if (terminalError == EXPIRED_CARD) {
		printf("Declined Process (Expired Card)\n");
		return ;
	}

	do {
		terminalError = getTransactionAmount(&terminalData);
		if (terminalError == INVALID_AMOUNT) {
			printf("Invalid Amount");
		}
	} while (terminalError != Card_is_OK);

	do {
		terminalError = setMaxAmount(&terminalData);
		if (terminalError == INVALID_MAX_AMOUNT) {
			printf("Invalid Maximum Amount");
		}
	} while (terminalError != Card_is_OK);

	terminalError = isBelowMaxAmount(&terminalData);
	if (terminalError == EXCEED_MAX_AMOUNT) {
		printf("Declined Process (Amount Exceeding Limit \n)");
		return ;
	}

	serverError = isValidAccount(&cardData);
	if (serverError == ACCOUNT_NOT_FOUND) {
		printf("Declined Process (stolen Account)");
		return ;
	}

	serverError = isAmountAvailable(&terminalData);
	if (serverError == LOW_BALANCE) {
		printf("Declined Process (Insuffecient Funds)");
		return ;
	}

	ST_transaction_t transactionData = {
		cardData,
		terminalData
	};

	printf("Your Current Balance is: \n%f \n", g_accountsDataBase[Num_Of_account].balance);
	transactionError = recieveTransactionData(&transactionData);
	if (transactionError == APPROVED) {
		printf("Approved Transaction, and your new balance is: \n%f \n", g_accountsDataBase[Num_Of_account].balance);
	}

	return ;
}

