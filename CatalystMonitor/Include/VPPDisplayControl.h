#pragma once

//#define SOCKETSPEEDTEST
#define BUFFERLENGTH    3072 // transmission buffer length, it should be bigger than sizeof(SocketDataSend)

enum DataType {test=0x100, speedTest=0x110, ClientAskFor=0x200, ServerAdvice=0x201, ServerNotAdvice=0x202, ClientSetting=0x300, ServerReceive=0x301};
enum SettingRate {normal = 1, good=2, perfer=3};

typedef struct DisplaySetting
{
	int			nXResolution;
	int			nYResolution;
	int			nColourDepth;
	float		fRefreshRate;
    int         nBrightness;
    int         nContrast;
    int         nSaturation;
    int         nHue;
    int         nTemperature;
    WORD        wGamma[3][256];
	SettingRate rate;
} DisplaySetting, *LPDisplaySetting;

typedef struct SocketDataSend
{
	DataType	type;
	char		szDisplay[256];
	char		szAdapter[256];
	char		szDrvVersion[256];
	char		szHostName[256];
	DisplaySetting  displaySetting;
	bool		bSucceed;
} SocketDataSend, *LPSocketDataSend;

typedef struct SocketSpeedData
{
	DataType	type;
	byte		buffer[196];
} SocketSpeedData, *LPSocketSpeedData;