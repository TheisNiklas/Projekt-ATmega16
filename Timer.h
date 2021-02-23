/*
 * Timer.h
 *
 * Created: 26.01.2021 16:27:30
 *  Author: Niklas Theis
 */ 

#pragma once

enum TimerError_t {NoError, Error};
typedef enum TimerError_t TimerError_t;

enum TimerClockSignal_t {CSTimerStop = 0b000, CSSystemClock = 0b001, CSSystemClockDiv8 = 0b010, CSSystemClockDiv64 = 0b011, CSSystemClockDiv256 = 0b100, CSSystemClockDiv1024 = 0b101, CSExtClockT1Fall = 0b110, CSExtClockT1Rise = 0b111};
typedef enum TimerClockSignal_t TimerClockSignal_t;

enum TimerCTCMode_t {CTCTopOCR1A = 0b01, CTCTopICR1 = 0b10};
typedef enum TimerCTCMode_t TimerCTCMode_t;

enum TimerPWMCOM1A_t {NoPWM, PWNNormal, PWMInverted};
typedef enum TimerPWMCOM1A_t TimerPWMCOM1A_t;

enum TimerInterrupt_t {InterruptInputCapture = 5, InterruptCompareA = 4, InterruptCompareB = 3, InterruptOverflow = 2};
typedef enum TimerInterrupt_t TimerInterrupt_t;

struct TimerSettings_t
{
	TimerClockSignal_t ClockSignal;
	TimerCTCMode_t CTCMode;
	TimerPWMCOM1A_t PWNCOM1A;
};
typedef struct TimerSettings_t TimerSettings_t;

uint8_t InitFlag;
volatile uint8_t* IRCompAFlag;
uint8_t* IRCompBFlag;

TimerError_t initTimer(uint16_t compareAValue, uint16_t compareBValue, TimerSettings_t timerSettings);
TimerError_t initPWN();

TimerError_t Timer_addInterrupt(enum TimerInterrupt_t interrupt, volatile uint8_t* irFlag);
TimerError_t Timer_removeInterrupt(enum TimerInterrupt_t interrupt);

TimerError_t Timer_calculateTimerSettings_s(uint16_t* compareAValue, TimerClockSignal_t* clockSignal, uint8_t seconds);
TimerError_t Timer_calculateTimerSettings_ms(uint16_t* compareAValue, TimerClockSignal_t* clockSignal, uint8_t ms);