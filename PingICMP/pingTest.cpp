#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WS2tcpip.h>
#include <Windows.h>
#include <iphlpapi.h>
#include <IcmpAPI.h>

#include <iostream>

#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib, "Ws2_32.lib")

using namespace std;
bool tryPinging() {
	bool pingStatus = false;
	// Create the ICMP context.
	HANDLE icmp_handle = IcmpCreateFile();
	if (icmp_handle == INVALID_HANDLE_VALUE) {
		throw;
	}

	// Parse the destination IP address.
	IN_ADDR dest_ip{};
	if (1 != InetPtonA(AF_INET, "192.168.0.59", &dest_ip)) {
		throw;
	}

	// Payload to send.
	constexpr WORD payload_size = 1;
	unsigned char payload[payload_size]{ 42 };

	// Reply buffer for exactly 1 echo reply, payload data, and 8 bytes for ICMP error message.
	constexpr DWORD reply_buf_size = sizeof(ICMP_ECHO_REPLY) + payload_size + 8;
	unsigned char reply_buf[reply_buf_size]{};

	// Make the echo request.
	DWORD reply_count = IcmpSendEcho(icmp_handle, dest_ip.S_un.S_addr, payload, payload_size, NULL, reply_buf, reply_buf_size, 10000);

	// Return value of 0 indicates failure, try to get error info.
	if (reply_count == 0) {
		auto e = GetLastError();
		DWORD buf_size = 1000;
		WCHAR buf[1000];
		GetIpErrorString(e, buf, &buf_size);
		cout << "IcmpSendEcho returned error " << e << " (" << buf << ")" << endl;
		//return 255;
		pingStatus = false;
	}
	else {
		pingStatus = true;
	}

	const ICMP_ECHO_REPLY* r = (const ICMP_ECHO_REPLY*)reply_buf;
	struct in_addr addr;
	addr.s_addr = r->Address;
	char* s_ip = inet_ntoa(addr);
	cout << "Reply from: " << s_ip << ": bytes=" << r->DataSize << " time=" << r->RoundTripTime << "ms TTL=" << (int)r->Options.Ttl << endl;

	// Close ICMP context.
	IcmpCloseHandle(icmp_handle);

	return pingStatus;
}

bool isPingable() {
	for (int retry = 1; retry <= 3; retry++) {
		if (tryPinging())
			return true;
	}
	return false;
}

void print_ip(unsigned int ip)
{
	unsigned char bytes[4];
	bytes[0] = ip & 0xFF;
	bytes[1] = (ip >> 8) & 0xFF;
	bytes[2] = (ip >> 16) & 0xFF;
	bytes[3] = (ip >> 24) & 0xFF;
	printf("%d.%d.%d.%d\n", bytes[3], bytes[2], bytes[1], bytes[0]);
}

int main()
{
	/*while (true) {
		if (isPingable())
			cout << ".";
		else
			cout << "\nPING FAIL" << endl;
	}*/

	//print_ip(3232235876);
	unsigned long ip = 3232235876;
	struct in_addr ip_addr;
	ip_addr.s_addr = ip;
	printf("The IP address is %s\n", inet_ntoa(ip_addr));

	return 0;
}