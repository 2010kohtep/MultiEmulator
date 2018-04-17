
#include <Public\StrUtils.h>
#include <Windows.h>

void CreateRandomString(char* pszDest, int nLength)
{
	static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	for (int i = 0; i < nLength; ++i)
		pszDest[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

	pszDest[nLength] = '\0';
}