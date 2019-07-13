#include <stdio.h>
#include<iostream>

#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>

using namespace std;

bool IsPinging(unsigned long ipAddr)
{
	bool pingStatus = false;
	HANDLE hIcmp;
	char SendData[] = "ICMP SEND DATA";
	LPVOID ReplyBuffer;
	DWORD dwRetVal;
	DWORD buflen;
	PICMP_ECHO_REPLY pIcmpEchoReply;

	hIcmp = IcmpCreateFile();

	buflen = sizeof(ICMP_ECHO_REPLY) + strlen(SendData) + 8;
	ReplyBuffer = (VOID*)malloc(buflen);
	if (ReplyBuffer == NULL) {
		return 1;
	}
	memset(ReplyBuffer, 0, buflen);
	pIcmpEchoReply = (PICMP_ECHO_REPLY)ReplyBuffer;

	dwRetVal = IcmpSendEcho(hIcmp, ipAddr, SendData, strlen(SendData), NULL, ReplyBuffer, buflen, 4000);
	if (dwRetVal != 0 && (((ICMP_ECHO_REPLY*)ReplyBuffer)->Status == IP_SUCCESS)) {
		/*printf("Received %ld messages.\n", dwRetVal);
		printf("\n");
		printf("RTT: %d\n", pIcmpEchoReply->RoundTripTime);
		printf("Data Size: %d\n", pIcmpEchoReply->DataSize);
		printf("Message: %s\n", pIcmpEchoReply->Data);*/
		pingStatus = true;
	}
	else {
		printf("Call to IcmpSendEcho() failed.\n");
		printf("Error: %ld\n", GetLastError());
	}

	IcmpCloseHandle(hIcmp);

	return pingStatus;
}

bool IsPingable(unsigned long ipAddr) {
	for (int i = 1; i <= 3; i++) {
		if (IsPinging(ipAddr))
			return true;
	}

	return false;
}

int main()
{
	while (true) {
		//if (IsPingable(3232235527))//117483712
		//if (IsPingable(117483712))// 192.16
		//if (IsPingable(_byteswap_ulong(989898944)))// 192.168.0.59
		if (IsPingable(_byteswap_ulong(3232235527)))// 192.168.0.7 //change the byteoreder
			cout << ".";
		else
			cout << "\n NOT PINGABLE \n";
	}

	return 0;
}