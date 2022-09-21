#ifndef CARD_H
#define CARD_H
#include<stdio.h>
#include<string.h>


typedef struct cardData

{//NOTE: no padding will occur in the memory alignment.
	unsigned char holder_name[25];	
	unsigned char prim_account_num[20];
	unsigned char expiry_date[6];	//NOTE: in this way: MM/YY
//(contd.) as when the user types the date, '\0' is added implicitly defining the end of the string.
}ST_card_t;

typedef enum dataError
{
	CARD_OK,WRONG_NAME,WRONG_EXP_DATE,WRONG_PAN
}EN_cardCheck_t;

EN_cardCheck_t getCardHolderName(ST_card_t* cardata);
EN_cardCheck_t getCardExpiryDate(ST_card_t* cardata);
EN_cardCheck_t getCardPAN(ST_card_t* cardata);

#endif // !CARD_H
