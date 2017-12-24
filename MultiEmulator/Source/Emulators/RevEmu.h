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

#pragma once

#include "..\Shared\StrUtils.h"
#include "..\Shared\RevSpoofer.h"
#include <Windows.h>

int GenerateRevEmu(void* pDest, int nSteamID)
{
	char hwid[64];

	CreateRandomString(hwid, 16);
	if (!RevSpoofer::Spoof(hwid, nSteamID))
		return 0;

	auto pTicket = (int*)pDest;
	auto revHash = RevSpoofer::Hash(hwid);

	pTicket[0] = 'J';
	pTicket[1] = revHash;
	pTicket[2] = 'rev';
	pTicket[3] = 0;
	pTicket[4] = revHash << 1;
	pTicket[5] = 0x01001001;

	strcpy((char*)&pTicket[6], hwid);

	return 160;
}