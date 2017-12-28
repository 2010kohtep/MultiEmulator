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

int __cdecl SteamGetEncryptedUserIDTicket(void *pEncryptionKeyReceivedFromAppServer, int uEncryptionKeyLength, int *pOutputBuffer, int uSizeOfOutputBuffer, void *pReceiveSizeOfEncryptedTicket, TSteamError *pError)
{
  int result; // eax@5

  if ( g_bLogging && g_bLogUserID )
    WriteLog("SteamGetEncryptedUserIDTicket\n");
  if ( byte_10058C75 )
  {
    *pOutputBuffer = -1;
    *pReceiveSizeOfEncryptedTicket = 1;
    result = 0;
  }
  else
  {
    g_EmuTicket.hash = g_revHashValue;
    g_EmuTicket.steamid = 2 * g_revHashValue;
    g_EmuTicket.steamid2 = 0x1100001;
    g_EmuTicket.header = 'S';
    g_EmuTicket.magic = 'rev';
    g_EmuTicket.magic2 = 0;
    qmemcpy(pOutputBuffer, &g_EmuTicket, 152u);
    *pReceiveSizeOfEncryptedTicket = 152;
    if ( pError )
    {
      pError->eSteamError = 0;
      pError->eDetailedErrorType = 0;
      pError->nDetailedErrorCode = 0;
      pError->szDesc[0] = 0;
    }
    result = 0;
  }
  return result;
}