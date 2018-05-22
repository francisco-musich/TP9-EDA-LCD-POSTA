#pragma once

#include <cstdint>
#include <cstdio>
#include <iostream>
#include <chrono>
#include <windows.h>
#include <thread>
#include <stdlib.h>
#include "General.h"
#define FTD2XX_EXPORTS
#include "ftd2xx.h"

class HitachiLow
{
public:
	HitachiLow();
	~HitachiLow();

protected:
	bool sendData(BYTE data, bool rs);
	void writeNybble(BYTE data);
	FT_STATUS status = !FT_OK;

private:
	void init();
	void sendDataInit(BYTE data, bool rs);
	FT_HANDLE lcdHandle;
	unsigned char info = 0x00;
	DWORD sizeSent = 0;
};

