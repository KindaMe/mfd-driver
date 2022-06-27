#include "Network.h"
#include "Ports.h"
#include "Parsers.h"
#include <iostream>
#include <thread>

using namespace std;

int main()
{
	//input
	ServerUDP server_F1;
	thread sthreadF1(&ServerUDP::Init, server_F1, Port_F1);

	ServerUDP server_PC2;
	thread sthreadPC2(&ServerUDP::Init, server_PC2, Port_PC2);

	ServerUDP server_DR;
	thread sthreadDR(&ServerUDP::Init, server_DR, Port_DR);

	ServerAC server_AC;
	thread sthreadAC(&ServerAC::Init, server_AC);

	//output
	ClientUDP client_MFD;
	thread cthread(&ClientUDP::Init, client_MFD);

	string input;
	getline(cin, input);
	while (input != "exit")
	{
		getline(cin, input);
	}

	cthread.detach();

	sthreadF1.detach();
	sthreadPC2.detach();
	sthreadDR.detach();
	sthreadAC.detach();
}