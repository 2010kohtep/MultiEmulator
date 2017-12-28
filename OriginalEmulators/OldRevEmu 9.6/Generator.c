int __cdecl SteamGetEncryptedUserIDTicket(void *pEncryptionKeyReceivedFromAppServer, int uEncryptionKeyLength, int pOutputBuffer, int uSizeOfOutputBuffer, void *pReceiveSizeOfEncryptedTicket, TSteamError *pError)
{
  DWORD v6; // eax@7
  int result; // eax@7
  char v8; // [sp+0h] [bp-20h]@0
  DWORD VolumeSerialNumber; // [sp+10h] [bp-10h]@4
  int v10; // [sp+14h] [bp-Ch]@7
  int v11; // [sp+1Ch] [bp-4h]@7

  if ( g_bLogging && g_bLogUserID )
  {
    WriteLog("SteamGetEncryptedUserIDTicket:\n", v8);
    WriteLog("\tKey Address: 0x%08X\n", (char)pEncryptionKeyReceivedFromAppServer);
    WriteLog("\tKey Length: %u\n", uEncryptionKeyLength);
    WriteLog("\tOutput Address: 0x%08X\n", pOutputBuffer);
    WriteLog("\tOutput Size: %u\n", uSizeOfOutputBuffer);
    WriteLog("\tTicket Size: %u\n", *(_DWORD *)pReceiveSizeOfEncryptedTicket);
    WriteLog("\tError Address: %u\n", (char)pError);
  }
  VolumeSerialNumber = 0;
  GetVolumeInformationA(0, 0, 0, &VolumeSerialNumber, 0, 0, 0, 0);
  if ( g_bLogging && g_bLogUserID )
    WriteLog("--\n\tSerial Number: %u\n", VolumeSerialNumber);
  v6 = VolumeSerialNumber;
  LOWORD(v10) = -1;
  *(_DWORD *)pOutputBuffer = v10;
  *(_DWORD *)(pOutputBuffer + 4) = v6;
  *(_WORD *)(pOutputBuffer + 8) = 0;
  result = 0;
  v11 = 0;
  *(_DWORD *)pReceiveSizeOfEncryptedTicket = 10;
  if ( !pError )
    return result;
  pError->eSteamError = 0;
  pError->eDetailedErrorType = 0;
  pError->nDetailedErrorCode = 0;
  pError->szDesc[0] = 0;
  return result;
}