// CreditCardTestApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <algorithm>

using namespace std;

const int MIN_LENGTH = 12;
const int MAX_LENGTH = 19;

enum class CreditCardVendor
{
	UNKNOWN,
	AMERICAN_EXPRESS,
	MAESTRO,
	MASTERCARD,
	VISA,
	JCB
};

CreditCardVendor GetCreditCardVendor(string &cardNumber)
{
	cardNumber.erase(remove_if(cardNumber.begin(), cardNumber.end(), isspace), cardNumber.end());
	int cardNumberlength = cardNumber.length();
	int firstSecondDigits = stoi(cardNumber.substr(0,2));
	int thirdFourthDigits = stoi(cardNumber.substr(2, 2));

	if (cardNumberlength < MIN_LENGTH || cardNumberlength > MAX_LENGTH || !all_of(cardNumber.begin(), cardNumber.end(), isdigit))
	{
		return CreditCardVendor::UNKNOWN;
	}
	else if (firstSecondDigits/10 == 4
		&& (cardNumberlength == 13 || cardNumberlength == 16 || cardNumberlength == 19))
	{
		return CreditCardVendor::VISA;
	}
	else if ((firstSecondDigits == 50 || (firstSecondDigits >= 56 && firstSecondDigits <= 69))
		&& (cardNumberlength >= 12 && cardNumberlength <= 19))
	{
		return CreditCardVendor::MAESTRO;
	}
	else if ((firstSecondDigits >= 51 && firstSecondDigits <= 55)
		&& cardNumberlength == 16)
	{
		return CreditCardVendor::MASTERCARD;
	}
	else if ((firstSecondDigits == 34 || firstSecondDigits == 37)
		&& cardNumberlength == 15)
	{
		return CreditCardVendor::AMERICAN_EXPRESS;
	}
	else if (firstSecondDigits == 35
		&& (thirdFourthDigits >= 28 && thirdFourthDigits <= 89)
		&& cardNumberlength == 16)
	{
		return CreditCardVendor::JCB;
	}
	else
	{
		return CreditCardVendor::UNKNOWN;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

