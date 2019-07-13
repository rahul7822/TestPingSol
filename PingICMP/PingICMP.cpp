// PingICMP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include "Icmp.h"
//#include <winsock2.h>
//#include <iphlpapi.h>
//#include <icmpapi.h>

//#pragma comment(lib, "iphlpapi.lib")
//#pragma comment(lib, "Ws2_32.lib")

//bool IsPingable(unsigned long addr)
//{
//	HANDLE hIcmpFile;
//	DWORD dwRetVal = 0;
//	char SendData[32] = "Data Buffer";
//	LPVOID ReplyBuffer = NULL;
//	DWORD ReplySize = 0;
//
//	bool bping = false;
//
//	hIcmpFile = IcmpCreateFile();
//	if (hIcmpFile != INVALID_HANDLE_VALUE) {
//
//		ReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(SendData)*10;
//		ReplyBuffer = (VOID*)malloc(ReplySize);
//
//		if (ReplyBuffer != NULL) {
//			dwRetVal = IcmpSendEcho(hIcmpFile, addr, SendData, sizeof(SendData), NULL, ReplyBuffer, ReplySize, 5000);
//			if (dwRetVal > 0) {
//				bping = true;
//			}
//			else {
//				cout << ((ICMP_ECHO_REPLY*)ReplyBuffer)->Status << endl;
//			}
//		}
//	}
//	return bping;
//}

//bool bPing = false;
//HANDLE hIcmpFile;
//DWORD dwRetVal = 0;
//char SendData[32] = "Data Buffer";
//LPVOID ReplyBuffer = NULL;
//DWORD ReplySize = 0;
//unsigned long ipaddr = INADDR_NONE;
//long lastErrorCode = 0;

//bool IsPingable(unsigned long addr)
//{
//	DWORD dwRetVal = 0;
//	bool isPingable = false;
//	long lastErrorCode = 0;
//	wstring logMsg;
//	if (hIcmpFile != INVALID_HANDLE_VALUE)
//	{
//		for (int i = 0; i <= ICMP_RETRIES; ++i)
//		{
//			dwRetVal = IcmpSendEcho(hIcmpFile, addr, SendData, sizeof(SendData), NULL, ReplyBuffer, ReplySize, DEFAULT_ECHO_TIMEOUT);
//			if ((dwRetVal == 0) && (((ICMP_ECHO_REPLY*)ReplyBuffer)->Status != IP_SUCCESS))
//			{
//				cout << dwRetVal << "|" << ((ICMP_ECHO_REPLY*)ReplyBuffer)->Status << endl;
//				if (dwRetVal != IP_REQ_TIMED_OUT)
//					break;
//				Sleep(1 * 1000);
//			}
//
//			if ((dwRetVal != 0))// && (((ICMP_ECHO_REPLY*)ReplyBuffer)->Status == IP_SUCCESS))
//			{
//				isPingable = true;
//				break;
//			}
//
//		}
//	}
//
//	return isPingable;
//}

bool TryPinging(unsigned long addr)
{
	bool isPingable = false;
	for (int i = 0; i <= ICMP_RETRIES; ++i)
	{
		Icmp* ping = new Icmp;
		if (ping->PingOnce(addr))
			isPingable = true;

		delete ping;

		if (isPingable == true) {
			break;
		}

		Sleep(1000);
	}

	return  isPingable;
}

int main()
{
	//hIcmpFile = IcmpCreateFile();
	//ReplySize = (sizeof(ICMP_ECHO_REPLY) + sizeof(SendData)) * 20;
	//ReplyBuffer = (VOID*)malloc(ReplySize);
	//while (1)
	//{
	//	if (IsPingable(2130706433)) //localhost 127.0.0.1 
	//	//if (IsPingable(3232235527)) // dell 
	//		cout << ".";
	//	else
	//		cout << "*";
	//}


	while (true)
	{
		//if (testPing(3232235876)) // espec
		//if (testPing(3232235948)) // rgs
		//if (testPing(long_address))
		//if (TryPinging(3232235835)) //lala
		//if (TryPinging(2130706433))//localhost
		if (TryPinging(3232235527))
			cout << ".";
		else
			cout << "*";
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
