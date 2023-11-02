#ifndef _ADC_CONFIG_H_
#define _ADC_CONFIG_H_

//-------------------------------------------------
//Voltage Reference Selection
#define AREF 		0		//AREF, Internal Vref turned off		REFS1 REFS0 00
#define AVCC 		1		//AVCC with external capacitor at AREF pin	REFS1 REFS0 01
#define Reserved 	2		//Reserved	REFS1 REFS0 10
#define Internal 	3		//Internal 2.56V Voltage Reference with external capacitor at AREF pin		REFS1 REFS0 11
#define Voltage_Reference_Selection 	AVCC
//-------------------------------------------------
// The ADC Data Register � ADCL and ADCH
#define ADC_10Bits				0									//ADLAR = 0 	for Right Adjust
#define ADC_8Bits				1									//ADLAR = 1		for Left Adjust
#define ADC_Data_Register_width		ADC_10Bits	 	// ADC_10Bits // ADC_8Bit //
//-------------------------------------------------
//ADC Prescaler Select Bits
//Bits 2:0 � ADPS2:0: ADC Prescaler Select Bits	0b000 -> Division Factor 2 ~ 0b111 -> Division Factor 128
//Bits 2:0 � ADPS2:0: ADC Prescaler Select Bits	conversion clock =  microcontroller clock / Division Factor,
//Bits 2:0 � ADPS2:0: ADC Prescaler Select Bits	Conversion time = conversion time * 8/10 based one 8bits/10bits
#define Division_Factor_2		0		// if clock 8MHz then conversion clock = 4MHz, conversion time = 1 /conversion clock
#define Division_Factor_4		1
#define Division_Factor_8		2
#define Division_Factor_16	3
#define Division_Factor_32	4
#define Division_Factor_64	5
#define Division_Factor_128	6
#define ADC_Division_Factor		Division_Factor_64
//-------------------------------------------------
//ADC Enable Mode
#define ADC_Enable_OD		0		//ADC Enable On demand , must be called each time >> Single conversion
#define ADC_Enable_ATT		1		//ADC Enable All The Time, Set in ADC Initialization function >>Free running
#define ADC_Enable_Mode			ADC_Enable_ATT
//-------------------------------------------------
//ADC Auto Trigger Enable
//When this bit is written to one, Auto Triggering of the ADC is enabled.
//The ADC will start a conversion on a positive edge of the selected trigger signal.
//The trigger source is selected by setting the ADC Trigger Select bits, ADTS in SFIOR.
//If ADC_Auto_Trigger_Disable then ADATE is cleared, the ADTS2:0 settings will have no effect
//A conversion will be triggered by the rising edge of the selected Interrupt Flag.
#define ADC_Auto_Trigger_Disable		0		//ADC Enable On demand , must be called each time >> Single conversion
#define ADC_Auto_Trigger_Enable		1		//ADC Enable All The Time, Set in ADC Initialization function >>Free running
#define ADC_Auto_Trigger					ADC_Auto_Trigger_Enable
//-------------------------------------------------
// ADC Auto Trigger Source Selections	(Table 86)
//ADTS2 ADTS1 ADTS0 Trigger Source
#define Free_Running_mode						0	//0 0 0
#define Analog_Comparator							1	//0 0 1
#define External_Interrupt_Request_0			2	//0 1 0
#define Timer_Counter0_Compare_Match		3	//0 1 1
#define Timer_Counter0_Overflow				4	//1 0 0
#define Timer_Counter_Compare_Match_B 	5	//1 0 1
#define Timer_Counter1_Overflow				6	//1 1 0
#define Timer_Counter1_Capture_Event		7	//1 1 1
#define ADC_Auto_Trigger_Source_Selections	Free_Running_mode
//-------------------------------------------------
//

#endif	//end guard _ADC_CONFIG_H_//
