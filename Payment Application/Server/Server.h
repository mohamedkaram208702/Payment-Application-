/*
 * Server.h
 *
 *  Created on: Sep 6, 2022
 *      Author: moham
 */
// Header Guard
#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_
#include "../Application/Standard_datatypes.h"
#include "../Card/Card.h"
#include "../Terminal/Terminal.h"

typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR
}EN_transStat_t;

typedef enum EN_serverError_t
{
	Server_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE
}EN_serverError_t ;

typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t  terminalData;
	EN_transStat_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction_t;

typedef struct ST_accountsDB_t
{
	float balance;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

EN_transStat_t recieveTransactionData(ST_transaction_t *transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData);
EN_serverError_t saveTransaction(ST_transaction_t *transData);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData);


extern ST_transaction_t g_transactionDataBase[20];
extern ST_accountsDB_t g_accountsDataBase[20];
extern uint8_t Num_Of_account;   				//The index of the PAN in the data base

#endif /* SERVER_SERVER_H_ */
