#include "Utils.h"

bool String::EndsWith(char* str, char* prefix)
{
	if(strlen(str) < strlen(prefix)) 
	{
		return false;
	}

	char* pptr = str + strlen(str) - 1;
	char* pprefix = prefix + strlen(prefix) - 1;
	while(pprefix >= prefix && *pprefix == *pptr)
	{
		pprefix--;
		pptr--;
	}
	if(pprefix < prefix) 
	{
		return true;
	} else 
	{
		return false;
	}
}