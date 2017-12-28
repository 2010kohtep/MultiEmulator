int __cdecl SteamStartValidatingUserIDTicket(int pEncryptedUserIDTicketFromClient, unsigned int uSizeOfEncryptedUserIDTicketFromClient, unsigned int ObservedClientIPAddr, int *pReceiveHandle)
{
  int v4; // eax@1
  HMODULE v5; // eax@5
  FARPROC v6; // eax@5
  int v7; // ebx@5
  int result; // eax@9
  int v9; // ST1C_4@16
  __int16 v10; // ST24_2@16

  v4 = g_bLogging;
  if ( g_bLogging && g_bLogUserID )
  {
    WriteLog("SteamStartValidatingUserIDTicket (%u, %u)\n", ObservedClientIPAddr, *pReceiveHandle);
    v4 = g_bLogging;
  }
  if ( dword_1003D3C0 )
  {
    v5 = GetModuleHandleA(ModuleName);
    v6 = GetProcAddress(v5, "SteamStartValidatingUserIDTicket");
    v7 = ((int (__cdecl *)(int, unsigned int, unsigned int, int *))v6)(
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
      byte_1003D3EC = 1;
      return 23;
    }
    if ( !v7 )
    {
      byte_1003D3EC = 1;
      if ( !v4 )
        return 0;
      if ( g_bLogUserID )
        WriteLog("\t Client using legitimate STEAM account.\n");
      return 0;
    }
  }
  if ( *(_WORD *)pEncryptedUserIDTicketFromClient == -1 )
  {
    v9 = *(_DWORD *)pEncryptedUserIDTicketFromClient;
    v10 = *(_WORD *)(pEncryptedUserIDTicketFromClient + 8);
    *(_DWORD *)g_ClientSID = *(_DWORD *)(pEncryptedUserIDTicketFromClient + 4);
    dword_1003C158 = 0;
    if ( v4 && g_bLogUserID )
      WriteLog("\t Client using REVOLUTiON emulator.\n");
    byte_1003D3ED = 1;
    byte_1003D3EC = 0;
    result = 0;
  }
  else
  {
    *(_DWORD *)g_ClientSID = ObservedClientIPAddr;
    dword_1003C158 = 1;
    if ( v4 && g_bLogUserID )
      WriteLog("\t Client not using REVOLUTiON emulator.\n");
    byte_1003D3EC = 0;
    if ( byte_1003C154 )
      return 0;
    result = 36;
  }
  return result;
}