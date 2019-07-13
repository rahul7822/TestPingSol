#include "Icmp.h"
#include <ipexport.h>

Icmp::Icmp()
{
	ReplyBuffer = NULL;
	ReplySize = 0;
}


Icmp::~Icmp()
{
	if (ReplyBuffer != NULL)
	{
		free(ReplyBuffer);
	}
	IcmpCloseHandle(hIcmpFile);
}

bool Icmp::PingOnce(unsigned long addr)
{
	char SendData[32] = "Data Buffer";
	bool isPingable = false;
	hIcmpFile = IcmpCreateFile();
	ReplySize = (sizeof(ICMP_ECHO_REPLY) + sizeof(SendData));
	ReplyBuffer = (VOID*)malloc(ReplySize);
	if (hIcmpFile != INVALID_HANDLE_VALUE && ReplyBuffer!=NULL)
	{
		//for (int i = 0; i < ICMP_RETRIES; ++i)
		dwRetVal = IcmpSendEcho(hIcmpFile, addr, SendData, sizeof(SendData), NULL, ReplyBuffer, ReplySize, DEFAULT_ECHO_TIMEOUT);
		if ((dwRetVal == 0) && (((ICMP_ECHO_REPLY*)ReplyBuffer)->Status != IP_SUCCESS))
		{
			cout << dwRetVal << "|" << ((ICMP_ECHO_REPLY*)ReplyBuffer)->Status << endl;
		}

		if ((dwRetVal != 0))// && (((ICMP_ECHO_REPLY*)ReplyBuffer)->Status == IP_SUCCESS))
		{
			isPingable = true;
		}
	}

	return isPingable;
}
