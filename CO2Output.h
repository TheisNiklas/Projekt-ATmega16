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
#include "utils.h"

#define MAX_CHAR_LEN 40

enum CO2Output_AlignValueRight_t
{
	NoAlign = 0,
	AlignIfPossible = 1
};
typedef enum CO2Output_AlignValueRight_t CO2Output_AlignValueRight_t;

struct CO2Output_Data_t
{
	char co2Value[MAX_CHAR_LEN];
	char humidityValue[MAX_CHAR_LEN];
	char temperatureValue[MAX_CHAR_LEN];
	char autocalibMode[MAX_CHAR_LEN];
	char measState[MAX_CHAR_LEN];
	char firmwareVersion[MAX_CHAR_LEN];
};

typedef struct CO2Output_Data_t CO2Output_Data_t;

uint8_t CurrentLine;

SensorData_t* SensorData;

CO2Output_AlignValueRight_t AlignSetting;

CO2Output_Data_t OutputData;

void CO2Output_Init(SensorData_t* sensorData, volatile uint8_t* Port, LCD_CursorSetting_t cursor, CO2Output_AlignValueRight_t align);

void CO2Output_UpdateData();
void CO2Output_MoveUp();
void CO2Output_MoveDown();
void CO2Output_UpdateLEDs();