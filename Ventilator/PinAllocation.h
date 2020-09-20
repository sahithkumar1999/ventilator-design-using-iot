// ---------------------------------------------------------------------------
// *                        www.apsis-solutions.com
// *               Copyright (c) Apsis Solutions, Bangalore
// *--------------------------------------------------------------------------
// *    Project         : Generic
// *    Module          : ADC 
// *    Description     : Used to Configure the ADC and Read ADC
// *    Author          : Pankaj Sharma
// *    Workfile        : PinAllocation.h
// *    Revision        : 1.0
// *    Last changed on : Date: 2012-04-17
// *                     
// *    Last changed by : Pankaj Sharma
// *
// *--------------------------------------------------------------------------

#include<p18f46k22.h>


// Pin allocation.h
#define DEBUGMODE		1
#define RELEASEMODE	 	0
#define MODE			RELEASEMODE
#define DBGPRINTF if(MODE) printf

#define GPSMODE			RELEASEMODE
#define GPSDBGPRINTF	if(GPSMODE) printf

#define FAIL	0
#define PASS	1

#define SET_ANALOG   1
#define SET_DIGITAL  0

#define SET_INPUT   1
#define SET_OUTPUT  0

#define SET_TRUE 	1
#define SET_FALSE 	0

#define OUTPUT_HIGH  1
#define OUTPUT_LOW   0

#define ON 1
#define OFF 0



#define SELECT_GPS_ON_UART	1
#define SELECT_RFID_ON_UART	2
#define SELECT_PC_ON_UART		3



//  Configuration of LCD pins: 4 data pins, RS pin and Enable pin

#define RS_lcd          LATDbits.LATD0   	// For Selection of data or Command Mode.  				
#define Enable_lcd		LATDbits.LATD1   	// For Enabling the LCD.
#define lcd_d4_lsb		LATDbits.LATD2  	// pin 11 of LCD
#define lcd_d5			LATDbits.LATD3  	// pin 12 of LCD
#define lcd_d6			LATDbits.LATD4   	// pin 13 of LCD
#define lcd_d7_msb		LATDbits.LATD5   	// pin 14 of LCD	

// Direction selection of the PIC controller. The pin selected either as input or output as per the requirement
#define RS_lcd_dir          TRISDbits.TRISD0     				
#define Enable_lcd_dir		TRISDbits.TRISD1   
#define lcd_d4_lsb_dir		TRISDbits.TRISD2   // pin 11 of LCD DIR
#define lcd_d5_dir			TRISDbits.TRISD3   // pin 12 of LCD DIR
#define lcd_d6_dir			TRISDbits.TRISD4   // pin 13 of LCD DIR
#define lcd_d7_msb_dir		TRISDbits.TRISD5   // pin 14 of LCD DIR


#define Dir_DEVICE_0   TRISAbits.TRISA0
#define Dir_DEVICE_1   TRISAbits.TRISA1
#define Dir_DEVICE_2   TRISAbits.TRISA2
#define Dir_DEVICE_3   TRISAbits.TRISA3
#define Dir_DEVICE_4   TRISAbits.TRISA4
#define Dir_DEVICE_5   TRISAbits.TRISA5




#define DEVICE_0   LATAbits.LATA0
#define DEVICE_1   LATAbits.LATA1
#define DEVICE_2   LATAbits.LATA2
#define DEVICE_3   LATAbits.LATA3
#define DEVICE_4   LATAbits.LATA4
#define DEVICE_5   LATAbits.LATA5





#define SMOKE_SENSOR_CHANNEL 6//E1

#define BUZZER_ON 	1
#define BUZZER_OFF 	0

#define Dir_BUZZER 	TRISBbits.TRISB0
#define BUZZER      LATBbits.LATB0 	

#define DEVICE_OFF 		0
#define DEVICE_ON	 	1


#define SMOKE_SENSOR_ADC_THRESHOLD 500




#define ALARM_ON	1
#define ALARM_OFF	0

#define ALARM_PIN	PORTAbits.RA4
#define Dir_ALARM_PIN	TRISAbits.TRISA4
#define Ans_ALARM_PIN	ANSELAbits.ANSA4


#define PRESSED	0
#define NOT_PRESSED	1

#define sw_EMERGENCY_SWITCH	PORTBbits.RB0
#define Dir_sw_EMERGENCY_SWITCH	TRISBbits.TRISB0
#define Ans_sw_EMERGENCY_SWITCH	ANSELBbits.ANSB0

#define sw_PANIC_SWITCH	PORTBbits.RB1
#define Dir_sw_PANIC_SWITCH	TRISBbits.TRISB1
#define Ans_sw_PANIC_SWITCH	ANSELBbits.ANSB1

#define sw_START_LIMIT_SWITCH	PORTBbits.RB2
#define Dir_sw_START_LIMIT_SWITCH	TRISBbits.TRISB2
#define Ans_sw_START_LIMIT_SWITCH	ANSELBbits.ANSB2

#define sw_END_LIMIT_SWITCH	PORTBbits.RB3
#define Dir_sw_END_LIMIT_SWITCH	TRISBbits.TRISB3
#define Ans_sw_END_LIMIT_SWITCH	ANSELBbits.ANSB3


#define sw_START_SWITCH	PORTBbits.RB4
#define Dir_sw_START_SWITCH	TRISBbits.TRISB4
#define Ans_sw_START_SWITCH	ANSELBbits.ANSB4

#define sw_PANIC_SWITCH	PORTBbits.RB1
#define Dir_sw_PANIC_SWITCH	TRISBbits.TRISB1
#define Ans_sw_PANIC_SWITCH	ANSELBbits.ANSB1


#define sw_FORWARD	PORTAbits.RA0
#define Dir_sw_FORWARD	TRISAbits.TRISA0
#define Ans_sw_FORWARD	ANSELAbits.ANSA0

#define sw_BACKWARD	PORTAbits.RA1
#define Dir_sw_BACKWARD	TRISAbits.TRISA1
#define Ans_sw_BACKWARD	ANSELAbits.ANSA1

#define sw_LEFT	PORTAbits.RA2
#define Dir_sw_LEFT	TRISAbits.TRISA2
#define Ans_sw_LEFT	ANSELAbits.ANSA2

#define sw_RIGHT		PORTAbits.RA3
#define Dir_sw_RIGHT	TRISAbits.TRISA3
#define Ans_sw_RIGHT	ANSELAbits.ANSA3



//---- For Stepper Motor COntrolling ----

#define STEPPER_MOTOR_1_COIL_A		PORTAbits.RA0
#define Dir_STEPPER_MOTOR_1_COIL_A	TRISAbits.TRISA0
#define Ans_STEPPER_MOTOR_1_COIL_A	ANSELAbits.ANSA0

#define STEPPER_MOTOR_1_COIL_B		PORTAbits.RA1
#define Dir_STEPPER_MOTOR_1_COIL_B	TRISAbits.TRISA1
#define Ans_STEPPER_MOTOR_1_COIL_B	ANSELAbits.ANSA1

#define STEPPER_MOTOR_1_COIL_C		PORTAbits.RA2
#define Dir_STEPPER_MOTOR_1_COIL_C	TRISAbits.TRISA2
#define Ans_STEPPER_MOTOR_1_COIL_C	ANSELAbits.ANSA2

#define STEPPER_MOTOR_1_COIL_D		PORTAbits.RA3
#define Dir_STEPPER_MOTOR_1_COIL_D	TRISAbits.TRISA3
#define Ans_STEPPER_MOTOR_1_COIL_D	ANSELAbits.ANSA3

// For Trial DC Motor

#define DC_MOTOR_1_COIL_A		PORTDbits.RD4
#define Dir_DC_MOTOR_1_COIL_A	TRISDbits.TRISD4
#define Ans_DC_MOTOR_1_COIL_A	ANSELDbits.ANSD4

#define DC_MOTOR_1_COIL_B		PORTDbits.RD5
#define Dir_DC_MOTOR_1_COIL_B	TRISDbits.TRISD5
#define Ans_DC_MOTOR_1_COIL_B	ANSELDbits.ANSD5




