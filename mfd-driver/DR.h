#pragma once
struct drpacket
{
	float Time;
	float TimeofCurrentLap;
	float DistanceDrivenonCurrentLap;
	float DistanceDrivenOverall;
	float PositionX;
	float PositionY;
	float PositionZ;
	float VelocitySpeedMs;
	float VelocityX;
	float VelocityY;
	float VelocityZ;
	float RollVectorX;
	float RollVectorY;
	float RollVectorZ;
	float PitchVectorX;
	float PitchVectorY;
	float PitchVectorZ;
	float PositionOfSuspensionRearLeft;
	float PositionOfSuspensionRearRight;
	float PositionOfSuspensionFrontLeft;
	float PositionOfSuspensionFrontRight;
	float VelocityOfSuspensionRearLeft;
	float VelocityOfSuspensionRearRight;
	float VelocityOfSuspensionFrontLeft;
	float VelocityOfSuspensionFrontRight;
	float VelocityOfWheelRearLeft;
	float VelocityOfWheelRearRight;
	float VelocityOfWheelFrontLeft;
	float VelocityOfWheelFrontRight;
	float PositionThrottle;
	float PositionSteer;
	float PositionBrake;
	float PositionClutch;
	float Gear;//[0 = Neutral, 1 = 1, 2 = 2, ..., 10 = Reverse]
	float GForceLateral;
	float GForceLongitudinal;
	float CurrentLap;
	float SpeedofEngine;//[rpm / 10]
	float Unknown1;
	float Unknown2;
	float Unknown3;
	float Unknown4;
	float Unknown5;
	float Unknown6;
	float Unknown7;
	float Unknown8;
	float Unknown9;
	float Unknown10;
	float Unknown11;
	float Unknown12;
	float Unknown13;
	float TemperatureBrakeRearLeft; //?
	float TemperatureBrakeRearRight; //?
	float TemperatureBrakeFrontLeft; //?
	float TemperatureBrakeFrontRight; //?
	float Unknown14;
	float Unknown15;
	float Unknown16;
	float Unknown17;
	float Unknown18;
	float NumberOfLapsinTotal; //?
	float LengthOfTrackinTotal;
	float Unknown19;
	float MaximumRPM; //[rpm / 10]
};