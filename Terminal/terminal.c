#include"terminal.h"
EN_terminalCheck_t getTransactionDate(ST_terminal_t* termData)
{
	printf("\nEnter the transaction date: ");		
//TRY: 25/06/2022
	gets_s(termData->transaction_date,11);
//NOTICE: safer than gets(), as well as gets() it is undefinde according to the warning C4013

	size_t trans_date_length = strlen(termData->transaction_date);
	if ((termData->transaction_date == NULL) || (trans_date_length < 10))
	{
		printf("\n WRONG_DATE ");
		return WRONG_DATE;
	}
	else if ((termData->transaction_date[2] != '/') || (termData->transaction_date[5] != '/'))
//NOTE: testeing the format of the given date.
	{
		printf("\n WRONG_DATE ");
		return WRONG_DATE;
	}
	else
	{
		printf("\n TERMINAL_OK");
		return TERMINAL_OK;
	}
}

EN_terminalCheck_t isCardExpired(ST_card_t* cardData, ST_terminal_t* termData)
{

	char small_transDate[6] = "00000"; //NOTE: intial-
//izing for proper execution.
		
//NOTE: I implemented this method:
	int jmp = 0, index = 0;
//NOTE: It's as making a subset array of the transaction date.
	for (int i = 3; i < 10; i++)
	{
		index = i - 3 - jmp;
//NOTE: just getting MM/ and the most right 2 digits of the year.
		small_transDate[index] = termData->transaction_date[i];
		if (i == 5)
		{
			i += 2;
			jmp = 2;
		}	
	}
//(contd."this method:") so that I can easily compare the month and the year of transaction and expiry dates,
//(contd.) because of the riddle of variation between their formats.

	if (strcmp(cardData->expiry_date, small_transDate) < 0)	//NOTE:
// It won't give proper result every time. 
	{
		printf("\nEXPIRED_CARD");
		return EXPIRED_CARD;
//SAD_1: hence, the application closes here -according to the flowchart-.
	}
	else
	{
		printf("\nNot expired.");
		return CARD_OK;
	}

}

EN_terminalCheck_t isValidCardPAN(ST_card_t* cardData)	// NOTE: optional function for Luhn number.
{
	int state = getCardPAN(cardData); //NOTE: as the enum member is int type.
	if (state == WRONG_PAN)
	{
		//printf("\n INVALID_CARD");
		return INVALID_CARD;
	}
	else //if (state == CARD_OK)
	{
		//printf("\n TERMINAL_OK");
		return TERMINAL_OK;
	}
}

EN_terminalCheck_t getTransactionAmount(ST_terminal_t* termData)
{
	printf("\nEnter the transaction amount: ");
	scanf_s("%f", &(termData->trans_amount));		//NOTE: safer than scanf()
	if (termData->trans_amount <= 0.0)
	{
		printf("\nINVALID_AMOUNT");
/*		getTransactionAmount(termData);		*/
		return INVALID_AMOUNT;
		
	}
	else
	{
		printf("\nAMOUNT_OK");
		return TERMINAL_OK;
	}
}

EN_terminalCheck_t isBelowMaxAmount(ST_terminal_t* termData)
{
	setMaxAmount(termData); //NOTE: no need to define
//(contd.) the function before calling it, as it is declared in the header file.
	if (termData->trans_amount > termData->max_amount)
	{
		printf("\n EXCEED_MAX_AMOUNT");
		return EXCEED_MAX_AMOUNT;
//SAD_2: hence, the application closes here -according to the flowchart-.

	}
	else
	{
		printf("\n Below max amount");
		return TERMINAL_OK;
	}
}

EN_terminalCheck_t setMaxAmount(ST_terminal_t* termData)	
{
	printf("\n [terminal_limit]Enter the max amount: ");
	scanf_s("%f", &(termData->max_amount));
	if (termData->max_amount <= 0.0)
	{
		printf("\n INVALID_MAX_AMOUNT ");
/*		setMaxAmount(termData);		*/
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		printf("\n MAX_AMOUNT_OK");
		return TERMINAL_OK;
	}
}
