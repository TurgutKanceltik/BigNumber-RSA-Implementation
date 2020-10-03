#include "RsaModule.h"
#include <iostream>

using namespace std;

LongNumber RsaModule::Keygen(LongNumber* p, LongNumber* q, LongNumber* e, int lenght)
{
	LongNumber temp;
	string answ;
	cout << "Do you want to set values manually ? (yes/no): ";
	cin >> answ;
	if (answ == "yes")
	{
		cout << "'P': ";
		cin >> answ;
		*p = *new LongNumber(answ);

		cout << "'Q': ";
		cin >> answ;
		*q = *new LongNumber(answ);

		cout << "'E': ";
		cin >> answ;
		*e = *new LongNumber(answ);
	}
	else
	{
		*p = temp.generateprime(lenght);
		*q = temp.generateprime(lenght);
		*e = temp.generateprime(lenght);
	}

	cout << "'P' value : " + (*p).getString() << endl;
	cout << "'Q' value : " + (*q).getString() << endl;
	cout << "'E' value : " + (*e).getString() << endl;

	bool answer;
	while (true)
	{
		answer = (*p).IsPrime();
		if (answer == false)
		{
			cout << "'P' is not prime please set again: ";
			*p = temp.generateprime(lenght);
			cout << "'P' new value : " + (*p).getString() << endl;
		}
		else
			break;
	}

	while (true)
	{
		answer = (*q).IsPrime();
		if (answer == false)
		{
			cout << "'Q' is not prime please set again: ";
			*q = temp.generateprime(lenght);
			cout << "'Q' new value : " + (*q).getString() << endl;
		}
		else
			break;
	}

	while (true)
	{
		answer = (*e).IsPrime();
		if (answer == false)
		{
			cout << "'E' is not prime please set again: ";
			*e = temp.generateprime(lenght);
			cout << "'E' new value : " + (*e).getString() << endl;
		}
		else
			break;
	}

	LongNumber One;
	One._bigNumber.Num[0] = 1;
	LongNumber PMinusOne = (*p).Sub(One);
	LongNumber QMinusOne = (*q).Sub(One);
	LongNumber PhiValue = PMinusOne.Mul(QMinusOne);

	cout << "'Phi' Value: ";
	cout << PhiValue.getString() << endl;

	return PhiValue;
}

LongNumber RsaModule::RsaEncrypt(LongNumber e, LongNumber n)
{
	string msg;
	cout << "Encrypt Value: ";
	cin >> msg;

	LongNumber result = *new LongNumber(msg);
	result = result.ExpMod(e, n);

	cout << "Secret: " + result.getString() << endl;
	return result;
}

LongNumber RsaModule::RsaDecrypt(LongNumber d, LongNumber n)
{
	string msg;
	cout << "Decrypt Value: ";
	cin >> msg;

	LongNumber result = *new LongNumber(msg);
	result = result.ExpMod(d, n);

	cout << "Result: " + result.getString() << endl;
	return result;
}

void RsaModule::testRsa()
{
	RsaModule rsaModule;
	LongNumber* PArray = new LongNumber("0");
	LongNumber* QArray = new LongNumber("0");
	LongNumber* EArray = new LongNumber("0");

	LongNumber phi = rsaModule.Keygen(PArray, QArray, EArray, 2);

	cout << "'N' Value: ";
	LongNumber n = (*PArray).Mul(*QArray);
	string Print = n.getString();
	cout << Print << endl;

	LongNumber encryptValue = rsaModule.RsaEncrypt((*EArray), n);

	cout << "'D' Value: ";
	LongNumber d = (*EArray).Inverse(phi);
	Print = d.getString();
	cout << Print << endl;

	LongNumber decryptValue = rsaModule.RsaDecrypt(d, n);
}