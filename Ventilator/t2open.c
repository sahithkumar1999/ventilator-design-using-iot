


// ---------------------------------------------------------------------------
// *                        www.apsis-solutions.com
// *               Copyright (c) Apsis Solutions, Bangalore
// *--------------------------------------------------------------------------
// *    Project         : Generic
// *    Module          : timer 
// *    Description     : Timeout period can be configured using this file  
// *					  	  
// *    Author          : Apsis Solutions
// *    Workfile        : t2open.c
// *    Revision        : 2.0
// *    Last changed on : Date: 2017-12-06
// *                     
// *    Last changed by : Ajith Kirlaya
// *
// *--------------------------------------------------------------------------




#include <p18cxxx.h>
#include "timers.h"
#define TMR_V2
/********************************************************************
*    Function Name:  OpenTimer2                                     *
*    Return Value:   void                                           *
*    Parameters:     config: bit definitions to configure Timer2    *
*    Description:    This routine first resets the Timer2 regs      *
*                    to the POR state and then configures the       *
*                    interrupt and clock source.                    *
*    Notes:          The bit definitions for config can be found    *
*                    in the timers.h file.                          *
********************************************************************/
extern unsigned char guchTimeOutFlag ;
unsigned char guchTimerTimeOutCount;
extern unsigned char guchTimerCount;
#if defined (TMR_V2) || defined (TMR_V3) || defined (TMR_V4) ||\
    defined (TMR_V5) || defined (TMR_V6) || defined (TMR_V7) || defined (TMR_V7_1)
void OpenTimer2(unsigned char config)
{
  T2CON = (0xfb & config);  // Set all configuration values, but
                            // don't start timer yet 								

  TMR2 = 0;                 // Clear Timer2
  PIR1bits.TMR2IF = 0;

  if(config & 0x80)         // Enable timer interrupts?
    PIE1bits.TMR2IE = 1;
  else
    PIE1bits.TMR2IE = 0;

  T2CONbits.TMR2ON = 1; // Turn on Timer2
}
#endif

/// Changed BY Ajith Kirlaya // 
/// This  function is used to give the  to timeout for the ifinite loops
void fnApsisTimeout(unsigned char uchTimeOutTimeinSeconds)
{
  fnoneSecondTimerDelay();

  guchTimerTimeOutCount = uchTimeOutTimeinSeconds;
}
/// Changed BY Ajith Kirlaya // 
// Disable the timer 
void CloseTimer(void)
{
	T0CONbits.TMR0ON      = 0;  // Disable Timer0
	INTCONbits.TMR0IF     = 0;   // Disable Timer0 overflow interrupts
	guchTimerTimeOutCount = 0;
	guchTimeOutFlag		  = 0;
	guchTimerCount		  = 0; // 
}


void fnoneSecondTimerDelay()
{
   

  T0CONbits.TMR0ON  = 0;
  TMR0H = 0x0B;
  TMR0L = 0xDC; // Count 39063 so load -39063 or 6769 // i.e. 65536 - 39063 = 26473 
  INTCONbits.TMR0IF = 0;
  T0CONbits.TMR0ON  = 1;

}


void fnTimer0Initialize(void)
{
  unsigned char uchTimer0RegisterValue;
  T0CON = 0x00;
  T0CON = TMR0Off|T016bit|T0CS_Internal|T0SE_HightoLow|PSA_Enable|TOPS_Foscby16 ; 
	INTCONbits.GIE		= 1;
	INTCONbits.PEIE		= 1;	
	INTCONbits.TMR0IE	= 1;

}


