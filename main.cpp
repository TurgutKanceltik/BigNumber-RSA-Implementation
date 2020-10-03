#include <iostream>
#include "LongNumber.h"
#include "RsaModule.h"

using namespace std;

int main()
{
	LongNumber TestNum1 = *new LongNumber("98765");
	LongNumber TestNum2 = *new LongNumber("65432");
	LongNumber TestNum3 = *new LongNumber("54321");

	LongNumber ResultNum;

	cout << "TestNum1: " + TestNum1.getString();
	cout << "TestNum2: " + TestNum1.getString();
	cout << "TestNum3: " + TestNum1.getString();
	cout << endl;

	ResultNum = TestNum1 + TestNum2;
	cout << "operator '+' result (TestNum1 + TestNum2) is: " + ResultNum.getString();
	cout << endl;

	ResultNum = TestNum1 - TestNum2;
	cout << "operator '-' result (TestNum1 - TestNum2) is: " + ResultNum.getString();
	cout << endl;

	ResultNum = TestNum1 * TestNum2;
	cout << "operator '*' result (TestNum1 * TestNum2) is: " + ResultNum.getString();
	cout << endl;

	ResultNum = TestNum1 / TestNum2;
	cout << "operator '/' result (TestNum1 / TestNum2) is: " + ResultNum.getString();
	cout << endl;

	cout << "ResultNum = 0";
	cout << endl;
	ResultNum = *new LongNumber("0");
	ResultNum += TestNum1;
	cout << "operator '+=' result (ResultNum += TestNum1) is: " + ResultNum.getString();
	cout << endl;
	cout << endl;

	cout << "ResultNum = 98766";
	cout << endl;
	ResultNum = *new LongNumber("98766");
	ResultNum -= TestNum1;
	cout << "operator '-=' result (ResultNum -= TestNum1) is: " + ResultNum.getString();
	cout << endl;
	cout << endl;

	while (true)
	{
		RsaModule rsaModule;
		rsaModule.testRsa();
		cout << "Loop Done...";
		cout << endl;
		cout << endl;
	}

	return 0;
}
