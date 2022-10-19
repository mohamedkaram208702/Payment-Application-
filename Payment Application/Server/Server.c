/*
 * Server.c
 *
 *  Created on: Sep 6, 2022
 *      Author: moham
 */
#include <stdio.h>
#include <string.h>
#include "Server.h"
#include "../Application/Standard_datatypes.h"
#include "../Card/Card.h"
EN_serverError_t isValidAccount(ST_cardData_t* cardData) {
	uint8_t i,j,valid=0;
	for (j = 0; (j < 20 && valid == 0); j++) {
		for (i = 0; cardData->primaryAccountNumber[i] != '\0'; i++) {
			if (cardData->primaryAccountNumber[i] == g_accountsDataBase[j].primaryAccountNumber[i]) {
				valid = 1;
			}
			else {
				valid = 0;
				break;
			}
		}
	}
	if (valid == 0) {
		return ACCOUNT_NOT_FOUND;
	}
	else {
		Num_Of_account = j-1;
		return Server_OK;
	}
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {
	/*This function will take terminal data and validate these data.
	It checks if the transaction's amount is available or not.*/
	if (termData->transAmount > g_accountsDataBase[Num_Of_account].balance) {
		return LOW_BALANCE;
	}
	else {
		return Server_OK;
	}
}
EN_serverError_t saveTransaction(ST_transaction_t *transData){
	static uint8_t transactionNumber=0;
	transData->transactionSequenceNumber = transactionNumber;
	memcpy(&g_transactionDataBase[transactionNumber], transData, sizeof(*transData));
	transactionNumber++;
	return Server_OK;
}
EN_transStat_t recieveTransactionData(ST_transaction_t* transData) {
	/*This function will take all transaction data and valid
	 its data. It checks the account details and amount availability.
	 If the account does not exist return DECLINED_STOLEN_CARD,
	 if the amount is not available will return DECLINED_INSUFFECIENT_FUND,
	 if a transaction can't be saved will return INTERNAL_SERVER_ERROR
	 and will not save the transaction, else returns APPROVED.
	 It will update the database with the new balance */
	if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND) {
		transData->transState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}
	else if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE) {
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}
	else if (saveTransaction(&transData) == SAVING_FAILED) {
		return INTERNAL_SERVER_ERROR;
	}
	else {
		g_accountsDataBase[Num_Of_account].balance -= transData->terminalData.transAmount;
		return APPROVED;
	}
}
