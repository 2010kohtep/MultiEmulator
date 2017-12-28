int __cdecl SteamStartValidatingUserIDTicket(int *pEncryptedUserIDTicketFromClient, unsigned int uSizeOfEncryptedUserIDTicketFromClient, unsigned int ObservedClientIPAddr, int *pReceiveHandle)
{
  unsigned int v4; // esi@4
  int v5; // eax@8
  int v7; // [sp+Ch] [bp-14h]@8
  unsigned int v8; // [sp+10h] [bp-10h]@8
  char v9; // [sp+14h] [bp-Ch]@8

  if ( byte_20042A95 )
    sub_2000B0F0();
  if ( pEncryptedUserIDTicketFromClient[20] == -1 )
    v4 = pEncryptedUserIDTicketFromClient[21];
  else
    v4 = (ObservedClientIPAddr ^ 0x25730981) & 0x7FFFFFFF;
  if ( dword_20043B14 > 100 )
  {
    sub_2000BD90(*(dword_20043B10 + 4));
    *(dword_20043B10 + 4) = dword_20043B10;
    dword_20043B14 = 0;
    *dword_20043B10 = dword_20043B10;
    *(dword_20043B10 + 8) = dword_20043B10;
  }
  v7 = dword_20042234;
  v8 = v4;
  sub_2000BA50(&v7, &v9);
  v5 = dword_20042234;
  *pReceiveHandle = dword_20042234;
  dword_20042234 = v5 + 1;
  return 0;
}