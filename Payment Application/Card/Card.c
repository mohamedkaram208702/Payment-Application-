/*
 * Card.c
 *
 *  Created on: Sep 6, 2022
 *      Author: moham
 */
#include "Card.h"
#include <stdio.h>

EN_cardError_t getCardHolderName(ST_cardData_t *cardData){ 	// Function to enter the Card Holder Name.
	uint8_t HolderName[50]={0} ,NameSize, i;
	printf("please enter the holder name : \n");
	gets(HolderName);
	for(i=0;HolderName[i]!='\0';i++){
		if(!((HolderName[i]>='A'&& HolderName[i] <= 'Z')||(HolderName[i]>='a'&& HolderName[i] <= 'z')|| (HolderName[i]==' '))){
			return WRONG_NAME;
		}
	}
	NameSize=i;
	if(NameSize < 20 || NameSize > 24){
		return WRONG_NAME;
	}else{
		for(i=0;HolderName[i]!='\0';i++){
			cardData->cardHolderName[i]=HolderName[i];
		}
		cardData->cardHolderName[i]='\0';
		return CARD_IS_OK   ;
	}

}
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){	// Function to get the Card expired date.
	uint8_t ExpirationDate[10]={0} ,dateSize, i;
	printf("Please Enter the card expired date in the format MM/YY, e.g 05/25 : \n");
	gets(ExpirationDate);
	for(i=0;ExpirationDate[i]!='\0';i++){
		if(!((ExpirationDate[i]>='0'&& ExpirationDate[i] <= '9')|| (ExpirationDate[i]=='/'))){
			return WRONG_NAME;
		}
	}
	dateSize=i;
	if(dateSize != 5 && ExpirationDate[2]!='/'){
		return WRONG_EXP_DATE;
	}else{
		for(i=0;ExpirationDate[i]!='\0';i++){
			cardData->cardExpirationDate[i]=ExpirationDate[i];
		}
		cardData->cardExpirationDate[i]='\0';
		return CARD_IS_OK;
	}

}
EN_cardError_t getCardPAN(ST_cardData_t *cardData){ 	// Function to enter the Card PAN.
	uint8_t PAN[50]={0} ,PAN_Size, i;
	printf("please enter the primary account number : \n");
	gets(PAN);
	for(i=0;PAN[i]!='\0';i++){
		if(!((PAN[i]>='0'&& PAN[i] <= '9'))){
			return WRONG_PAN;
		}
	}
	PAN_Size=i;
	if(PAN_Size < 16 || PAN_Size > 19){
		return WRONG_PAN;
	}else{
		for(i=0;PAN[i]!='\0';i++){
			cardData->primaryAccountNumber[i]=PAN[i];
		}
		cardData->primaryAccountNumber[i]='\0';
		return CARD_IS_OK;
	}

}


