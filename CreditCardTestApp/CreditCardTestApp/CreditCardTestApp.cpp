// CreditCardTestApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
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

CreditCardVendor GetCreditCardVendor(const string &creditCardNumber)
{
	string number = creditCardNumber;
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

bool IsCreditCardNumberValid(const string &creditCardNumber)
{
	bool isOdd = true;
	int digit = 0;
	int sum = 0;
	string number = creditCardNumber;
	number.erase(remove_if(number.begin(), number.end(), isspace), number.end());
	reverse(number.begin(), number.end());
	int length = number.length();

	if (length < MIN_LENGTH || length > MAX_LENGTH || !all_of(number.begin(), number.end(), isdigit))
	{
		return false;
	}
	for (char& c : number) 
	{
		digit = c - '0';
		sum += isOdd ? digit : digit / 5 + (2 * digit) % 10;
		isOdd = !isOdd;
	}
	return sum % 10 == 0;
}


int _tmain(int argc, _TCHAR* argv[])
{
	cout << (int)GetCreditCardVendor("4390 4566 4213 5673") << endl;
	cout << IsCreditCardNumberValid("4390 4566 4213 5673") << endl;
	cout << IsCreditCardNumberValid("1234 5678 1234 5670") << endl;
	
	return 0;
}

