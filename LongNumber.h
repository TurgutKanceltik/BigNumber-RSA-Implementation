#pragma once
#include <string>

const int Size2048 = 309;

struct BigNum
{
	int Num[309] = {};
	bool negative = false;
};

struct DivResult
{
	BigNum Result;
	BigNum Remainder;
};

struct ArrayOfArray
{
	BigNum Result;
	BigNum Count;
};

class LongNumber
{
public:

	BigNum _bigNumber;
	DivResult _divResult;
	ArrayOfArray _arrayOfArray;

	LongNumber();
	LongNumber(std::string input);

	void StringToArray(std::string input);
	std::string getString();

	LongNumber CopyOf();
	LongNumber AddFront(int val);
	bool IsZero();
	LongNumber Add(LongNumber number);
	LongNumber Sub(LongNumber number);
	LongNumber Mul(LongNumber number);
	LongNumber DivSmall(LongNumber number);
	LongNumber DivLarge(LongNumber number);
	bool IsPrime();
	LongNumber Inverse(LongNumber mod);
	bool Equal(LongNumber number);

	LongNumber generateprime(int lenght);
	LongNumber generaterandom(int lenght);
	LongNumber addMod(LongNumber number, LongNumber Mod);
	LongNumber multMod(LongNumber number, LongNumber Mod);
	LongNumber ExpMod(LongNumber number, LongNumber Mod);

	friend LongNumber operator+(LongNumber b1, const LongNumber& b2);
	friend LongNumber operator-(LongNumber b1, const LongNumber& b2);
	friend LongNumber operator*(LongNumber b1, const LongNumber& b2);
	friend LongNumber operator/(LongNumber b1, const LongNumber& b2);

	LongNumber& operator+=(const LongNumber& other);
	LongNumber& operator-=(const LongNumber& other);

private:
	int logpower(int n, int p, int mod);
	bool rabinmiller(int n);
};
