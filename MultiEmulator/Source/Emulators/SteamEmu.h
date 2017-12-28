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

int GenerateSteamEmu(void* pDest, int nSteamID)
{
	auto pTicket = (int*)pDest;

	pTicket[20] = -1;        // +80, dproto/reunion wants this value to be -1, but if this value
	                         //      does not match -1, then instead of SteamID in [21] cell
	                         //      client IP address that xored with 0x25730981 number should 
	                         //      be used. But dproto/reunion will just skip ticket validation
	                         //      in that case.

	pTicket[21] = nSteamID;  // +84, SteamId, low part. Actually, this is just system volume serial
	                         //      number, which comes from GetVolumeInformationA() function. If
	                         //      function failed (returned 0), then instead of volume serial number
	                         //      777 number will be written to the ticket.

	return 768;
}