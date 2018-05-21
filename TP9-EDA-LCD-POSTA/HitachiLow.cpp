#include "HitachiLow.h"



HitachiLow::HitachiLow()
{
	std::chrono::seconds MaxTime(CONNECTING_TIME);/*The display has a settling time after the physical connection so the attempt to connect
												  will be done for a few seconds*/
	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> current = start;

	while (status != FT_OK && ((current - start) < MaxTime))//loop till succesful connection o max connecting time is exceeded
	{
		status = FT_OpenEx((void *)MY_LCD_DESCRIPTION, FT_OPEN_BY_DESCRIPTION, &lcdHandle);
		if (status == FT_OK)
		{
			UCHAR Mask = 0xFF;	//Selects all FTDI pins.
			UCHAR Mode = 1; 	// Set asynchronous bit-bang mode
			if (FT_SetBitMode(lcdHandle, Mask, Mode) == FT_OK)	// Sets LCD as asynch bit mode. Otherwise it doesn't work.
			{
				init(); //sets mode and clear all
			}
			else
				printf("Couldn't configure LCD\n");
		}
		current = std::chrono::system_clock::now();
	}
	if (status != FT_OK)
		printf("Couldn't open LCD\n");
}


HitachiLow::~HitachiLow()
{
	FT_Close(lcdHandle);
}


//Aca van las protected

void HitachiLow::init()
{
	sendDataInit(LCD_FUNCTION8, IR);
	std::this_thread::sleep_for(std::chrono::milliseconds(4));
	sendDataInit(LCD_FUNCTION8, IR);
	std::this_thread::sleep_for(std::chrono::microseconds(100));
	sendDataInit(LCD_FUNCTION8, IR);
	sendDataInit(LCD_FUNCTION4, IR);
	sendData(LCD_FUNCTION4, IR);
	sendData(LCD_DISPLAY_AOFF, IR);
	sendData(LCD_CLEAR, IR);
	sendData(LCD_ENTRY, IR);
}

void HitachiLow::sendDataInit(BYTE data, bool _rs)
{
	BYTE rs = (_rs) ? LCD_RS_DR : LCD_RS_IR;
	BYTE temp = data & 0xF0;
	temp = temp | rs;
	writeNybble(temp);
}

void HitachiLow::sendData(BYTE data, bool _rs)
{
	BYTE rs = (_rs) ? LCD_RS_DR : LCD_RS_IR;
	BYTE temp = data & 0xF0;
	temp = temp | rs;
	writeNybble(temp);
	temp = ((data & 0x0F) << 4) & 0xF0;
	temp = temp | rs;
	writeNybble(temp);
}

void HitachiLow::writeNybble(BYTE data)
{
	DWORD bytesSent = 0;
	BYTE temp = 0x00;
	//Bajar enable
	temp = data & NOT_LCD_E;
	if (FT_Write(lcdHandle, &temp, sizeof(temp), &bytesSent) == FT_OK)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(500));
		//Subir en enable
		temp = data | LCD_E;
		if (FT_Write(lcdHandle, &temp, sizeof(temp), &bytesSent) == FT_OK)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(3));
			//Bajar enable
			temp = data & NOT_LCD_E;
			if (FT_Write(lcdHandle, &temp, sizeof(temp), &bytesSent) == FT_OK)
			{
			}
			else
				status = !FT_OK;
		}
		else
			status = !FT_OK;
	}
	else
		status = !FT_OK;
}