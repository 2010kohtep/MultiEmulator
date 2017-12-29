/**
* Copyright (C) 2017, 2010kohtep
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

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