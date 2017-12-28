int __cdecl SteamGetEncryptedUserIDTicket(int *pEncryptionKeyReceivedFromAppServer, int uEncryptionKeyLength, int *pOutputBuffer, int uSizeOfOutputBuffer, void *pReceiveSizeOfEncryptedTicket, TSteamError *pError)
{
  unsigned int i; // esi@3
  int result; // eax@6
  DWORD VolumeSN; // [sp+8h] [bp-D4h]@5
  DWORD MaxComponentLen; // [sp+Ch] [bp-D0h]@5
  DWORD FSSysFlags; // [sp+10h] [bp-CCh]@5
  CHAR FSNameBuf; // [sp+14h] [bp-C8h]@5
  CHAR VolumeNameBuf; // [sp+78h] [bp-64h]@5

  if ( pError )
  {
    strcpy(pError->szDesc, &sEmptyStr);
    pError->eSteamError = 0;
    pError->eDetailedErrorType = 0;
    pError->nDetailedErrorCode = 0;
  }
  i = 0;
  do
    *(pOutputBuffer + i++) = rand();
  while ( i < 768 );
  *pReceiveSizeOfEncryptedTicket = 768;
  pOutputBuffer[20] = -1;
  if ( GetVolumeInformationA("C:\\", &VolumeNameBuf, 100u, &VolumeSN, &MaxComponentLen, &FSSysFlags, &FSNameBuf, 100u) )
  {
    pOutputBuffer[21] = (VolumeSN ^ 0xC9710266) & 0x7FFFFFFF;
    result = 0;
  }
  else
  {
    pOutputBuffer[21] = 777;
    result = 0;
  }
  return result;
