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

#include "..\Public\StrUtils.h"
#include "..\Public\RevSpoofer.h"
#include <Windows.h>

int GenerateRevEmu(void* pDest, int nSteamID)
{
	char hwid[64];

	CreateRandomString(hwid, 16);
	if (!RevSpoofer::Spoof(hwid, nSteamID))
		return 0;

	auto pTicket = (int*)pDest;
	auto revHash = RevSpoofer::Hash(hwid);

	pTicket[0] = 'J';           //  +0, header
	pTicket[1] = revHash;       //  +4, hash of string at +24 offset
	pTicket[2] = 'rev';         //  +8, magic number
	pTicket[3] = 0;             // +12, unknown number, must always be 0

	pTicket[4] = revHash << 1;  // +16, SteamId, Low part
	pTicket[5] = 0x01100001;    // +20, SteamId, High part

	strcpy((char*)&pTicket[6], hwid); // +24, string for hash

	return 152;
}