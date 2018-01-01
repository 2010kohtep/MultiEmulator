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
#include "..\Public\Encryption\CRijndael.h"
#include "..\Public\Encryption\SHA.h"
#include <Windows.h>
#include <time.h>

int GenerateRevEmu2013(void* pDest, int nSteamID)
{
	char hwid[64];

	CreateRandomString(hwid, 32);
	if (!RevSpoofer::Spoof(hwid, nSteamID))
		return 0;

	auto pTicket = (int*)pDest;
	auto pbTicket = (unsigned char*)pDest;

	auto revHash = RevSpoofer::Hash(hwid);

	pTicket[0] = 'S';                      // +0
	pTicket[1] = revHash;                  // +4
	pTicket[2] = 'rev';                    // +8
	pTicket[3] = 0;                        // +12
	pTicket[4] = revHash << 1;             // +16
	pTicket[5] = 0x01100001;               // +20
	pTicket[6] = (int)_time64(0) + 90123;  // +24
	pbTicket[27] = ~(pbTicket[27] + pbTicket[24]);
	pTicket[7] = ~(int)_time64(0);         // +28
	pTicket[8] = revHash * 2 >> 3;         // +32

	static const char AESKeyRand[] = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
	char AESHashRand[32];
	auto AESRand = CRijndael();
	AESRand.MakeKey(AESKeyRand, CRijndael::sm_chain0, 32, 32);
	AESRand.EncryptBlock(hwid, AESHashRand);
	memcpy(&pbTicket[40], AESHashRand, 32);

	static const char AESKeyRev[] = "_YOU_SERIOUSLY_NEED_TO_GET_LAID_";
	char AESHashRev[32];
	auto AESRev = CRijndael();
	AESRev.MakeKey(AESKeyRev, CRijndael::sm_chain0, 32, 32);
	AESRev.EncryptBlock(AESKeyRand, AESHashRev);
	memcpy(&pbTicket[72], AESHashRev, 32);

	char SHAHash[32];
	auto sha = CSHA(CSHA::SHA256);
	sha.AddData(hwid, 32);
	sha.FinalDigest(SHAHash);
	memcpy(&pbTicket[104], SHAHash, 32);

	return 194;
}