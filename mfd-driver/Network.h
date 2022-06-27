#pragma once

#include "Parsers.h"
#include "Ports.h"

#include <iostream>
#include <ws2tcpip.h>
#include <string>
#include <bitset>
#include <chrono>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

class ClientUDP
{
public:
	void Init()
	{
		//start winsock
		WSAData data;
		WORD version = MAKEWORD(2, 2);
		int wsOK = false;

		wsOK = WSAStartup(version, &data);
		if (wsOK != false)
		{
			cout << "Can't init Winsock!" << endl;
			return;
		}

		//create hint struct for the server
		sockaddr_in server;
		server.sin_family = AF_INET;
		server.sin_port = htons(21377);
		inet_pton(AF_INET, "192.168.100.17", &server.sin_addr);

		//create socket
		SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);

		//write out to socket
		while (true)
		{
			char* my_s_bytes = reinterpret_cast<char*>(&_DataToSend);

			int sendOK = sendto(out, my_s_bytes, sizeof(my_s_bytes), 0, (sockaddr*)&server, sizeof(server));

			if (sendOK == SOCKET_ERROR)
			{
				cout << "Couldn't send a packet" << endl;
			}
			Sleep(10);
		}

		//close socket
		closesocket(out);

		//shutdown winsock
		WSACleanup();
	}
};

class ServerUDP
{
public:
	void Init(int Port)
	{
		//start winsock
		WSAData data;
		WORD version = MAKEWORD(2, 2);
		int wsOK = false;

		wsOK = WSAStartup(version, &data);
		if (wsOK != false)
		{
			cout << "Can't init Winsock!" << endl;
			return;
		}

		//create socket and bind to ip and port
		SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);

		sockaddr_in serverHint;
		serverHint.sin_addr.S_un.S_addr = ADDR_ANY;
		serverHint.sin_family = AF_INET;
		serverHint.sin_port = htons(Port);//convert from little to big endian

		if (bind(in, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR)
		{
			cout << "Can't bind socket!" << endl;
			return;
		}

		//client holder
		sockaddr_in client;
		int clientLength = sizeof(client);
		ZeroMemory(&client, clientLength);

		char buf[1500];

		//assign correct parser
		Parser* PtrCurrentParser = NULL;
		switch (Port)
		{
		case Port_F1:
			PtrCurrentParser = new Parser_F1;
			cout << "Listening on F1 Port!\n";
			break;
		case Port_PC2:
			PtrCurrentParser = new Parser_PC2;
			cout << "Listening on PC2 Port!\n";
			break;
		case Port_DR:
			PtrCurrentParser = new Parser_DR;
			cout << "Listening on DR Port!\n";
			break;
		default:
			cout << "Error assigning Parser for port " << Port << "!" << endl;
			closesocket(in);
			WSACleanup();
			return;
		}

		//start loop
		while (true)
		{
			ZeroMemory(buf, 1500);

			//wait for message
			int bytesIn = recvfrom(in, buf, 1500, 0, (sockaddr*)&client, &clientLength);

			if (bytesIn == SOCKET_ERROR)
			{
				cout << "Error recieving from client" << "!" << endl;
				continue;
			}

			PtrCurrentParser->Parse(buf, bytesIn);
		}

		//close socket
		closesocket(in);

		//shutdown winsock
		WSACleanup();
	}
};

class ServerAC
{
private:
	struct handshaker
	{
	public:
		handshaker(int _identifier, int _version, int _operationId)
		{
			identifier = _identifier;
			version = _version;
			operationId = _operationId;
		}

		int identifier;
		int version;
		int operationId;
	};

	Parser* PtrCurrentParser = new Parser_AC;

public:
	void Init()
	{
		WSAData data;
		WORD version = MAKEWORD(2, 2);
		int wsOK = false;

		wsOK = WSAStartup(version, &data);
		if (wsOK != false)
		{
			cout << "Can't init Winsock!" << endl;
			return;
		}

		sockaddr_in server;
		server.sin_family = AF_INET;
		server.sin_port = htons(Port_AC);
		inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

		SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);

		sockaddr_in client;
		int clientLength = sizeof(client);
		ZeroMemory(&client, clientLength);

		char buf[1500];

		handshaker hs_subscribe(1, 1, 1);
		char* hs_sub_message = reinterpret_cast<char*>(&hs_subscribe);
		while (true)
		{
			int pog = -1;
			do
			{
				int sendOK = sendto(out, hs_sub_message, sizeof(handshaker), 0, (sockaddr*)&server, sizeof(server));

				if (sendOK == SOCKET_ERROR)
				{
					cout << "Couldn't send a packet" << endl;
					continue;
				}

				ZeroMemory(buf, 1500);
				pog = recvfrom(out, buf, 1500, 0, (sockaddr*)&client, &clientLength);

				Sleep(1000);
			} while (pog == -1);//temporary workaround cuz socket recieves its own packet i think? somehow its lenght is -1 tho

			cout << "Listening on AC Port!\n";

			fd_set fds;
			while (true)
			{
				FD_ZERO(&fds);
				FD_SET(out, &fds);

				struct timeval tv;
				tv.tv_sec = 1;
				tv.tv_usec = 0;

				int sret = select(0, &fds, NULL, NULL, &tv);

				if (sret <= 0)
				{
					cout << "AC Connection Timed Out!\n";
					break;
				}

				ZeroMemory(buf, 1500);
				int bytesIn = recvfrom(out, buf, 1500, 0, (sockaddr*)&client, &clientLength);

				if (bytesIn == SOCKET_ERROR)
				{
					cout << "Error recieving from client" << "!" << endl;
					continue;
				}

				PtrCurrentParser->Parse(buf, bytesIn);
			}
		}

		closesocket(out);
		WSACleanup();
	}
};
