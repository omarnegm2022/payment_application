#include"app.h"

/*There should be if test to:
1. recall the function for proper input.(recursion)
2. close the program due to nonvalidation.>>DONE!*/

void appStart(void) 
{
// Card section:-
	ST_card_t c_info = { "NA","NA","NA" };
	getCardHolderName(&c_info);
	
	getCardExpiryDate(&c_info);
	
	getCardPAN(&c_info);
	
	//printf("\n holder_name: %s\n prim_account_num: %s\n expiry_date: %s",
	//c_info.holder_name,c_info.prim_account_num,c_info.expiry_date);
//____________________________________________________________________________
// Terminal section:-
	ST_terminal_t t_info = { 0.0,0.0,"NA" };
	getTransactionDate(&t_info);
	if (isCardExpired(&c_info, &t_info) == EXPIRED_CARD)
	{//RESULT(SAD_1): expired card user story

		printf("\n Declined: expired card.");
		//printf("\n holder_name: %s\n prim_account_num: %s\n expiry_date: %s", 
		//	c_info.holder_name, c_info.prim_account_num, c_info.expiry_date);
		//printf("\n trans_amount: NA\n max_amount: NA\n transaction_date: %s", t_info.transaction_date);
		return;
	}
	
	getTransactionAmount(&t_info);

	if (isBelowMaxAmount(&t_info) == EXCEED_MAX_AMOUNT)
	{//RESULT(SAD_2): exceed the maximum amount user story

		printf("\n Declined: amount exceeding limit.");
		//printf("\n holder_name: %s\n prim_account_num: %s\n expiry_date: %s", 
		//	c_info.holder_name, c_info.prim_account_num, c_info.expiry_date);
		//printf("\n trans_amount: NA\n max_amount: %f\n transaction_date: %s", 
		//	 t_info.max_amount, t_info.transaction_date);
		return;
	}
	
	//printf("\n trans_amount: %f\n max_amount: %f\n transaction_date: %s", 
	//	t_info.trans_amount, t_info.max_amount, t_info.transaction_date);
//____________________________________________________________________________
// Server section:-
	ST_transaction_t s_transaction_info = { c_info ,t_info ,0 ,0010 };
	ST_accounts_t s_account_info = { 0.0,0,"NA" };

	switch (recieveTransactionData(&s_transaction_info))
//NOTE: This switch includes account validation and amount availablity, as well as
//(contd.)for happy user story: updating the balance and saving transaction.
	{
	case FRAUD_CARD:	//	if (isValidAccount(...) == DECLINED_STOLEN_CARD), or
	case DECLINED_STOLEN_CARD: //if (isBlockedAccount(...) == BLOCKED_ACCOUNT)
	{//RESULT(SAD_3):Invalid card user story

		printf("\n Declined: invalid account.");
		//printf("\n holder_name: %s\n prim_account_num: %s\n expiry_date: %s", 
		//	c_info.holder_name, c_info.prim_account_num, c_info.expiry_date);
		//printf("\n trans_amount: %f\n max_amount: %f\n transaction_date: %s", 
		//	t_info.trans_amount, t_info.max_amount, t_info.transaction_date);

		return;
	}
	case DECLINED_INSUFFECIENT_FUND:	//	if (isAmountAvailable(...)== LOW_BALANCE)
	{//RESULT(SAD_4): insufficient fund user story

		printf("\n Declined: insuffecient funds.");
		//printf("\n holder_name: %s\n prim_account_num: %s\n expiry_date: %s", 
		//	c_info.holder_name, c_info.prim_account_num, c_info.expiry_date);
		//printf("\n trans_amount: %f\n max_amount: %f\n transaction_date: %s", 
		//	t_info.trans_amount, t_info.max_amount, t_info.transaction_date);

		return;
	}
	default:	//HAPPY_1: transaction approved user story
	{
		printf("\n Updating account balance..");
		saveTransaction(&s_transaction_info);
		return;
	}
	}

}

