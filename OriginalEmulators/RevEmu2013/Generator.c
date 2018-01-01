// Very mangy generation code obtained from unpacked steamclient.dll (PECompact)
// All offsets for a1 variable should be less by 8

void __usercall GenerateSteamTicket(int a1@<edi>)
{
  int time; // eax@1
  int v2; // ecx@1
  int v3; // [sp+0h] [bp-Ch]@0

  ZeroTicketData(a1 + 80, a1 + 48, a1 + 112, v3);
  *(a1 + 16) = 'rev';
  *(a1 + 20) = 0;
  *(a1 + 8) = 'S';
  time = _time64(0);
  v2 = *(a1 + 256);
  *(a1 + 32) = time + 90123;
  *(a1 + 35) = ~*(a1 + 35) - *(a1 + 32);
  *(a1 + 240) = 2 * v2; // just don't look at this line
  *(a1 + 24) = 2 * v2;
  *(a1 + 12) = v2;
  *(a1 + 244) = 0x1100001; // and this...
  *(a1 + 28) = 0x1100001;
  *(a1 + 40) = (2 * v2) >> 3;
  *(a1 + 44) = 0;
  *(a1 + 36) = ~_time64(0);
}