#ifndef _ADC_INTERFACE_H_
#define _ADC_INTERFACE_H_

//------------------AVR ATmega32------------------------
//------------------ADC Control and Status Register A � ADCSRA------------------------
#define ADCSRA_ADEN		7	//Bit 7 � ADEN: ADC Enable
#define ADCSRA_ADSC		6	//Bit 6 � ADSC: ADC Start Conversion
#define ADCSRA_ADATE		5	//Bit 5 � ADATE: ADC Auto Trigger Enable
#define ADCSRA_ADIF			4	//Bit 4 � ADIF: ADC Interrupt Flag
#define ADCSRA_ADIE			3	//Bit 3 � ADIE: ADC Interrupt Enable
#define ADCSRA_ADPS2		2	//Bits 2:0 � ADPS2:0: ADC Prescaler Select Bits	0b000 -> Division Factor 2 ~ 0b111 -> Division Factor 128
#define ADCSRA_ADPS1		1	//Bits 2:0 � ADPS2:0: ADC Prescaler Select Bits	conversion clock =  microcontroller clock / Division Factor
#define ADCSRA_ADPS0		0	//Bits 2:0 � ADPS2:0: ADC Prescaler Select Bits	Conversion time = conversion clock * 8/10 based one 8bits/10bits
//------------------------------------------
//------------------ADC Multiplexer Selection Register � ADMUX------------------------
#define ADMUX_REFS1			7
#define ADMUX_REFS0			6
#define ADMUX_ADLAR 		5
//ADC Input Channel
//MUX4..0 Single Ended Input without Gain
#define	ADC_Channel0		0b00000
#define	ADC_Channel1		0b00001
#define	ADC_Channel2		0b00010
#define	ADC_Channel3		0b00011
#define	ADC_Channel4		0b00100
#define	ADC_Channel5		0b00101
#define	ADC_Channel6		0b00110
#define	ADC_Channel7		0b00111
//------------------------------------------
//ADC Input Channel and Gain Selections
//PositiveDifferentialInput_NegativeDifferentialInput_Gain//
//all 200x are not tested for devices in PDIP Package,
//all 200x are only guaranteed to work for devices in TQFP and MLF Packages
// ADC = ((VPOS � VNEG) * GAIN * 512) / VREF
#define ADC0_ADC0_10x			0b01000
#define ADC1_ADC0_10x			0b01001
#define ADC0_ADC0_200x		0b01010
#define ADC1_ADC0_200x		0b01011
#define ADC2_ADC2_10x			0b01100
#define ADC3_ADC2_10x			0b01101
#define ADC0_ADC0_10x			0b01000
#define ADC2_ADC2_200x		0b01110
#define ADC3_ADC2_200x		0b01111
#define ADC0_ADC1_1x			0b10000
#define ADC1_ADC1_1x			0b10001
#define ADC2_ADC1_1x			0b10010
#define ADC3_ADC1_1x			0b10011
#define ADC4_ADC1_1x			0b10100
#define ADC5_ADC1_1x			0b10101
#define ADC6_ADC1_1x			0b10110
#define ADC7_ADC1_1x			0b10111
#define ADC0_ADC2_1x			0b11000
#define ADC1_ADC2_1x			0b11001
#define ADC2_ADC2_1x			0b11010
#define ADC3_ADC2_1x			0b11011
#define ADC4_ADC2_1x			0b11100
#define ADC5_ADC2_1x			0b11101
#define Single_Ended_Input_1_22V	0b11110		// for (VBG) N/A 1.22v
#define Single_Ended_Input_0V 		0b11111		// for (GND)
//------------------------------------------
//------------------ADC Special FunctionIO Register � SFIOR------------------------
//Bit 7:5 � ADTS2:0: ADC Auto Trigger Source
// ADC Auto Trigger Source Selections from ADC_Config.h
#define SFIOR_ADTS2 				7
#define SFIOR_ADTS1				6
#define SFIOR_ADTS0				5
//------------------------------------------


//Functions declaration
void ADC_VidInit(void);	//ADC initialization
u16 ADC_VidGetDigitalValue(u8 LOC_u8channel);	// ADC return the digital value of conversion
void ADC_VidInterrupt_Enable(void);
void ADC_VidStartConversionNonBlocking( u8 LOC_u8channel);
void ADC_SetCallBack(void(*LocalPF)(void));
void ADC_VidSTOPConversion( u8 LOC_u8channel);

#endif
