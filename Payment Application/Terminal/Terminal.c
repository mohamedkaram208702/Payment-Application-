/*
 * Terminal.c
 *
 *  Created on: Sep 6, 2022
 *      Author: Mohamed Karam
 */
#include "Terminal.h"
#include <stdio.h>

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){  // This function will ask for the transaction data and store it in terminal data.
	uint8_t Transaction_date[20],Transaction_date_size,i ;
	printf("please enter the Transaction_date  in the format DD/MM/YYYY, e.g 25/06/2022. : \n");
	gets(Transaction_date);
	for(i=0;Transaction_date[i]!='\0';i++){
		if(!((Transaction_date[i]>='0'&& Transaction_date[i] <= '9')|| (Transaction_date[i]=='/'))){
			return WRONG_DATE;
		}
	}
	Transaction_date_size=i;
	if(Transaction_date_size !=10 || Transaction_date[2]!='/' || Transaction_date[5]!='/' ){
		return WRONG_DATE;
	}else{
		for(i=0;Transaction_date[i]!='\0';i++){
			termData->transactionDate[i]=Transaction_date[i];
		}
		termData->transactionDate[i]='\0';
		return Card_is_OK;
	}
}
EN_terminalError_t isCardExpired(ST_cardData_t*cardData, ST_terminalData_t*termData){	//This function compares the card expiry date with the transaction date.
	if (cardData->cardExpirationDate[3] < termData->transactionDate[8]) {
		return EXPIRED_CARD;
	}
	else if (cardData->cardExpirationDate[3] == termData->transactionDate[8]) {
		if (cardData->cardExpirationDate[4] < termData->transactionDate[9]) {
			return EXPIRED_CARD;
		}
		else if (cardData->cardExpirationDate[4] == termData->transactionDate[9]) {
			if (cardData->cardExpirationDate[0] < termData->transactionDate[3]) {
				return EXPIRED_CARD;
			}
			else if (cardData->cardExpirationDate[0] == termData->transactionDate[3]) {
				if (cardData->cardExpirationDate[1] < termData->transactionDate[4]) {
					return EXPIRED_CARD;
				}
				else {
					return Card_is_OK;
				}
			}
			else {
				return Card_is_OK;
			}
		}
		else {
			return Card_is_OK;
		}
	}
	else {
		return Card_is_OK;
	}
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){	//This function asks for the transaction amount and saves it into terminal data.
	float32_t TransactionAmount;
	printf("please enter the TransactionAmount :\n");
	scanf("%f", &TransactionAmount);
	if(TransactionAmount<=0){
		return INVALID_AMOUNT;
	}else{
		termData->transAmount=TransactionAmount;
		return Card_is_OK;
	}
}
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData){	//This function sets the maximum allowed amount into terminal data
	float32_t max_Amount;
		printf("please enter the maximum allowed amount :\n");
		scanf("%f", &max_Amount);
		if(max_Amount<=0){
			return INVALID_MAX_AMOUNT;
		}else{
			termData->maxTransAmount=max_Amount;
			return Card_is_OK;
		}
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){	//This function compares the transaction amount with the terminal max amount
	if(termData->transAmount<=termData->maxTransAmount){
		return Card_is_OK;
	}else{
		return EXCEED_MAX_AMOUNT;
	}
}
