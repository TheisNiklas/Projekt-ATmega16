/*
 * CO2_Output.h
 *
 * Created: 03.02.2021 14:29:59
 *  Author: Niklas Theis
 */
#pragma once

#include <avr/io.h>
#include <stdio.h>

#include "LCD.h"
#include "CO2Sensor.h"

#define MAX_CHAR_LEN 40

enum CO2OutputAlignValueRight
{
	NoAlign = 0,
	AlignIfPossible = 1
};
typedef enum CO2OutputAlignValueRight CO2OutputAlignValueRight;

struct CO2OutputData_t
{
	char co2Value[MAX_CHAR_LEN];
	char humidityValue[MAX_CHAR_LEN];
	char temperatureValue[MAX_CHAR_LEN];
	char autocalibMode[MAX_CHAR_LEN];
	char measState[MAX_CHAR_LEN];
	char firmwareVersion[MAX_CHAR_LEN];
};

typedef struct CO2OutputData_t CO2OutputData_t;

uint8_t CurrentLine;

SensorData_t* SensorData;

CO2OutputAlignValueRight AlignSetting;

CO2OutputData_t OutputData;

void InitCO2Output(SensorData_t* sensorData, volatile uint8_t* Port, enum LCD_CursorSetting cursorSetting, enum CO2OutputAlignValueRight alignSetting);

void CO2Output_UpdateData();
void CO2Output_MoveUp();
void CO2Output_MoveDown();