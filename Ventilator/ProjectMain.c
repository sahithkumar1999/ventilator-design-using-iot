// ---------------------------------------------------------------------------
// *                        www.apsis-solutions.com
// *               Copyright (c) Apsis Solutions, Bangalore
// *--------------------------------------------------------------------------
// *    Project         : Generic
// *    Module          : Project Main
// *    Description     : Project Starts Here
// *					  	  
// *    Author          : Ajith Kirlaya
// *    Workfile        : Projectmain.c
// *    Revision        : 2.0
// *    Last changed on : Date: 2017-10-08
// *                     
// *    Last changed by : Nitin Awasthi - +91-9880221378
// *    Last changed on : Date: 2019-11-19
// *
// *    Last changed by : Chiranjit Gorai
// *    Last changed on : Date: 2020-04-13
// *--------------------------------------------------------------------------

#include <p18f46k22.h>    
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include "ProjectMain.h"  
#include "serial_codes.h"
#include "ADC.H" 
#include "PinAllocation.h"
#include "LCD.h"
#include "delay.h"
#include "timers.h"
#include "wifimodule.h" 

unsigned char guchLCDLine1String[17],guchLCDLine2String[17];
unsigned char uchBuffDisplay[] = "APSIS SOLUTIONS\n\r";
#pragma udata udata3
unsigned char uchRecieve150Ch[150],i = 0;
unsigned int guchDataTowebsite;
extern unsigned int gunField1Value,gunField2Value,gunField3Value,gunField4Value,gunField5Value,gunField6Value,gunField7Value,gunField8Value;
unsigned long ulVoltageInVolts;
extern unsigned char guchField5Value;
extern unsigned int gunDataFromFields;
unsigned char guchSendingData[10]= "TESTED OK";

unsigned char uchStepperMotor_1_Status = 0x88;





void fnDCMotor_1_Clock()
{
	DC_MOTOR_1_COIL_A = OUTPUT_HIGH;
	DC_MOTOR_1_COIL_B = OUTPUT_LOW;
}

void fnDCMotor_1_AntiClock()
{
	DC_MOTOR_1_COIL_A = OUTPUT_LOW;
	DC_MOTOR_1_COIL_B = OUTPUT_HIGH;
}

void fnDCMotor_1_Stop()
{
	DC_MOTOR_1_COIL_A = OUTPUT_LOW;
	DC_MOTOR_1_COIL_B = OUTPUT_LOW;
}





void fnStepperMotor_1_UpdateToPort(void)
{
	if((uchStepperMotor_1_Status & 0x01) !=0)
	{
		STEPPER_MOTOR_1_COIL_D = 1;
	}
	else
	{
		STEPPER_MOTOR_1_COIL_D = 0;
	}

	if((uchStepperMotor_1_Status & 0x02) !=0)
	{
		STEPPER_MOTOR_1_COIL_C = 1;
	}
	else
	{
		STEPPER_MOTOR_1_COIL_C = 0;
	}

	if((uchStepperMotor_1_Status & 0x04) !=0)
	{
		STEPPER_MOTOR_1_COIL_B = 1;
	}
	else
	{
		STEPPER_MOTOR_1_COIL_B = 0;
	}

	if((uchStepperMotor_1_Status & 0x08) !=0)
	{
		STEPPER_MOTOR_1_COIL_A = 1;
	}
	else
	{
		STEPPER_MOTOR_1_COIL_A = 0;
	}
}

void fnStepperMotor_1_Clockwise(void)
{
	unsigned char uchStoreMSB = 0;

	uchStoreMSB = uchStepperMotor_1_Status & 0x80;

	uchStepperMotor_1_Status = uchStepperMotor_1_Status << 1; // uchStepperMotor_1_Status = uchStepperMotor_1_Status * 2;

	if(uchStoreMSB != 0)
	{
		uchStepperMotor_1_Status = uchStepperMotor_1_Status | 0x1; // + 1
	}
	fnStepperMotor_1_UpdateToPort();
}


void fnStepperMotor_1_AntiClockwise(void)
{
	unsigned char uchStoreLSB = 0;

	uchStoreLSB = uchStepperMotor_1_Status & 0x01; // LSB Mask = 0x01

	uchStepperMotor_1_Status = uchStepperMotor_1_Status >> 1; // uchStepperMotor_1_Status = uchStepperMotor_1_Status / 2;

	if(uchStoreLSB != 0)
	{
		uchStepperMotor_1_Status = uchStepperMotor_1_Status | 0x80; // + 128
	}
	fnStepperMotor_1_UpdateToPort();
}

void fnMain_Project()
{	
	unsigned int unTemperatureValue; 
	unsigned int unADCvalueSmokeSensor =0;
	unsigned int unDataFromThingspeakforDeviceControl = 0;
	unsigned int unDataFromField1,unDataFromField2;
	unsigned char uchCommandForRobot;
	unsigned char a=10,b=5,c=0;
	unsigned char uchData;
	unsigned char uchData1;
	
 	unsigned char uchRecieve150Ch[10],i = 0;
 	unsigned char uchtemp;
 	
 	unsigned char uchTempvalue[];
 	unsigned int  unADCvalue1=0;
 	unsigned int  unADCvalue2=0;
 	unsigned int  unADCvalue3=0;
 	unsigned int  unADCvalue4=0;
 	
 	unsigned int unIteration=0;

 	unsigned int unCount;

	
 	ANSELA = 0X00;
	Dir_DEVICE_0   = SET_OUTPUT;
	Dir_DEVICE_1   = SET_OUTPUT;
	Dir_DEVICE_2   = SET_OUTPUT;
	Dir_DEVICE_3   = SET_OUTPUT;
	Dir_DEVICE_4   = SET_OUTPUT;
	Dir_DEVICE_5   = SET_OUTPUT;

	Dir_BUZZER     		= SET_INPUT;
	BUZZER			 	= BUZZER_OFF; 

	DEVICE_0   = DEVICE_OFF;
	DEVICE_1   = DEVICE_OFF;
	DEVICE_2   = DEVICE_OFF;
	DEVICE_3   = DEVICE_OFF;
	DEVICE_4   = DEVICE_OFF;
	DEVICE_5   = DEVICE_OFF;


	Ans_STEPPER_MOTOR_1_COIL_A = SET_DIGITAL;
	Ans_STEPPER_MOTOR_1_COIL_B = SET_DIGITAL;
	Ans_STEPPER_MOTOR_1_COIL_C = SET_DIGITAL;
	Ans_STEPPER_MOTOR_1_COIL_D = SET_DIGITAL;

	Ans_DC_MOTOR_1_COIL_A  = SET_DIGITAL;
	Ans_DC_MOTOR_1_COIL_B  = SET_DIGITAL;

	Dir_STEPPER_MOTOR_1_COIL_A = SET_OUTPUT;
	Dir_STEPPER_MOTOR_1_COIL_B = SET_OUTPUT;
	Dir_STEPPER_MOTOR_1_COIL_C = SET_OUTPUT;
	Dir_STEPPER_MOTOR_1_COIL_D = SET_OUTPUT;

	Dir_DC_MOTOR_1_COIL_A = SET_OUTPUT;
	Dir_DC_MOTOR_1_COIL_B = SET_OUTPUT;

	STEPPER_MOTOR_1_COIL_A = 1;
	STEPPER_MOTOR_1_COIL_B = 0;
	STEPPER_MOTOR_1_COIL_C = 0;
	STEPPER_MOTOR_1_COIL_D = 0;

	Ans_sw_EMERGENCY_SWITCH			= SET_DIGITAL;
	Ans_sw_PANIC_SWITCH				= SET_DIGITAL;
	Ans_sw_START_LIMIT_SWITCH		= SET_DIGITAL;
	Ans_sw_END_LIMIT_SWITCH			= SET_DIGITAL;
	Ans_sw_START_SWITCH				= SET_DIGITAL;
	Ans_sw_PANIC_SWITCH				= SET_DIGITAL;

	Dir_sw_EMERGENCY_SWITCH			= SET_INPUT;
	Dir_sw_PANIC_SWITCH				= SET_INPUT;
	Dir_sw_START_LIMIT_SWITCH		= SET_INPUT;
	Dir_sw_END_LIMIT_SWITCH			= SET_INPUT;
	Dir_sw_START_SWITCH				= SET_INPUT;
	Dir_sw_PANIC_SWITCH				= SET_INPUT;

	// Bring Our Motor to Start 
	// fnStepperMotor_1_Clockwise(); --- Move towards Start
	// fnStepperMotor_1_AntiClockwise(); --- Move towards End

	printf("Bringing Motor Towards Start Limit Switch\n\r");
	printf("If Motor was not in start position then move motor towards Start\n\r");
	while(sw_START_LIMIT_SWITCH == NOT_PRESSED)
	{
		printf("SMC.");
		fnStepperMotor_1_Clockwise();
	}
	printf("Motor Reached the Start position\n\r");

	printf("Waiting for the Doctor to press Start Switch \n\r");

	while(sw_START_SWITCH == NOT_PRESSED)
	{
		printf("Press Start Switch\n\r");
		Delay_in_ms(2000);
	}

	printf("Start Switch was pressed - Initiating the logic\n");

	while(1)
	{
		// Move motor towards the End Limit Switch
		while(sw_END_LIMIT_SWITCH == NOT_PRESSED)
		{
			printf("SMA.");
			fnStepperMotor_1_AntiClockwise();
		}
		printf("End Reached so starting to move Back towards Start\n\r");
		while(sw_START_LIMIT_SWITCH == NOT_PRESSED)
		{
			printf("SMC.");
			fnStepperMotor_1_Clockwise();
		}
		printf("Motor Reached the Start position\n\r");
		printf("Motor Now Moving towards End\n\r");


	}







	printf("Stepper Motor - Inmovidu\n\r");
	fnStepperMotor_1_UpdateToPort();

	printf("uchStepperMotor_1_Status %d 0x%x\n",uchStepperMotor_1_Status,uchStepperMotor_1_Status);
	
	for(i=0;i<9;i++)
	{
		fnStepperMotor_1_Clockwise();
		Delay_in_ms(100);
		printf("CLOCK uchStepperMotor_1_Status %d 0x%x\n",uchStepperMotor_1_Status,uchStepperMotor_1_Status);		
	}
	for(i=0;i<9;i++)
	{
		fnStepperMotor_1_AntiClockwise();
		Delay_in_ms(100);
		printf("AntiClock uchStepperMotor_1_Status %d 0x%x\n",uchStepperMotor_1_Status,uchStepperMotor_1_Status);		
	}



	
	while(1)
	{
		fnDCMotor_1_Clock();
		delay_in_half_seconds(4);
		fnDCMotor_1_AntiClock();
		delay_in_half_seconds(4);
		fnDCMotor_1_Stop();
		delay_in_half_seconds(4);		
	}
	





	printf("Nitin Entering into a loop to check the switch pressed state\n\r");

	//Ans_ALARM_PIN 	= SET_DIGITAL;
	Dir_ALARM_PIN	= SET_OUTPUT;
	ALARM_PIN 		= ALARM_OFF;







	Ans_sw_EMERGENCY_SWITCH 	= SET_DIGITAL;	// ANSELBbits.ANSB0 = 0;
	Dir_sw_EMERGENCY_SWITCH 	= SET_INPUT;    // TRISBbits.TRISB0 = 1;
	
	Ans_sw_FORWARD 	= SET_DIGITAL;	
	Dir_sw_FORWARD 	= SET_INPUT;    
	
	Ans_sw_BACKWARD = SET_DIGITAL;	
	Dir_sw_BACKWARD = SET_INPUT;  

	Ans_sw_LEFT 	= SET_DIGITAL;	
	Dir_sw_LEFT 	= SET_INPUT;  

	Ans_sw_RIGHT 	= SET_DIGITAL;	
	Dir_sw_RIGHT 	= SET_INPUT;  



	printf("Basic settings completed\n\r");

	unCount = 0;
	while(1)
	{
		Delay_in_ms(2000);
		printf(".");
		if(sw_FORWARD == PRESSED) // Sw_Forward is our Sensor in this example
		{
			unCount++;
			printf("\n\rHuman Identified and counted %d\n\r", unCount);
			
		}

	}






	while(1)
	{
		Delay_in_ms(2000);
		if(sw_FORWARD == PRESSED) 
		{
			printf("sw_FORWARD was PRESSED\n\r");
		}
		else if(sw_BACKWARD == PRESSED) 
		{
			printf("sw_BACKWARD was PRESSED\n\r");
		}
		else if(sw_LEFT == PRESSED) 
		{
			printf("sw_LEFT was PRESSED\n\r");
		}
		else if(sw_RIGHT == PRESSED) 
		{
			printf("sw_RIGHT was PRESSED\n\r");
		}
		else 
		{
			printf("Robot Stop\n\r");
		}
	}



	while(1)
	{
		Delay_in_ms(2000);
		if(sw_EMERGENCY_SWITCH == PRESSED) // PORTBbits.RB0 == PRESSED
		{
			ALARM_PIN 		= ALARM_ON;
			printf("sw_EMERGENCY_SWITCH was PRESSED\n\r");
		}
		else
		{
			ALARM_PIN 		= ALARM_OFF;
			printf("sw_EMERGENCY_SWITCH was NOT PRESSED\n\r");
		}

	}
	
	
	
	





	///------------------------------

	ANSELA 	= 	0xFF;
	ANSELA 	= 	0x55;
	
	
	TRISA	=	0x55;

	TRISE	=	0xFF;
	TRISE	=	0x55;

	printf("My First Code \n\r");

	while(1)
	{
		printf("Iteration Number %d \n\r", unIteration);
		unIteration++;
		if(unIteration > 10)
		{
			unIteration = 0;
		}
		// To convert the port into Digital
		ANSELA 	= 	0x0;
		// To make the port as output
		TRISA	=	0x0;
		// 
		
		Delay_in_ms(250);
		PORTA	= 	0xFF;
		Delay_in_ms(250);		
	}

















	gunField1Value=-1;
	gunField2Value=-1;
	gunField3Value=-1; // value to update
	gunField4Value=-1;
	
	while(1)
	{
		printf("Nitin Waiting For Bluetooth Data...\n\r");
		while(uchfnReceive_Serial(UART1)!='*');
		printf("Data Received From Bluetooth ...\n\r");


		gunField1Value += 100;
		//gunField2Value += 200;
		gunField3Value += 300;
		gunField4Value += 400;



		gunField2Value += 200;
		
		printf("\n\rUploading %d...",gunField2Value);

		fnDatauploadTothingspeakwebsite();
		printf("\n\rUploaded...");
		delay_in_seconds(2);
		unDataFromThingspeakforDeviceControl = fnFieldValuesFromChannels(2);//DP 2
		// delay_in_seconds(1);

		if(unDataFromThingspeakforDeviceControl == gunField2Value)
		{
			printf("Tested OK: Thank you for Testing...\n\r");
		}
		else
		{
			printf("ERROR: Tested NOK - Data Not Matched\n\r");
		}
	


	}





























	printf("Waiting For Blutooth Data...\n\r");

	gunField2Value = 175;

	while(1)
	{
		// printf("Waiting For Blutooth Data...\n\r");
		// while(uchfnReceive_Serial(UART1)!='*');
		// printf("Data Recevied From Blutooth ...\n\r");

		gunField2Value = gunField2Value + 50;

		fnDatauploadTothingspeakwebsite();
		printf("\n\rUploaded...");
		delay_in_seconds(2);
		unDataFromThingspeakforDeviceControl = fnFieldValuesFromChannels(2);//DP 2
		// delay_in_seconds(1);

		if(unDataFromThingspeakforDeviceControl == gunField2Value)
		{
			printf("Tested OK, Thank you for Tested...\n\r");
		}
		//printf("unDataFromThingspeakforDeviceControl =%d \n\r",unDataFromThingspeakforDeviceControl);
		//delay_in_seconds(5);

	}




	// while(1)
	// {


	// 	unDataFromThingspeakforDeviceControl = fnFieldValuesFromChannels(7);
	// 	printf("unDataFromThingspeakforDeviceControl =%d \n\r",unDataFromThingspeakforDeviceControl);
	// 	LATA= unDataFromThingspeakforDeviceControl & 0x3F;
	// 	delay_in_seconds(3);
	// 	unADCvalueSmokeSensor = unfnReadADCChannel(SMOKE_SENSOR_CHANNEL,ADC_10BIT_MODE);
	// 	printf("unADCvalueSmokeSensor =%d \n\r",unADCvalueSmokeSensor);
	// 	if(unADCvalueSmokeSensor > SMOKE_SENSOR_ADC_THRESHOLD)
	// 	{
	// 		BUZZER = BUZZER_ON;
	// 		gunField8Value = unADCvalueSmokeSensor;
	// 		fnDatauploadTothingspeakwebsite();
	// 		delay_in_seconds(3);
			
			
	// 	}
	// 	else
	// 	{

	// 		BUZZER	= BUZZER_OFF; 
	// 	}


	// }

	while(1)
	{
		unDataFromField1 = fnFieldValuesFromChannels(1);
		printf("unDataFromField4 = %d\n\r",unDataFromField1);
		
	}

	// while(1)
	// {
	// 	unADCvalue1 = unfnReadADCChannel(CHANNEL_0,ADC_10BIT_MODE);
	// 	unADCvalue2 = unfnReadADCChannel(CHANNEL_5,ADC_10BIT_MODE);
	// 	printf("unADCvalue1 =%04d  unADCvalue2 =%04d  \n\r",unADCvalue1,unADCvalue2);
	// 	gunField1Value=unADCvalue1;
	// 		delay_in_half_seconds(4);
		
	// }	
	// while(1)
	// {
	// 	unDataFromField1=fnFieldValuesFromChannels(1);
		
	// 	printf("unDataFromField1	= %d\n\r",unDataFromField1);
	// 	unDataFromField2=fnFieldValuesFromChannels(2);
	// 	printf("unDataFromField2	= %d\n\r",unDataFromField2);	
	// 	delay_in_half_seconds(2);
		
	// }
}
