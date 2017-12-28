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

int GenerateOldRevEmu(void* pDest, int nSteamID)
{
	auto pTicket = (int*)pDest;
	auto pbTicket = (unsigned char*)pDest;

	pTicket[0] = 0xFFFF;                       // +0, header
	pTicket[1] = (nSteamID ^ 0xC9710266) << 1; // +4, SteamId
	*(short *)pbTicket[8] = 0;                 // +8, unknown, in original emulator must be 0

	return 10;
}