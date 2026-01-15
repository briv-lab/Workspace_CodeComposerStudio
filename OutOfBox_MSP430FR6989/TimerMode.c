/* --COPYRIGHT--,BSD
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/*******************************************************************************
 *
 * TimerMode.c
 *
 * Simple countdown timer application with increment/decrement controls
 *
 ******************************************************************************/

#include <driverlib.h>
#include "TimerMode.h"
#include "hal_LCD.h"

volatile unsigned char timerRunning = 0;
volatile int timerSeconds = 60;

void timer()
{
    while(mode == TIMER_MODE)
    {
        __bis_SR_register(LPM3_bits | GIE);
        __no_operation();

        displayTimerValue();
    }
}

void timerModeInit()
{
    timerRunning = 0;
    timerSeconds = 60;
    timerRtcCounter = 0;
    
    displayScrollText("mode minuteur");

    LCD_C_selectDisplayMemory(LCD_C_BASE, LCD_C_DISPLAYSOURCE_MEMORY);

    RTC_C_holdClock(RTC_C_BASE);

    RTC_C_initCounter(RTC_C_BASE, RTC_C_CLOCKSELECT_32KHZ_OSC, RTC_C_COUNTERSIZE_16BIT);
    RTC_C_definePrescaleEvent(RTC_C_BASE, RTC_C_PRESCALE_1, RTC_C_PSEVENTDIVIDER_32);
    RTC_C_enableInterrupt(RTC_C_BASE, RTC_C_PRESCALE_TIMER1_INTERRUPT);

    displayTimerValue();

    S1buttonDebounce = 0;
    S2buttonDebounce = 0;

    Timer_A_initUpMode(TIMER_A0_BASE, &initUpParam_A0);
    __bis_SR_register(LPM3_bits | GIE);
    __no_operation();

    ADC12_B_disable(ADC12_B_BASE);
    ADC12_B_disableConversions(ADC12_B_BASE, true);
    Timer_A_stop(TIMER_A1_BASE);
}

void displayTimerValue()
{
    int absSeconds = (timerSeconds < 0) ? -timerSeconds : timerSeconds;
    int minutes = absSeconds / 60;
    int seconds = absSeconds % 60;

    showChar((seconds % 10) + '0', pos6);
    showChar((seconds / 10) + '0', pos5);
    showChar((minutes % 10) + '0', pos4);
    showChar((minutes / 10) + '0', pos3);
    showChar(' ', pos2);
    showChar((timerSeconds < 0) ? '-' : ' ', pos1);

    LCDM7 |= 0x04;
    LCDBM7 |= 0x04;
    LCDM20 |= 0x04;
    LCDBM20 |= 0x04;
}
