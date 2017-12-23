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

int GenerateSetti(void* pDest)
{
	auto pTicket = (int*)pDest;

	pTicket[0] = 0xD4CA7F7B;
	pTicket[1] = 0xC7DB6023;
	pTicket[2] = 0x6D6A2E1F;
	pTicket[5] = 0xB4C43105;

	return 768;
}