#include "HTTP.h"
#include <WinSock.h>

const char* g_pszHosts[] = 
{
	"http://myexternalip.com/raw",
	"http://api.ipify.org",
	"http://ipinfo.io/ip"
};

/*
* Extracts external IP of the current machine via internet
* resources.
*
* @output       IPv4 address as string.
*/
char* GetExternalIPString()
{
	int iResSize = 0;
	int iRetCode = 0;
	void* pData = nullptr;

	for (int i = 0; i < _countof(g_pszHosts); i++)
	{
		pData = HTTPGetRequest(g_pszHosts[i], &iResSize, &iRetCode);

		if (pData && iResSize && iRetCode == 200)
			break;
	}

	if (!pData || !iResSize || iRetCode != 200)
		return nullptr;

	static char sIP[256];
	strcpy(sIP, (char*)pData);

	auto psz = sIP;
	char c;
	while (c = *psz, c != '\0')
	{
		if (c == '\n')
		{
			*psz = '\0';
			break;
		}

		psz++;
	}
	free(pData);

	return sIP;
}

/*
* Extracts external IP of the current machine via internet
* resources.
*
* @output       IPv4 address as integer.
*/
long GetExternalIPLong()
{
	auto pszIP = GetExternalIPString();
	return inet_addr(pszIP);
}