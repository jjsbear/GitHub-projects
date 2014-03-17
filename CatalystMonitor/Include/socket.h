#pragma once

//#define SOCKETSPEEDTEST
#define BUFFERLENGTH    4200 //3072 // transfer buffer length, it should be bigger than sizeof(SocketDataSend)

enum DataType {test=0x100, speedTest=0x110, ClientSetting=0x300, ServerReceived=0x301};

typedef struct strFeatureChange
{
    char szFeature[32];
    int bChanged;
};

typedef struct SocketFeatureData
{
	DataType	type;
	char		szHostName[256];
	strFeatureChange featureChanges[100];
	bool		bSucceed;
} SocketFeatureData, *LPSocketFeatureData;

typedef struct SocketTestData
{
	DataType	type;
	byte		buffer[196];
	bool		bSucceed;
} SocketTestData, *LPSocketTestData;

typedef struct SocketSpeedData
{
	DataType	type;
	byte		buffer[196];
} SocketSpeedData, *LPSocketSpeedData;