#ifndef TERMINAL_H
#define TERMINAL_H
#include"..\Card\card.h"	//NOTE: for validation of:
// card expiration date, and correctness of PAN.

typedef struct terminalData
{
	float trans_amount;
	float max_amount;
	unsigned char transaction_date[11];	//NOTE: in this format>> DD/MM/YYYY
}ST_terminal_t;

typedef enum terminalError
{
	TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalCheck_t;

EN_terminalCheck_t getTransactionDate(ST_terminal_t* termData);
EN_terminalCheck_t isCardExpired(ST_card_t* cardData, ST_terminal_t* termData);
EN_terminalCheck_t isValidCardPAN(ST_card_t* cardData);						// NOTE: optional for Luhn number.
EN_terminalCheck_t getTransactionAmount(ST_terminal_t* termData);	
EN_terminalCheck_t isBelowMaxAmount(ST_terminal_t* termData);

EN_terminalCheck_t setMaxAmount(ST_terminal_t* termData);//NOTICE: same way of implementation
//(contd.) as getTransactionAmount().
#endif // !TERMINAL_H
