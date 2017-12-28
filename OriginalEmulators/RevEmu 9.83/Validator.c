struct TRevEmuTicket
{
	int header;
	int hash;
	int magic;
	int magic2;
	int steamid;
	int steamid2;
	char hwid[128];
};

int __cdecl SteamStartValidatingUserIDTicket(int *pEncryptedUserIDTicketFromClient, unsigned int uSizeOfEncryptedUserIDTicketFromClient, unsigned int ObservedClientIPAddr, int *pReceiveHandle)
{
  int v4; // eax@1
  HMODULE v5; // eax@5
  FARPROC F; // eax@5
  int v7; // edi@5
  bool v9; // al@22
  TRevEmuTicket Ticket; // [sp+10h] [bp-A0h]@16

  v4 = g_bLogging;
  if ( g_bLogging && g_bLogUserID )
  {
    WriteLog("SteamStartValidatingUserIDTicket (%u, %u)\n", ObservedClientIPAddr, *pReceiveHandle);
    v4 = g_bLogging;
  }
  if ( dword_10058C9C )
  {
    v5 = GetModuleHandleA(ModuleName);
    F = GetProcAddress(v5, "SteamStartValidatingUserIDTicket");
    v7 = (F)(
           pEncryptedUserIDTicketFromClient,
           uSizeOfEncryptedUserIDTicketFromClient,
           ObservedClientIPAddr,
           pReceiveHandle);
    v4 = g_bLogging;
    if ( g_bLogging && g_bLogUserID )
    {
      WriteLog("\t %u\n", v7);
      v4 = g_bLogging;
    }
    if ( v7 == 23 )
    {
      byte_10058CC5 = 1;
      return 23;
    }
    if ( !v7 )
    {
      byte_10058CC5 = 1;
      if ( !v4 || !g_bLogUserID )
        return 0;
      WriteLog("\t Client using legitimate STEAM account.\n");
      return 0;
    }
  }
  if ( uSizeOfEncryptedUserIDTicketFromClient == 1 )
    return 36;
  qmemcpy(&Ticket, pEncryptedUserIDTicketFromClient, sizeof(Ticket));
  if ( Ticket.magic != 'rev' || Ticket.magic2 )
  {
    *g_ClientSID = ObservedClientIPAddr;
    dword_10048180 = 1;
    if ( v4 && g_bLogUserID )
      WriteLog("\t Client not using REVOLUTiON emulator.\n");
    byte_10058CC5 = 0;
    if ( byte_1004817C )
      return 0;
    return 36;
  }
  *g_ClientSID = Ticket.steamid;
  dword_10048180 = 0;
  byte_10058CC6 = 1;
  byte_10058CC5 = 0;
  if ( Ticket.header >= 'S' )
  {
    if ( v4 && g_bLogUserID )
      WriteLog("\t Client using REVOLUTiON emulator.\n");
    v9 = sub_100128C0(&Ticket, 0);
  }
  else
  {
    if ( v4 && g_bLogUserID )
      WriteLog("\t Client using REVOLUTiON emulator prior to v9.83.\n");
    v9 = sub_100128C0(&Ticket, 1);
  }
  byte_10058CC7 = v9;
  return 0;
}