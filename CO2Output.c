/*
 * CO2_Output.c
 *
 * Created: 03.02.2021 14:28:42
 *  Author: Niklas Theis
 */

#include "CO2Output.h"

void SendLinesToLCD();

void CO2Output_Init(SensorData_t* sensorData, volatile uint8_t* Port, LCD_CursorSetting_t cursor, CO2Output_AlignValueRight_t align)
{
	LCD_Init(Port, cursor);
	SensorData = sensorData;
	CurrentLine = 0;
	AlignSetting = align;
	//LCD_UpdateData((char*) &OutputData, MAX_CHAR_COUNT, 6);
	//SendLinesToLCD();
	CO2Output_UpdateData();
	CO2Output_UpdateLEDs();
}

void CO2Output_UpdateData()
{
	char tmp[20];
	ConvertFloatToCharArray(tmp, SensorData->co2_value_u16);
	sprintf(OutputData.co2Value, "CO2: %s ppm", tmp);
	sprintf(OutputData.humidityValue, "Humidity: %d%%", SensorData->humidity_value_u16);
	sprintf(OutputData.temperatureValue, "Temp: %dßC", SensorData->temperature_value_u16); //ß wegen ROM Code A00
	sprintf(OutputData.firmwareVersion, "Firmware: %d", SensorData->firmware_version_u16);
	if (SensorData->MeasState_en == 1) sprintf(OutputData.measState, "MeasState: On");
	else sprintf(OutputData.measState, "MeasState: Off");
	if (SensorData->AutocalibMode_en == 1) sprintf(OutputData.autocalibMode, "MeasState: On");
	else sprintf(OutputData.autocalibMode, "AutoCalib: Off");
	//LineList = (char*) &OutputData;
	LCD_UpdateData((char*) &OutputData, MAX_CHAR_COUNT, 6);
	//SendLinesToLCD();
	return;
}

void CO2Output_MoveUp()
{
	LCD_MoveUp();
}

void CO2Output_MoveDown()
{
	LCD_MoveDown();
}

void CO2Output_UpdateLEDs()
{
	PORTD &= 0b10001111;
	if (SensorData->co2_value_u16 < 350)
	{
		PORTD |= 0b01000000;
	}
	else if (SensorData->co2_value_u16 >= 350 && SensorData->co2_value_u16 <= 380)
	{
		PORTD |= 0b00100000;
	}
	else
	{
		PORTD |= 0b00010000;
	}
}