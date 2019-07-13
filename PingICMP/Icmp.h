#pragma once
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

#include <iostream>

#include <Windows.h>
#include <iphlpapi.h>
#include <icmpapi.h>

#define ICMP_RETRIES				2
#define DEFAULT_ECHO_TIMEOUT   5 * 1000

using namespace std;

class Icmp
{
public:
	Icmp();
	~Icmp();
	bool PingOnce(unsigned long addr);
private:
	HANDLE hIcmpFile;
	DWORD dwRetVal;
	LPVOID ReplyBuffer;
	DWORD ReplySize;
};

