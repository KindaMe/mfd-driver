#pragma once
#include "F1.h"
#include "PC2.h"
#include "DR.h"
#include "AC.h"

using namespace std;

struct DataToSend
{
	uint16_t Speed = 0;
	int8_t Gear = 0;
	uint16_t RevLights = 0;
}_DataToSend;

class Parser
{
public:
	virtual void Parse(char(&buf)[1500], int BytesIn) = 0;
};

class Parser_F1 : public Parser
{
public:
	virtual void Parse(char(&buf)[1500], int BytesIn) override
	{
		if (BytesIn == 1347)
		{
			PacketCarTelemetryData const* data;

			data = reinterpret_cast<PacketCarTelemetryData const*>(buf);

			int PlayerCarIndex = data->m_header.m_playerCarIndex;

			_DataToSend.Speed = data->m_carTelemetryData[PlayerCarIndex].m_speed;
			_DataToSend.Gear = data->m_carTelemetryData[PlayerCarIndex].m_gear;
			_DataToSend.RevLights = data->m_carTelemetryData[PlayerCarIndex].m_revLightsBitValue;
		}
	}
};

class Parser_PC2 : public Parser
{
public:
	virtual void Parse(char(&buf)[1500], int BytesIn) override
	{
		if (BytesIn == 559)
		{
			sTelemetryData const* data;

			data = reinterpret_cast<sTelemetryData const*>(buf);

			_DataToSend.Speed = data->sSpeed * 3.6;
			_DataToSend.Gear = data->sGearNumGears;
		}
	}
};

class Parser_DR : public Parser
{
public:
	virtual void Parse(char(&buf)[1500], int BytesIn) override
	{
		if (BytesIn == 264)
		{
			drpacket const* data;

			data = reinterpret_cast<drpacket const*>(buf);

			_DataToSend.Speed = data->VelocitySpeedMs * 3.6;
			_DataToSend.Gear = data->Gear;
		}
	}
};

class Parser_AC : public Parser
{
public:
	float mrpm = 0;

	virtual void Parse(char(&buf)[1500], int BytesIn) override
	{
		RTCarInfo const* data;

		data = reinterpret_cast<RTCarInfo const*>(buf);

		_DataToSend.Speed = data->speed_Kmh;
		_DataToSend.Gear = data->gear - 1;

		float rpm = data->engineRPM;

		if (mrpm < data->engineRPM)
			mrpm = data->engineRPM;

		float revpercent = (rpm / mrpm) * (float)100;

		int counter = 0;

		while (counter < 15)
		{
			if (revpercent - 50 > counter * 3.33)
			{
				_DataToSend.RevLights &= ~(1u << counter);
				_DataToSend.RevLights |= (1u << counter);
			}
			else
			{
				_DataToSend.RevLights &= ~(1u << counter);
				_DataToSend.RevLights |= (0u << counter);
			}

			counter++;
		}
	}
};
