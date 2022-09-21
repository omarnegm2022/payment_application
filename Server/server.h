#ifndef SERVER_H
#define SERVER_H
#include"..\Terminal\terminal.h"
typedef enum transState
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef struct transaction
{
	ST_card_t cardHolderData;
	ST_terminal_t termData;
	EN_transState_t transtate;
	unsigned int transactionSeqNumber;
}ST_transaction_t;

typedef enum serverError
{
	SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverCheck_t;

typedef enum accountState
{
	RUNNING,
	BLOCKED
}EN_accountState_t;

typedef struct accountsDB
{
	float balance;
	EN_accountState_t state;
	unsigned char primaryAccountNumber[20];
}ST_accounts_t; 

EN_transState_t recieveTransactionData(ST_transaction_t* transData);
EN_serverCheck_t isValidAccount(ST_card_t* cardata, ST_accounts_t* accountRef);
EN_serverCheck_t isBlockedAccount(ST_accounts_t* accountRef);
EN_serverCheck_t isAmountAvailable(ST_terminal_t* termData);
EN_serverCheck_t saveTransaction(ST_transaction_t* transData);
EN_serverCheck_t getTransaction(unsigned int* transactionSeqNumber, ST_transaction_t* transData);
#endif // !SERVER_H


