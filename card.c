char string_test[100] = "11111111111";	//NOTE: used in case of exceeding string limit of the name, date, or PAN.

#include"card.h"
EN_cardCheck_t getCardHolderName(ST_card_t* cardata)
{
	printf("Enter your name:\n");
	gets_s(string_test,100);
//NOTE: safer than gets(), avoiding debug error when exceeding the array size.

	size_t name_length = strlen(string_test);//NOTE: instead of int type,
	//(contd.) avoiding loss of data. according to the warning: C4267
//(contd.) It's typedef of an unsinged integer type.
 
	if ((string_test == NULL) || (name_length  < 20) || (name_length > 24))
	{
		printf("\nWRONG_NAME");
/*		getCardHolderName(cardata);		*/
		return WRONG_NAME;
	}
	else
	{
		strcpy_s(cardata->holder_name,25, string_test);
		printf("\nNAME_OK");
		return CARD_OK;
	}
}

EN_cardCheck_t getCardExpiryDate(ST_card_t* cardata)
{
	printf("\nEnter the expiry date(month/year): ");
	gets_s(string_test, 100);
	int date_text_length = (int)strlen(string_test);
	//NOTE: using type casting, as strlen() returns size_t value.
	
	if ((string_test == NULL) || (date_text_length < 5) || (date_text_length > 5))
	{
		printf("\nWRONG_EXPIRY_DATE");
/*		getCardExpiryDate(cardata);     */
		return WRONG_EXP_DATE;
	}
	else if ((string_test[2] != '/'))	//NOTE: checking the format,
		// but it's exhausting to check the numbers as well.
	{
		printf("\nWRONG_EXPIRY_DATE");
/*		getCardExpiryDate(cardata);     */
		return WRONG_EXP_DATE;
	}
	else
	{
		strcpy_s(cardata->expiry_date, 6, string_test);
		printf("\nEXPIRY_DATE_OK");
		return CARD_OK;
	}
}
EN_cardCheck_t getCardPAN(ST_card_t* cardata)
{
	printf("\nEnter the primary account number: ");
	gets_s(string_test, 100);
	size_t PAN_length = strlen(string_test);
	
	if ((string_test == NULL) || (PAN_length < 16) || (PAN_length > 19))
	{
		printf("\nWRONG_PAN");
/*		getCardPAN(cardata);     */
		return WRONG_PAN;
	}
	else
	{	printf("\nPAN_OK");
		strcpy_s(cardata->prim_account_num, 20, string_test);
		return CARD_OK;
	}
	
}