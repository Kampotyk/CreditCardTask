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

CreditCardVendor GetCreditCardVendor(const string &inCreditCardNumber)
{
	auto number = inCreditCardNumber;
	number.erase(remove_if(number.begin(), number.end(), isspace), number.end());
	int length = number.length();
	int firstPairOfDigits = stoi(number.substr(0,2));
	int secondPairOfDigits = stoi(number.substr(2, 2));

	if (length < MIN_LENGTH || length > MAX_LENGTH || !all_of(number.begin(), number.end(), isdigit))
	{
		return CreditCardVendor::UNKNOWN;
	}
	else if (firstPairOfDigits/10 == 4
		&& (length == 13 || length == 16 || length == 19))
	{
		return CreditCardVendor::VISA;
	}
	else if ((firstPairOfDigits == 50 || (firstPairOfDigits >= 56 && firstPairOfDigits <= 69))
		&& (length >= 12 && length <= 19))
	{
		return CreditCardVendor::MAESTRO;
	}
	else if ((firstPairOfDigits >= 51 && firstPairOfDigits <= 55)
		&& length == 16)
	{
		return CreditCardVendor::MASTERCARD;
	}
	else if ((firstPairOfDigits == 34 || firstPairOfDigits == 37)
		&& length == 15)
	{
		return CreditCardVendor::AMERICAN_EXPRESS;
	}
	else if (firstPairOfDigits == 35
		&& (secondPairOfDigits >= 28 && secondPairOfDigits <= 89)
		&& length == 16)
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
	GetCreditCardVendor("4390 4566 4213 5673");
	return 0;
}

