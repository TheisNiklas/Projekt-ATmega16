/*
 * LCD.c
 *
 * Created: 30.01.2021 10:38:29
 *  Author: Niklas Theis
 */ 
#include "LCD.h"

LCD_Error_t InitLCD(volatile uint8_t* port, enum LCD_CursorSetting cursorSetting)
{
	LcdPort = port;
	
	CurrentLine = 0;

	_delay_ms (15);
	LCD_8Bit(0x30);
	_delay_ms (4.1);
	LCD_8Bit(0x30);
	_delay_ms (0.1);
	LCD_8Bit(0x30);
	_delay_ms (1);
	LCD_8Bit(0x20);

	LCD_4Bit(0x28,0);
	LCD_4Bit((cursorSetting << 1 | 0b11 << 2),0);
	LCD_4Bit(0x01,0);
	LCD_4Bit(0x02,0);
	_delay_ms (5);
	return LCD_NoError;
}

LCD_Error_t LCD_8Bit(char x)
{
	*LcdPort = x;
	setpin(*LcdPort,LCD_E_PIN);
	_delay_us (1);
	clrpin(*LcdPort,LCD_E_PIN);
	_delay_us (100);
	return LCD_NoError;
}

LCD_Error_t LCD_4Bit(char x, char rs)
{
	LCD_8Bit((x & 0xf0) | (rs<<LCD_RS_PIN));
	LCD_8Bit(((x & 0x0f)<<4) | (rs<<LCD_RS_PIN));
	return LCD_NoError;
}

LCD_Error_t LCD_send(char *s)
{
	while (*s)
	{
		LCD_4Bit(*s, 1);
		s++;
	}
	return LCD_NoError;
}

LCD_Error_t LCD_Clear()
{
	LCD_4Bit(0x01, 0);
	_delay_ms(2);
	return LCD_NoError;
}

LCD_Error_t LCD_Write2Lines(char* line1, char* line2)
{
	int i = 0;
	LCD_Error_t status = LCD_NoError;
	while (*line1)
	{
		LCD_4Bit(*line1, 1);
		line1++;
		i++;
		if(i == 40)
		{
			status = LCD_Error_LineOverflow;
			break;
		}
	}
	LCD_4Bit(0xc0, 0);
	i = 0;
	while (*line2)
	{
		LCD_4Bit(*line2, 1);
		line2++;
		i++;
		if(i == 40)
		{
			status = LCD_Error_LineOverflow;
			break;
		}
	}
	return status;
}

LCD_Error_t LCD_UpdateData(char* lineList, uint8_t linelength, uint8_t lineCount)
{
	LineList = lineList;
	LineLength = linelength;
	LineCount = lineCount;
	LCD_WriteToDisplay();
	return LCD_NoError;
}

LCD_Error_t LCD_WriteToDisplay()
{
	if (CurrentLine >= LineCount) return LCD_Error_OutOfList;
	char* tempList = LineList + CurrentLine * LineLength;
	char line1[MAX_CHAR_COUNT] = {0};
	char line2[MAX_CHAR_COUNT] = {0};
	int i = 0;
	while (*tempList)
	{
		line1[i] = *tempList;
		tempList++;
		i++;
	}
	tempList += LineLength - i;
	i = 0;
	while (*tempList)
	{
		line2[i] = *tempList;
		tempList++;
		i++;
	}
	LCD_Clear();
	LCD_Write2Lines(line1, line2);
	return LCD_NoError;
}

void LCD_MoveUp()
{
	if (CurrentLine != 0) CurrentLine--;
	LCD_WriteToDisplay();
	return;
}

void LCD_MoveDown()
{
	if (CurrentLine < LineCount - 2) CurrentLine++;
	LCD_WriteToDisplay();
	return;
}