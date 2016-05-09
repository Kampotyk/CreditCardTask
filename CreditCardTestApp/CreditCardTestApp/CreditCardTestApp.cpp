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

class CreditCardTest
{
private:
	static void IncrementNumericalString(string &numString);
	static void CorrectInvalidCreditCardNumber(string &number);

public:
	static CreditCardVendor GetCreditCardVendor(const string &creditCardNumber);
	static bool IsCreditCardNumberValid(const string &creditCardNumber);
	static string GenerateNextCreditCardNumber(const string &creditCardNumber);
};

void CreditCardTest::IncrementNumericalString(string &numString)
{
	string::reverse_iterator iter = numString.rbegin(), end = numString.rend();
	int carry = 1;
	while (carry && iter != end)
	{
		int value = (*iter - '0') + carry;
		carry = (value / 10);
		*iter = '0' + (value % 10);
		++iter;
	}
	if (carry)
	{
		numString.insert(0, "1");
	}
}

void CreditCardTest::CorrectInvalidCreditCardNumber(string &number)
{
	bool isOdd = true;
	int digit = 0;
	int sum = 0;

	reverse(number.begin(), number.end());
	number.at(0) = '0';
	for (char& c : number)
	{
		digit = c - '0';
		sum += isOdd ? digit : digit / 5 + (2 * digit) % 10;
		isOdd = !isOdd;
	}
	number.replace(0, 1, to_string(sum * 9 % 10));
	reverse(number.begin(), number.end());
}

CreditCardVendor CreditCardTest::GetCreditCardVendor(const string &creditCardNumber)
{
	string number = creditCardNumber;
	number.erase(remove_if(number.begin(), number.end(), isspace), number.end());
	int length = number.length();
	int firstPairOfDigits = stoi(number.substr(0, 2));
	int secondPairOfDigits = stoi(number.substr(2, 2));

	if (length < MIN_LENGTH || length > MAX_LENGTH || !all_of(number.begin(), number.end(), isdigit))
	{
		return CreditCardVendor::UNKNOWN;
	}
	else if (firstPairOfDigits / 10 == 4
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

bool CreditCardTest::IsCreditCardNumberValid(const string &creditCardNumber)
{
	bool isOdd = true;
	int digit = 0;
	int sum = 0;
	string number = creditCardNumber;
	number.erase(remove_if(number.begin(), number.end(), isspace), number.end());
	if (GetCreditCardVendor(number) == CreditCardVendor::UNKNOWN)
	{
		return false;
	}
	reverse(number.begin(), number.end());
	for (char& c : number)
	{
		digit = c - '0';
		sum += isOdd ? digit : digit / 5 + (2 * digit) % 10;
		isOdd = !isOdd;
	}
	return sum % 10 == 0;
}


string CreditCardTest::GenerateNextCreditCardNumber(const string &creditCardNumber)
{
	string number = creditCardNumber;
	number.erase(remove_if(number.begin(), number.end(), isspace), number.end());
	auto curVendor = GetCreditCardVendor(number);

	if (curVendor == CreditCardVendor::UNKNOWN)
	{
		return "";
	}
	if (IsCreditCardNumberValid(number))
	{
		if (number.back() != '9')
		{
			number.back() = '9';
		}
		IncrementNumericalString(number);
		if (GetCreditCardVendor(number) != curVendor)
		{
			return "";
		}
		if (!IsCreditCardNumberValid(number))
		{
			CorrectInvalidCreditCardNumber(number);
		}
	}
	else
	{
		CorrectInvalidCreditCardNumber(number);
	}
	
	return number;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//Examples of using
	cout << (int)CreditCardTest::GetCreditCardVendor("4390 4566 4213 5673") << endl;
	cout << CreditCardTest::IsCreditCardNumberValid("4390 4566 4213 5673") << endl;
	cout << CreditCardTest::IsCreditCardNumberValid("1234 5678 1234 5670") << endl;
	cout << CreditCardTest::GenerateNextCreditCardNumber("1234 5678 1234 5671") << endl;
	cout << CreditCardTest::GenerateNextCreditCardNumber("1234 5678 1234 5670") << endl;
	//Fixed Issues
	cout << (int)CreditCardTest::GetCreditCardVendor("35301113333000001") << endl;
	cout << CreditCardTest::IsCreditCardNumberValid("35301113333000001") << endl;
	cout << CreditCardTest::GenerateNextCreditCardNumber("4999999999999999993") << endl;
	return 0;
}
