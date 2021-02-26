/*
 * LCD.h
 *
 * Created: 30.01.2021 10:38:36
 *  Author: Niklas Theis
 */ 
#pragma once

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#define setpin(port,bitnummer) port |= (1<<bitnummer)
#define clrpin(port,bitnummer) port &= ~(1<<bitnummer)

#define LCD_RS_PIN 0
#define LCD_RW_PIN 1
#define LCD_E_PIN 2

#define MAX_CHAR_COUNT 40

uint8_t CurrentLine;
uint8_t LineCount;
uint8_t LineLength;

char* LineList;

volatile uint8_t* LcdPort;

enum LCD_Error_t {LCD_NoError = 0, LCD_Error = 1, LCD_Error_LineOverflow = 2, LCD_Error_OutOfList = 3};
typedef enum LCD_Error_t LCD_Error_t;
enum LCD_CursorSetting_t {CursorOff = 0, CursorOn = 1};
typedef enum LCD_CursorSetting_t LCD_CursorSetting_t;
enum LCD_Lines_t {OneLine = 0, TwoLines = 1};
typedef enum LCD_Lines_t LCD_Lines_t;

struct LCD_Settings
{
	LCD_CursorSetting_t Cursor;
	LCD_Lines_t Lines;
};

LCD_Error_t LCD_Init(volatile uint8_t* Port, LCD_CursorSetting_t cursorSetting);
LCD_Error_t LCD_8Bit(char x);
LCD_Error_t LCD_4Bit(char x, char rs);
LCD_Error_t LCD_Send(char *s);
LCD_Error_t LCD_Write2Lines(char* line1, char* line2);
LCD_Error_t LCD_UpdateData(char* lineList, uint8_t linelength, uint8_t lineCount);
LCD_Error_t LCD_WriteToDisplay();
LCD_Error_t LCD_MoveUp();
LCD_Error_t LCD_MoveDown();
LCD_Error_t LCD_Clear();
