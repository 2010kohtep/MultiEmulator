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

#include <Windows.h>
#include "RevSpoofer.h"

#define astrlen(x) _countof(x) - 1

static char Dictionary[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" };

static int iInputLen;
static unsigned int uTreasure;

bool ScanLast3(char* pszInput, unsigned int uPrevHash)
{
	unsigned int h1, h2, h3, hh;
	for (int i1 = 0; i1 < astrlen(Dictionary); i1++)
	{
		h1 = uPrevHash ^ ((uPrevHash >> 2) + (uPrevHash << 5) + Dictionary[i1]);
		hh = h1 ^ ((h1 >> 2) + (h1 << 5));
		hh = hh ^ ((hh >> 2) + (hh << 5));

		if ((hh ^ uTreasure) >> (8 + 5 + 3))
			continue;

		for (int i2 = 0; i2 < astrlen(Dictionary); i2++)
		{
			h2 = h1 ^ ((h1 >> 2) + (h1 << 5) + Dictionary[i2]);
			hh = h2 ^ ((h2 >> 2) + (h2 << 5));
			if ((hh ^ uTreasure) >> (8 + 3))
				continue;

			for (int i3 = 0; i3 < astrlen(Dictionary); i3++)
			{
				h3 = h2 ^ ((h2 >> 2) + (h2 << 5) + Dictionary[i3]);
				if (h3 == uTreasure)
				{
					pszInput[iInputLen - 3] = Dictionary[i1];
					pszInput[iInputLen - 2] = Dictionary[i2];
					pszInput[iInputLen - 1] = Dictionary[i3];
					return true;
				}
			}
		}
	}
	return false;
}

bool ScanNext(char* pszInput, int uIndex, unsigned int uPrevHash)
{
	bool res;

	for (int i = 0; i < astrlen(Dictionary); i++)
	{
		auto h = uPrevHash ^ ((uPrevHash >> 2) + (uPrevHash << 5) + Dictionary[i]);

		if (uIndex + 1 < iInputLen - 3)
			res = ScanNext(pszInput, uIndex + 1, h);
		else
			res = ScanLast3(pszInput, h);

		if (res)
		{
			pszInput[uIndex] = Dictionary[i];
			return true;
		}
	}
	return false;
}

namespace RevSpoofer
{
	bool Spoof(char* pszDest, int uSID)
	{
		uTreasure = uSID;
		iInputLen = strlen(pszDest);

		auto i = iInputLen - 7;
		i = (i < 0) ? 0 : i;
		pszDest[i] = '\0';
		auto h = Hash(pszDest);
		return ScanNext(pszDest, i, h);
	}

	unsigned int Hash(char* pszString)
	{
		int i = 0;
		unsigned int hash = 0x4E67C6A7;
		int c = pszString[i++];

		while (c)
		{
			hash = hash ^ ((hash >> 2) + (hash << 5) + c);
			c = pszString[i++];
		}

		return hash;
	}
}