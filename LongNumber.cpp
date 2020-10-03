#include "LongNumber.h"
#include <stack>
using namespace std;

LongNumber::LongNumber()
{
}

LongNumber::LongNumber(string number)
{
	StringToArray(number);
}

void LongNumber::StringToArray(string input)
{
	bool neg = false;

	if (input[0] == 'P' || input[0] == 'p' || input[0] == 'Q' || input[0] == 'q' || input[0] == 'E' || input[0] == 'e')
	{
		input.erase(0, 2);
	}

	if (input[0] == '-')
	{
		neg = true;
		input.erase(0, 1);
	}

	reverse(begin(input), end(input));

	int val = 0, itr = 1, Out = 0;
	for (int i = 0; i < input.size(); i++)
	{
		val += (input[i] - '0') * itr;
		itr *= 10;
		if (itr == 100)
		{
			_bigNumber.Num[Out] = val;
			Out++;
			itr = 1;
			val = 0;
		}
	}

	if (val != 0)
		_bigNumber.Num[Out] = val;

	_bigNumber.negative = neg;
}
LongNumber LongNumber::CopyOf()
{
	LongNumber Result;
	Result._bigNumber.negative = _bigNumber.negative;
	for (int i = 0; i < 309; i++)
		Result._bigNumber.Num[i] = _bigNumber.Num[i];
	return Result;
}
LongNumber LongNumber::AddFront(int val)
{
	LongNumber Result;
	Result._bigNumber.negative = _bigNumber.negative;
	for (int i = 0; i < 308; i++)
		Result._bigNumber.Num[i + 1] = _bigNumber.Num[i];

	Result._bigNumber.Num[0] = val;
	return Result;
}
string LongNumber::getString()
{
	LongNumber temp = (*this).CopyOf();
	string out;
	bool Entered = false;
	if (temp._bigNumber.negative == true)
		out += "-";

	reverse(begin(temp._bigNumber.Num), end(temp._bigNumber.Num));
	int i;
	for (i = 0; i < Size2048; i++)
	{
		if (temp._bigNumber.Num[i] != 0)
			break;
	}
	int itr = 10, val = 0;
	for (int j = 0; j < 2; j++)
	{
		val = temp._bigNumber.Num[i] / itr;
		if (val != 0)
		{
			temp._bigNumber.Num[i] = temp._bigNumber.Num[i] - val * itr;
			out += (val + '0');
			Entered = true;
		}
		else
		{
			if (Entered)
			{
				temp._bigNumber.Num[i] = temp._bigNumber.Num[i] - val * itr;
				out += (val + '0');
			}
		}
		itr /= 10;
	}

	i++;
	for (i; i < Size2048; i++)
	{
		int itr = 10, val = 0;
		for (int j = 0; j < 2; j++)
		{
			val = temp._bigNumber.Num[i] / itr;
			temp._bigNumber.Num[i] = temp._bigNumber.Num[i] - val * itr;
			out += (val + '0');
			itr /= 10;
		}
	}
	return out;
}
bool LongNumber::IsZero()
{
	for (int i = 0; i < Size2048; i++)
	{
		if (_bigNumber.Num[i] != 0)
			return false;
	}
	return true;
}
LongNumber LongNumber::Add(LongNumber number)
{
	if (this->IsZero())
		return number;

	if (number.IsZero())
		return *this;

	LongNumber Result;
	int val = 0, carry = 0;
	bool BothNegative = false;

	if (this->_bigNumber.negative && number._bigNumber.negative)
		BothNegative = true;

	else if (this->_bigNumber.negative)
	{
		this->_bigNumber.negative = false;
		Result = number.Sub(*this);
		return Result;
	}
	else if (number._bigNumber.negative)
	{
		number._bigNumber.negative = false;
		Result = this->Sub(number);
		return Result;
	}
	int i = 0;
	for (i; i < Size2048; i++)
	{
		val = (this->_bigNumber.Num[i] + number._bigNumber.Num[i] + carry) % 100;
		carry = (this->_bigNumber.Num[i] + number._bigNumber.Num[i] + carry) / 100;
		Result._bigNumber.Num[i] = val;
	}

	if (carry != 0)
		Result._bigNumber.Num[i] = carry;

	Result._bigNumber.negative = BothNegative;
	return Result;
}
LongNumber LongNumber::Sub(LongNumber number)
{
	//Op1 - Op2 .. first - second
	if (number.IsZero())
	{
		return *this;
	}
	if (this->IsZero())
	{
		number._bigNumber.negative = true;
		return number;
	}

	LongNumber Result, tempResult, first;
	first = (*this).CopyOf();
	int val = 0, NextToMe = 0;
	bool LastNum = false;

	if (number._bigNumber.negative)
	{
		if (first._bigNumber.negative)
		{
			first._bigNumber.negative = false;
			number._bigNumber.negative = false;
			Result = number.Sub(first);
			return Result;
		}
		else
		{
			number._bigNumber.negative = false;
			Result = first.Add(number);
			return Result;
		}
	}
	else
	{
		if (first._bigNumber.negative)
		{
			first._bigNumber.negative = false;
			number._bigNumber.negative = false;
			Result = first.Add(number);
			Result._bigNumber.negative = true;
			return Result;
		}
	}

	int i = 0;
	for (i; i < Size2048; i++)
	{
		if (LastNum)
			break;
		if (first._bigNumber.Num[i] >= number._bigNumber.Num[i])
		{
			val = first._bigNumber.Num[i] - number._bigNumber.Num[i];
			Result._bigNumber.Num[i] = val;
		}
		else
		{
			if (i == Size2048)
				LastNum = true;

			int temp = i;
			while (temp < 308)
			{
				temp++;
				NextToMe++;
				if (first._bigNumber.Num[temp] != 0)
				{
					first._bigNumber.Num[temp] -= 1;
					first._bigNumber.Num[i] = first._bigNumber.Num[i] + 100;

					NextToMe--;

					temp = i + 1;
					i--;
					while (NextToMe != 0)
					{
						first._bigNumber.Num[temp] = 99;
						NextToMe--;
						temp++;;
					}
					break;
				}
				else if (first._bigNumber.Num[temp] == 0 && temp == 308)
					LastNum = true;
			}
		}
	}

	if (LastNum == true)
	{
		Result = number.Sub(*this);
		Result._bigNumber.negative = true;
		return Result;
	}

	return Result;
}
LongNumber LongNumber::Mul(LongNumber number)
{
	LongNumber Result;

	if (this->IsZero())
		return *this;
	if (number.IsZero())
		return number;

	int val = 0, carry = 0;
	bool neg = false;

	if (this->_bigNumber.negative && number._bigNumber.negative)
	{
		this->_bigNumber.negative = false;
		number._bigNumber.negative = false;
	}
	else if (this->_bigNumber.negative)
	{
		this->_bigNumber.negative = false;
		neg = true;
	}
	else if (number._bigNumber.negative)
	{
		number._bigNumber.negative = false;
		neg = true;
	}

	int i, j;
	for (i = 0; i < Size2048; i++)
	{
		LongNumber temp;
		for (j = 0; j < Size2048; j++)
		{
			val = ((this->_bigNumber.Num[i] * number._bigNumber.Num[j]) + carry) % 100;
			carry = ((this->_bigNumber.Num[i] * number._bigNumber.Num[j]) + carry) / 100;

			temp._bigNumber.Num[j] += val;
		}

		if (i != 0)
		{
			for (int k = 308; k != 0; k--)
			{
				temp._bigNumber.Num[k] = temp._bigNumber.Num[k - i];
			}
			for (int k = 0; k < i; k++)
			{
				temp._bigNumber.Num[k] = 0;
			}
		}
		Result = Result.Add(temp);
	}

	Result._bigNumber.negative = neg;
	return Result;
}
LongNumber LongNumber::DivSmall(LongNumber number)
{
	LongNumber Result;
	//DivResult Result;

	if (this->IsZero())
	{
		Result._divResult.Result = this->_bigNumber;
		Result._divResult.Remainder = this->_bigNumber;
		return Result;
	}

	LongNumber countArray, One, tempResult = *this;
	One._bigNumber.Num[0] = 1;

	bool CheckNeg = tempResult._bigNumber.negative;
	do
	{
		tempResult = tempResult.Sub(number);
		CheckNeg = tempResult._bigNumber.negative;
		if (countArray._bigNumber.Num[0] != 99)
			countArray._bigNumber.Num[0] = countArray._bigNumber.Num[0] + 1;
		else
			countArray = countArray.Add(One);
	} while (!CheckNeg);

	if (countArray._bigNumber.Num[0] != 0)
	{
		countArray._bigNumber.Num[0] = countArray._bigNumber.Num[0] - 1;
		Result._divResult.Result = countArray._bigNumber;
	}
	else
		Result._divResult.Result = countArray.Sub(One)._bigNumber;

	Result._divResult.Remainder = tempResult.Add(number)._bigNumber;

	return Result;
}
LongNumber LongNumber::DivLarge(LongNumber number)
{
	LongNumber temp = (*this).CopyOf();
	LongNumber Result, tempResult, partOffirst, test;

	if (temp.IsZero())
	{
		Result._divResult.Result = temp._bigNumber;
		Result._divResult.Remainder = temp._bigNumber;
	}

	bool neg = false;

	if (temp._bigNumber.negative && number._bigNumber.negative)
	{
		temp._bigNumber.negative = false;
		number._bigNumber.negative = false;
	}
	else if (temp._bigNumber.negative)
	{
		temp._bigNumber.negative = false;
		neg = true;
	}
	else if (number._bigNumber.negative)
	{
		number._bigNumber.negative = false;
		neg = true;
	}
	reverse(begin(temp._bigNumber.Num), end(temp._bigNumber.Num));

	///////
	int i = 0;
	while (i != 309)
	{
		do
		{
			partOffirst = partOffirst.AddFront(temp._bigNumber.Num[i]);
			test = partOffirst.Sub(number);
			i++;
		} while (test._bigNumber.negative && i != 309);

		tempResult = partOffirst.DivSmall(number);
		Result._divResult.Result.Num[309 - i] = tempResult._divResult.Result.Num[0];

		partOffirst._bigNumber = tempResult._divResult.Remainder;
	}
	///////

	Result._bigNumber = Result._divResult.Result;
	Result._divResult.Remainder = partOffirst._bigNumber;
	Result._divResult.Remainder.negative = neg;
	Result._divResult.Result.negative = neg;

	return Result;
}
bool LongNumber::IsPrime()
{
	bool Result = false;
	LongNumber DR;
	LongNumber n = (*this).CopyOf();

	LongNumber One, two, a, NMinusOne, K, tempK, Q, test, Calc, power;

	One._bigNumber.Num[0] = 1;
	two._bigNumber.Num[0] = 2;
	a._bigNumber.Num[0] = 2; // a = 2

	//check if even num
	DR = n.DivLarge(two);
	DR._bigNumber = DR._divResult.Remainder;
	if (DR.IsZero())
		return false;

	NMinusOne = n.Sub(One);

	do
	{
		Q = NMinusOne;
		K = tempK;

		DR = NMinusOne.DivLarge(two);
		NMinusOne._bigNumber = DR._divResult.Result;

		if (K._bigNumber.Num[0] != 99)
			tempK._bigNumber.Num[0] = K._bigNumber.Num[0] + 1;
		else
			tempK = K.Add(One);
		DR._bigNumber = DR._divResult.Remainder;
	} while (DR.IsZero());

	NMinusOne = n.Sub(One);

	Calc = a.ExpMod(Q, n);
	DR = Calc.DivLarge(n);
	DR._bigNumber = DR._divResult.Remainder;
	if (DR.Sub(One).IsZero() || DR.Sub(NMinusOne).IsZero())
		return true;

	if (test._bigNumber.Num[0] != 99)
		test._bigNumber.Num[0] = test._bigNumber.Num[0] + 1;
	else
		test = test.Add(One);

	while (!K.Sub(test).IsZero())
	{
		Calc = Calc.ExpMod(two, n);
		DR = Calc.DivLarge(n);
		DR._bigNumber = DR._divResult.Remainder;
		if (DR.Sub(One).IsZero())
		{
			Result = false;
			break;
		}
		else if (DR.Sub(NMinusOne).IsZero())
		{
			Result = true;
			break;
		}

		if (test._bigNumber.Num[0] != 99)
			test._bigNumber.Num[0] = test._bigNumber.Num[0] + 1;
		else
			test = test.Add(One);
	}

	return Result;
}
LongNumber LongNumber::Inverse(LongNumber mod)
{
	LongNumber Result, Q, A2, A3, B2, B3, T2, T3, Zero, One, temp;
	One._bigNumber.Num[0] = 1;

	A2 = Zero.CopyOf();
	A3 = mod.CopyOf();
	B2 = One.CopyOf();
	B3 = (*this).CopyOf();

	while (!B3.IsZero() && !B3.Sub(One).IsZero())
	{
		Q = A3.DivLarge(B3);
		Q._bigNumber = Q._divResult.Result;

		T2 = A2.Sub(Q.Mul(B2));
		T3 = A3.Sub(Q.Mul(B3));

		A2 = B2.CopyOf();
		A3 = B3.CopyOf();

		B2 = T2.CopyOf();
		B3 = T3.CopyOf();
	}

	if (B3.IsZero())
	{
		//no inverse
		//return 0
	}

	if (B3.Sub(One).IsZero())
	{
		while (B2._bigNumber.negative)
		{
			B2 = B2.Add(mod);
		}
		Result = B2;

		temp = Result.Sub(mod);
		while (!temp._bigNumber.negative)
		{
			Result = temp;
			temp = Result.Sub(mod);
		}
	}

	return Result;
}
bool LongNumber::Equal(LongNumber number)
{
	return false;
}

LongNumber LongNumber::ExpMod(LongNumber number, LongNumber Mod)
{
	if (this->IsZero())
		return *this;

	if (number.IsZero())
	{
		LongNumber hop;
		hop._bigNumber.Num[0] = 1;
		return hop;
	}

	LongNumber first = (*this).CopyOf();
	LongNumber second = number.CopyOf();
	stack<ArrayOfArray> memory;
	LongNumber AoA;

	LongNumber Result, tempResult, Count, tempCount, check, two;
	LongNumber DR;
	two._bigNumber.Num[0] = 2;
	tempCount._bigNumber.Num[0] = 1;
	tempResult = first;
	Result = first;

	do
	{
		DR = tempResult.DivLarge(Mod);
		Result._bigNumber = DR._divResult.Remainder;
		Count = tempCount;
		AoA._arrayOfArray.Result = Result._bigNumber;
		AoA._arrayOfArray.Count = Count._bigNumber;
		memory.push(AoA._arrayOfArray);

		tempCount = Count.Mul(two);
		tempResult = Result.Mul(Result);

		check = second.Sub(tempCount);
	} while (!check._bigNumber.negative);

	Result = *new LongNumber;
	Result._bigNumber.Num[0] = 1;

	while (!second.IsZero())
	{
		AoA._arrayOfArray = memory.top();
		AoA._bigNumber = AoA._arrayOfArray.Count;

		if (!second.Sub(AoA)._bigNumber.negative)
		{
			AoA._bigNumber = AoA._arrayOfArray.Result;
			Result = Result.Mul(AoA);
			DR = Result.DivLarge(Mod);
			Result._bigNumber = DR._divResult.Remainder;

			AoA._bigNumber = AoA._arrayOfArray.Count;
			second = second.Sub(AoA);
		}

		memory.pop();
	}
	return Result;
}

LongNumber LongNumber::addMod(LongNumber number, LongNumber Mod)
{
	LongNumber temp = (*this).CopyOf();
	temp = temp.Add(number);
	temp = temp / Mod;

	temp._bigNumber = temp._divResult.Remainder;

	return temp;
}
LongNumber LongNumber::multMod(LongNumber number, LongNumber Mod)
{
	LongNumber temp = (*this).CopyOf();
	temp = temp.Mul(number);
	temp = temp / Mod;

	temp._bigNumber = temp._divResult.Remainder;

	return temp;
}
LongNumber LongNumber::generateprime(int lenght)
{
	int maxDigit = 1;
	int minDigit = 1;
	for (int i = 0; i < lenght; i++)
	{
		maxDigit = maxDigit * 10;
	}

	for (int i = 0; i < lenght - 1; i++)
	{
		minDigit = minDigit * 10;
	}

	LongNumber result = *new LongNumber("0");
	do
	{
		int generated = rand() % ((maxDigit - minDigit) + 1) + minDigit;
		result = *new LongNumber(std::to_string(generated));
	} while (!result.IsPrime());

	return result;
}

LongNumber LongNumber::generaterandom(int lenght)
{
	int maxDigit = 1;
	int minDigit = 1;
	for (int i = 0; i < lenght; i++)
	{
		maxDigit = maxDigit * 10;
	}

	for (int i = 0; i < lenght - 1; i++)
	{
		minDigit = minDigit * 10;
	}

	int generated = rand() % ((maxDigit - minDigit) + 1) + minDigit;
	return *new LongNumber(std::to_string(generated));
}

int LongNumber::logpower(int n, int p, int mod)
{
	int result = 1;
	for (; p; p >>= 1)
	{
		if (p & 1)
			result = (1LL * result * n) % mod;
		n = (1LL * n * n) % mod;
	}
	return result;
}
bool LongNumber::rabinmiller(int n)
{
	bool ok = true;

	for (int i = 1; i <= 5 && ok; i++) {
		int a = rand() + 1;
		int result = logpower(a, n - 1, n);
		ok &= (result == 1);
	}

	return ok;
}

LongNumber& LongNumber::operator+=(const LongNumber& other)
{
	*this = *this + other;
	return *this;
}
LongNumber& LongNumber::operator-=(const LongNumber& other)
{
	*this = *this - other;
	return *this;
}

LongNumber operator+(LongNumber b1, const LongNumber& b2)
{
	return b1.Add(b2);
}
LongNumber operator-(LongNumber b1, const LongNumber& b2)
{
	return b1.Sub(b2);
}
LongNumber operator*(LongNumber b1, const LongNumber& b2)
{
	return b1.Mul(b2);
}
LongNumber operator/(LongNumber b1, const LongNumber& b2)
{
	return b1.DivLarge(b2);
}