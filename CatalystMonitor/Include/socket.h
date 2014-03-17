#pragma once

//#define SOCKETSPEEDTEST
#define BUFFERLENGTH    4000 //3072 // transmission buffer length, it should be bigger than sizeof(SocketDataSend)

enum DataType {test=0x100, speedTest=0x110, ClientAskFor=0x200, ServerAdvice=0x201, ServerNotAdvice=0x202, ClientSetting=0x300, ServerReceive=0x301};
enum SettingRate {normal = 1, good=2, perfer=3};

typedef struct strFeatureChange
{
    char szFeature[32];
    int bChanged;
};

typedef struct SocketDataSend
{
	DataType	type;
	char		szHostName[256];
	strFeatureChange featureChanges[100];
	bool		bSucceed;
} SocketDataSend, *LPSocketDataSend;

typedef struct SocketSpeedData
{
	DataType	type;
	byte		buffer[196];
} SocketSpeedData, *LPSocketSpeedData;