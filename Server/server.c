#include"server.h"

// server-side accounts' database
ST_accounts_t accounts_base[5] = { {1000.0,RUNNING,"45632587963215892"}, {2000.0,BLOCKED,"65897542314569879"}, \
{3000.0, RUNNING,"96521435897563215"}, {4000.0,BLOCKED,"23657896542147825"}, \
{5000.0,RUNNING,"45897852548789852"}
};

// server-side transactions' database
ST_transaction_t transaction_base[5] = { {0 //card holder data
,										  0 //terminal data
,                                         0 //transaction state
,                                         0 //transaction sequence number
										 }
, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} };

ST_accounts_t* ref_info = NULL; //NOTE: used in  isValidAccount() for isBlockedAccount().

int validity_flag = 0;	// NOTE: used to test isValid..() function with a printf().
int serving = -1;		//NOTE: incremented when a transaction is processed into the server.
 EN_serverCheck_t blocking_flag ;	// NOTE: used in two functions, especially for isAmount..().
 
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	serving += 1;
// NOTE: At this point, we have: cardHolderData and terminalData. the sequenceNumber and the state are left.
	//ST_accounts_t* accountRef = NULL;
	printf("\nTransaction state:");
	if (isValidAccount(&(transData->cardHolderData), ref_info) == ACCOUNT_NOT_FOUND)	//i.e. the account does not exist.!validity_flag
	{
		printf("\n FRAUD_CARD");
		transData->transtate = FRAUD_CARD;
		return FRAUD_CARD;
	}
	blocking_flag = isBlockedAccount(ref_info);
	if (blocking_flag == BLOCKED_ACCOUNT) //ref_info->state == BLOCKED
	{
		printf("\n DECLINED_STOLEN_CARD");
		transData->transtate = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}
	if (isAmountAvailable(&(transData->termData)) == LOW_BALANCE)//ref_info->balance < transData->termData.trans_amount
	{
		printf("\n DECLINED_INSUFFECIENT_FUND");
		transData->transtate = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}
	

// NOTE: There is another condition for saving failure, returns INTERNAL_SERVER_ERROR, I forgot to mention it in
	// the video.
	
	else
	{
		printf("\n APPROVED");
		ref_info->balance -= transData->termData.trans_amount;
		transData->transtate = APPROVED;
		//saveTransaction(transData);
		return APPROVED;
	}
}

EN_serverCheck_t isValidAccount(ST_card_t* cardata, ST_accounts_t* accountRef)
{
	printf("\nSearching for the account..");
	for (int i = 0; i < 5; i += 1)		//NOTE: using Linear_search algorithm.
	{
		accountRef = accounts_base+i;
		if (!strcmp(cardata->prim_account_num, accountRef->primaryAccountNumber))
		{
			validity_flag = 1;
			printf("\n ACCOUNT_FOUND");
			ref_info = accountRef;	//NOTE: this is passed to isBlockedAccount().
			return SERVER_OK;
		}
	}
	if (!validity_flag)
	{
		printf("\n ACCOUNT_NOT_FOUND");
	}
	return ACCOUNT_NOT_FOUND;
//SAD_3: hence, the application closes here -according to the flowchart-.
}

EN_serverCheck_t isBlockedAccount(ST_accounts_t* accountRef)
{
	accountRef = ref_info;		//NOTE ! : Keep this assignment if
	// this function is not called from the function:recieveTransactionData().
		
		
		if (accountRef->state == RUNNING)
		{
			printf("\n RUNNING_ACCOUNT");
			blocking_flag = SERVER_OK;
			return SERVER_OK;
		}
		else //if(s_info->state == BLOCKED)
		{
			printf("\n BLOCKED_ACCOUNT");
			blocking_flag = BLOCKED_ACCOUNT;
			return BLOCKED_ACCOUNT;
		}
}

EN_serverCheck_t isAmountAvailable(ST_terminal_t* termData)
{	
		if (blocking_flag == SERVER_OK)	//i.e. RUNNING
		{	printf("\n Checking the amount..");
			if (termData->trans_amount > ref_info->balance)
			{
				printf("\n LOW_BALANCE");
				return LOW_BALANCE;
//SAD_4: hence, the application closes here -according to the flowchart-.
			}
			else
			{
				printf("\n Amount available");
				return SERVER_OK;
			}
		}
		return 123;
}


EN_serverCheck_t getTransaction_flag = 12;	//NOTE: as enumeration members are integer values.

EN_serverCheck_t saveTransaction(ST_transaction_t* transData)
{		serving = 0;
	printf("\n saving transaction..\n");

// NOTE: Only if transaction is APPROVED, in accordance to the flowchart.
		// NOTE: up to 5 transactions can be saved in case of repetition.
		transData->transactionSeqNumber = 1000 + serving;	//1000
		transaction_base[serving] = *transData;
		getTransaction_flag = getTransaction(&(transData->transactionSeqNumber), transData);
		if (getTransaction_flag == TRANSACTION_NOT_FOUND)
		{
			printf("\n SAVING_FAILED");
			return SAVING_FAILED;
		}
/*
The transaction data are distributed in the 3 modules, each detail in its corresponding module -but all are in the 
transaction_base.
For transaction sequence number, it is written in the transaction data base in the first empty place and its next..respectively in each
transaction, and each sequence number is larger than its previous by 1.
So if a specific sequence number doesn't equal the expected value, hence data related to that sequence number
are not saved because of failureor  any other reason.
*/
		else if (getTransaction_flag == SERVER_OK)
		{
			printf("\n # saveTransaction():\n");
			printf("\n SERVER_OK");
			return SERVER_OK;
		}
		return 123;
}

EN_serverCheck_t getTransaction(unsigned int* transactionSeqNumber, ST_transaction_t* transData)
{
	//*transactionSeqNumber = 123;	//Try.
	printf("\n getting transaction..\n");
	for (int i = 0; i < 5; i += 1)
	{
		transData = transaction_base+i;
		if (*transactionSeqNumber == transData->transactionSeqNumber)
		{
			printf("\n ***\tInvoice\t***");
		printf("\nCard holder_name: %s", transData->cardHolderData.holder_name);	//cardHolderData
		printf("\nTransaction amount: %f\nTransaction date: %s",	\
		transData->termData.trans_amount,transData->termData.transaction_date);	//termData
		printf("\n transaction state: SERVER_OK");	//transtate
		printf("\n transaction sequence number: %u",transData->transactionSeqNumber);	//transactionSeqNumber
		printf("\n New balance: %f", ref_info->balance);

		getTransaction_flag = SERVER_OK;
		return SERVER_OK;
			
		}
	}
	printf("\n # getTransaction():\n");
	printf("\n TRANSACTION_NOT_FOUND");
	getTransaction_flag = TRANSACTION_NOT_FOUND;
	return TRANSACTION_NOT_FOUND;
}