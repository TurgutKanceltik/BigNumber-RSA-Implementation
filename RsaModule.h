#pragma once
#include "LongNumber.h"
class RsaModule
{
public:
	LongNumber Keygen(LongNumber* p, LongNumber* q, LongNumber* e, int lenght);
	LongNumber RsaEncrypt(LongNumber e, LongNumber n);
	LongNumber RsaDecrypt(LongNumber d, LongNumber n);

	void testRsa();
};
