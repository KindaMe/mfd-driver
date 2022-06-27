#pragma once
#include <cstdint>

struct PacketBase
{
	unsigned int mPacketNumber;         // 0 counter reflecting all the packets that have been sent during the game run
	unsigned int mCategoryPacketNumber; // 4 counter of the packet groups belonging to the given category
	unsigned char mPartialPacketIndex;  // 8 If the data from this class had to be sent in several packets, the index number
	unsigned char mPartialPacketNumber; // 9 If the data from this class had to be sent in several packets, the total number
	unsigned char mPacketType;          // 10 what is the type of this packet (see EUDPStreamerPacketHanlderType for details)
	unsigned char mPacketVersion;       // 11 what is the version of protocol for this handler, to be bumped with data structure change
};                                      // 12 total size

struct sTelemetryData
{
	static const unsigned int sPacketSize = 559;
	PacketBase sBase;                        // 0 12
											 // Participant info
	signed char sViewedParticipantIndex;     // 12 1
											 // Unfiltered input
	unsigned char sUnfilteredThrottle;       // 13 1
	unsigned char sUnfilteredBrake;          // 14 1
	signed char sUnfilteredSteering;         // 15 1
	unsigned char sUnfilteredClutch;         // 16 1
											 // Car state
	unsigned char sCarFlags;                 // 17 1
	signed short sOilTempCelsius;            // 18 2
	unsigned short sOilPressureKPa;          // 20 2
	signed short sWaterTempCelsius;          // 22 2
	unsigned short sWaterPressureKpa;        // 24 2
	unsigned short sFuelPressureKpa;         // 26 2
	unsigned char sFuelCapacity;             // 28 1
	unsigned char sBrake;                    // 29 1
	unsigned char sThrottle;                 // 30 1
	unsigned char sClutch;                   // 31 1
	float sFuelLevel;                        // 32 4
	float sSpeed;                            // 36 4
	unsigned short sRpm;                     // 40 2
	unsigned short sMaxRpm;                  // 42 2
	signed char sSteering;                   // 44 1
	unsigned char sGearNumGears;             // 45 1
	unsigned char sBoostAmount;              // 46 1
	unsigned char sCrashState;               // 47 1
	float sOdometerKM;                       // 48 4
	float sOrientation[3];                   // 52 12
	float sLocalVelocity[3];                 // 64 12
	float sWorldVelocity[3];                 // 76 12
	float sAngularVelocity[3];               // 88 12
	float sLocalAcceleration[3];             // 100 12
	float sWorldAcceleration[3];             // 112 12
	float sExtentsCentre[3];                 // 124 12
	unsigned char sTyreFlags[4];             // 136 4
	unsigned char sTerrain[4];               // 140 4
	float sTyreY[4];                         // 144 16
	float sTyreRPS[4];                       // 160 16
	unsigned char sTyreTemp[4];              // 176 4
	float sTyreHeightAboveGround[4];         // 180 16
	unsigned char sTyreWear[4];              // 196 4
	unsigned char sBrakeDamage[4];           // 200 4
	unsigned char sSuspensionDamage[4];      // 204 4
	signed short sBrakeTempCelsius[4];       // 208 8
	unsigned short sTyreTreadTemp[4];        // 216 8
	unsigned short sTyreLayerTemp[4];        // 224 8
	unsigned short sTyreCarcassTemp[4];      // 232 8
	unsigned short sTyreRimTemp[4];          // 240 8
	unsigned short sTyreInternalAirTemp[4];  // 248 8
	unsigned short sTyreTempLeft[4];         // 256 8
	unsigned short sTyreTempCenter[4];       // 264 8
	unsigned short sTyreTempRight[4];        // 272 8
	float sWheelLocalPositionY[4];           // 280 16
	float sRideHeight[4];                    // 296 16
	float sSuspensionTravel[4];              // 312 16
	float sSuspensionVelocity[4];            // 328 16
	unsigned short sSuspensionRideHeight[4]; // 344 8
	unsigned short sAirPressure[4];          // 352 8
	float sEngineSpeed;                      // 360 4
	float sEngineTorque;                     // 364 4
	unsigned char sWings[2];                 // 368 2
	unsigned char sHandBrake;                // 370 1
											 // Car damage
	unsigned char sAeroDamage;               // 371 1
	unsigned char sEngineDamage;             // 372 1
											 //  HW state
	unsigned int sJoyPad0;                   // 376 4
	unsigned char sDPad;                     // 377 1
	char sTyreCompound[4][40];               // 378 160
	float sTurboBoostPressure;               // 538 4
	float sFullPosition[3];                  // 542 12
	unsigned char sBrakeBias;                // 554 1 -- quantized brake bias
	unsigned int sTickCount;                 // 555
};