/*
 * Projekt.c
 *
 * Created: 26.01.2021 16:19:56
 * Author : Niklas Theis
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "CO2Output.h"
#include "Timer.h"
#include "utils.h"
#include "LCD.h"

#define setpin(port,bitnummer) port |= (1<<bitnummer)
#define clrpin(port,bitnummer) port &= ~(1<<bitnummer)

#define LCDPORT PORTB
#define LCDDDR DDRB

#define BUTTONUP ((~PIND & (1 << 0)) >> 0)
#define BUTTONDOWN ((~PIND & (1 << 1)) >> 1)

#define LCD_RS_PIN 0
#define LCD_RW_PIN 1
#define LCD_E_PIN 2

uint8_t buttonUp = 0;
uint8_t buttonUp_before = 0;
uint8_t buttonDown = 0;
uint8_t buttonDown_before = 0;

uint8_t timerInterruptFlag = 0;
uint8_t timerLEDOutput = 0;

int main(void)
{
	DDRD = 0b01111100;
	
	struct SensorData_t sensorData =
	{
		.co2_value_f = 1763.36f,
		.firmware_version_u16 = 12,
		.humidity_value_f = 50.5,
		.temperature_value_f = 26.4,
		.MeasState_en = CO2_MEAS_RUNNING,
		.AutocalibMode_en = CO2_AUTOCAL_INACTIVE
	};

	LCD_Settings_t lcdSettings =
	{
		.Cursor = CursorOff,
		.Port = &LCDPORT,
		.PortDDR = &LCDDDR,
		.PortPIN = &PINB
	};

	CO2Output_Init(&sensorData, &lcdSettings, NoAlign);
	
	struct Timer_Settings_t timerSettings =
	{
		.CompareBValue = 0,
		.CTCMode = CTCTopOCR1A
	};
	Timer_calculateTimerSettings_s(&(timerSettings.CompareAValue), &(timerSettings.ClockSignal), 2);
	
	Timer_init(timerSettings);
	Timer_addInterrupt(InterruptCompareA, &timerInterruptFlag);
	
	
	while(1)
	{
		if (timerInterruptFlag)
		{
			uint8_t COError = CO2Output_UpdateData();
			if (COError)
			{
				LCD_WriteError("CO2Output-Error", COError);
			}
			
			//debug section: LED
			if (timerLEDOutput)
			{
				PORTD &= 0b11111011;
				timerLEDOutput = 0;
			}
			else
			{
				PORTD |= 0b00000100;
				timerLEDOutput = 1;
			}
			//end debug section
			
			timerInterruptFlag = 0;
		}
		
		buttonUp = BUTTONUP;
		buttonDown = BUTTONDOWN;
		if ((buttonUp != buttonUp_before) && buttonUp == 1 && buttonDown == 0)
		{
			CO2Output_MoveUp();
		}
		buttonUp_before = buttonUp;
		if ((buttonDown != buttonDown_before) && buttonUp == 0 && buttonDown == 1)
		{
			CO2Output_MoveDown();
		}
		buttonDown_before = buttonDown;
	}
}