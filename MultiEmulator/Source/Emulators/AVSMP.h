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

/* bUniverse param is "y" value in "STEAM_x:y:z" */
int GenerateAVSMP(void* pDest, int nSteamID, bool bUniverse = true)
{
	auto pTicket = (int*)pDest;

	pTicket[0] = 0x14;                               //  +0, header
	pTicket[3] = (nSteamID << 1) | (int)bUniverse;   // +12, SteamId, Low part
	pTicket[4] = 0x01100001;                         // +16, SteamId, High part

	return 28;
}