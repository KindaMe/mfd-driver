#pragma once
#include <cstdint>

#pragma region Packet Response
#pragma pack(push, 1)
struct handshackerResponse
{
	char carName[50];
	char driverName[50];
	int identifier;
	int version;
	char trackName[50];
	char trackConfig[50];
};
#pragma pack(pop)
#pragma endregion
