#include "Global.h"

unsigned g_FileNameHash(const char* pString)
{
	unsigned int Id = 0;
	char c = 0;
	for (int i = 0; pString[i]; i++)
	{
		c = pString[i];
		if (c >= 'A' && c <= 'Z')
			c += 0x20;
		else if (c == '/')
			c = '\\';
		Id = (Id + (i + 1) * c) % 0x8000000b * 0xffffffef;
	}
	return (Id ^ 0x12345678);
}

char* g_StrReplace(char* src, char cs, char cd)
{
	char* p = src;
	while (*p++)
	{
		if (*p == cs)
			*p = cd;
	}
	return src;
}