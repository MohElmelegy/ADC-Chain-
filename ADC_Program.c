
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "ADC_Register.h"
#include "ADC_Config.h"
#include "ADC_Interface.h"
#include <util/delay.h>


//Global Pointer to Function
static void (*ADC_GPFunction)(void) = NULL;
//Set Global Pointer to Function
void ADC_SetCallBack(void(*LocalPF)(void)) // Parameter is a *ptr_function
{
	//check pointer validation
	if (LocalPF != NULL)
	{
		ADC_GPFunction = LocalPF;
	}
}
void ADC_VidInit(void)
{
	// select the voltage reference from ADC_Config.h
#if Voltage_Reference_Selection ==	AREF
	CLR_BIT(ADMUX, ADMUX_REFS1);
	CLR_BIT(ADMUX, ADMUX_REFS0);
#elif	Voltage_Reference_Selection == AVCC
	CLR_BIT(ADMUX, ADMUX_REFS1);
	SET_BIT(ADMUX, ADMUX_REFS0);
#elif	Voltage_Reference_Selection == Reserved
	SET_BIT(ADMUX, ADMUX_REFS1);
	CLR_BIT(ADMUX, ADMUX_REFS0);
#elif	Voltage_Reference_Selection == Internal
	SET_BIT(ADMUX, ADMUX_REFS1);
	SET_BIT(ADMUX, ADMUX_REFS0);
#else
#error	"Wrong Voltage Reference Selection"
#endif

	// The ADC Data Register – ADCL and ADCH
	// In ADMUX Register
	//ADLAR = 0 	for Right Adjust
	//ADLAR = 1		for Left Adjust
#if ADC_Data_Register_width == ADC_8Bits
	SET_BIT(ADMUX, ADMUX_ADLAR);
#elif ADC_Data_Register_width == ADC_10Bits
	CLR_BIT(ADMUX, ADMUX_ADLAR);
#else
#error	"Wrong Selection of ADC Data Register Width"
#endif

	//Select prescaler -> ADC_Division_Factor	 from ADC_Config.h
#if ADC_Division_Factor == Division_Factor_2
	CLR_BIT(ADCSRA, ADCSRA_ADPS2);
	CLR_BIT(ADCSRA, ADCSRA_ADPS1);
	CLR_BIT(ADCSRA, ADCSRA_ADPS0);
#elif ADC_Division_Factor == Division_Factor_2
	CLR_BIT(ADCSRA, ADCSRA_ADPS2);
	CLR_BIT(ADCSRA, ADCSRA_ADPS1);
	SET_BIT(ADCSRA, ADCSRA_ADPS0);
#elif ADC_Division_Factor == Division_Factor_4
	CLR_BIT(ADCSRA, ADCSRA_ADPS2);
	SET_BIT(ADCSRA, ADCSRA_ADPS1);
	CLR_BIT(ADCSRA, ADCSRA_ADPS0);
#elif ADC_Division_Factor == Division_Factor_8
	CLR_BIT(ADCSRA, ADCSRA_ADPS2);
	SET_BIT(ADCSRA, ADCSRA_ADPS1);
	SET_BIT(ADCSRA, ADCSRA_ADPS0);
#elif ADC_Division_Factor == Division_Factor_16
	SET_BIT(ADCSRA, ADCSRA_ADPS2);
	CLR_BIT(ADCSRA, ADCSRA_ADPS1);
	CLR_BIT(ADCSRA, ADCSRA_ADPS0);
#elif ADC_Division_Factor == Division_Factor_32
	SET_BIT(ADCSRA, ADCSRA_ADPS2);
	CLR_BIT(ADCSRA, ADCSRA_ADPS1);
	SET_BIT(ADCSRA, ADCSRA_ADPS0);
#elif ADC_Division_Factor == Division_Factor_64
	SET_BIT(ADCSRA, ADCSRA_ADPS2);
	SET_BIT(ADCSRA, ADCSRA_ADPS1);
	CLR_BIT(ADCSRA, ADCSRA_ADPS0);
#elif ADC_Division_Factor == Division_Factor_128
	SET_BIT(ADCSRA, ADCSRA_ADPS2);
	SET_BIT(ADCSRA, ADCSRA_ADPS1);
	SET_BIT(ADCSRA, ADCSRA_ADPS0);
#else
#error	"Wrong ADC Division Factor selection"
#endif

	//ADC_Auto_Trigger from ADC_Config.h
#if ADC_Auto_Trigger == ADC_Auto_Trigger_Disable
	CLR_BIT(ADCSRA, ADCSRA_ADATE);
#elif ADC_Auto_Trigger == ADC_Auto_Trigger_Enable
	SET_BIT(ADCSRA, ADCSRA_ADATE);
	// ADC_Auto_Trigger_Source_Selections
#if ADC_Auto_Trigger_Source_Selections == Free_Running_mode
	CLR_BIT(SFIOR,SFIOR_ADTS2);
	CLR_BIT(SFIOR,SFIOR_ADTS1);
	CLR_BIT(SFIOR,SFIOR_ADTS0);
#elif ADC_Auto_Trigger_Source_Selections == Analog_Comparator
	CLR_BIT(SFIOR,SFIOR_ADTS2);
	CLR_BIT(SFIOR,SFIOR_ADTS1);
	SET_BIT(SFIOR,SFIOR_ADTS0);
#elif ADC_Auto_Trigger_Source_Selections == External_Interrupt_Request_0
	CLR_BIT(SFIOR,SFIOR_ADTS2);
	SET_BIT(SFIOR,SFIOR_ADTS1);
	CLR_BIT(SFIOR,SFIOR_ADTS0);
#elif ADC_Auto_Trigger_Source_Selections == Timer_Counter0_Compare_Match
	CLR_BIT(SFIOR,SFIOR_ADTS2);
	SET_BIT(SFIOR,SFIOR_ADTS1);
	SET_BIT(SFIOR,SFIOR_ADTS0);
#elif ADC_Auto_Trigger_Source_Selections == Timer_Counter0_Overflow
	SET_BIT(SFIOR,SFIOR_ADTS2);
	CLR_BIT(SFIOR,SFIOR_ADTS1);
	CLR_BIT(SFIOR,SFIOR_ADTS0);
#elif ADC_Auto_Trigger_Source_Selections == Timer_Counter_Compare_Match_B
	SET_BIT(SFIOR,SFIOR_ADTS2);
	CLR_BIT(SFIOR,SFIOR_ADTS1);
	SET_BIT(SFIOR,SFIOR_ADTS0);
#elif ADC_Auto_Trigger_Source_Selections == Timer_Counter1_Overflow
	SET_BIT(SFIOR,SFIOR_ADTS2);
	SET_BIT(SFIOR,SFIOR_ADTS1);
	CLR_BIT(SFIOR,SFIOR_ADTS0);
#elif ADC_Auto_Trigger_Source_Selections == Timer_Counter1_Capture_Event
	SET_BIT(SFIOR,SFIOR_ADTS2);
	SET_BIT(SFIOR,SFIOR_ADTS1);
	SET_BIT(SFIOR,SFIOR_ADTS0);
#else
#error	"Wrong ADC Auto Trigger Source selection"
#endif	// ADC_Auto_Trigger_Source_Selections
#else
#error	"Wrong ADC Enable Mode"
#endif	//ADC_Auto_Trigger from ADC_Config.h

	// ADC_Enable_Mode	 from ADC_Config.h
#if ADC_Enable_Mode == ADC_Enable_ATT
	SET_BIT(ADCSRA,ADCSRA_ADEN); // In Free Running Mode, write this bit to one to start the first conversion take the normal 13 ADC clock cycles
#elif ADC_Enable_Mode == ADC_Enable_OD
	CLR_BIT(ADCSRA,ADCSRA_ADEN);
#else
#error	"Wrong ADC Enable Mode"
#endif	// ADC_Enable_Mode	 from ADC_Config.h

}
//==================================================
u16 ADC_VidGetDigitalValue(u8 LOC_u8channel)
{
	u16 ADC_Conversion_RESULT;
	// to select A0-A7
	ADMUX &=(0b11100000);
	ADMUX |=(LOC_u8channel & 0b00011111);
	//Enable ADC Mode	 from ADC_Config.h
#if ADC_Enable_Mode == ADC_Enable_OD
	SET_BIT(ADCSRA,ADCSRA_ADEN);			//Turning the ADC on/Enable
	SET_BIT(ADCSRA,ADCSRA_ADSC); 	//First start conversion will take 25 ADC clock cycles instead of the normal 13.
	while(GET_BIT(ADCSRA,ADCSRA_ADIF) ==0); // This bit is set when an ADC conversion completes and the Data Registers are updated.
	ADC_Conversion_RESULT = ADC_u16;
	SET_BIT(ADCSRA,ADCSRA_ADIF);
	CLR_BIT(ADCSRA,ADCSRA_ADEN);		//Turning the ADC off
#elif ADC_Enable_Mode == ADC_Enable_ATT
	//SET_BIT(ADCSRA,ADCSRA_ADSC); 	//start conversion will take normal 13 ADC clock cycles.
	ADC_Conversion_RESULT = ADC_u16;
	//SET_BIT(ADCSRA,ADCSRA_ADIE);
#else
#error	"Wrong ADC Enable Mode"
#endif // for Enable ADC Mode	 from ADC_Config.h
	return ADC_Conversion_RESULT;
}
void ADC_VidInterrupt_Enable(void)
{
	SET_BIT(ADCSRA,ADCSRA_ADIE);
}
void ADC_VidStartConversionNonBlocking( u8 LOC_u8channel)
{
	//Clear ADMUX
	ADMUX &=(0b11100000);
	//Choose channel
	ADMUX |=(LOC_u8channel & 0b00011111);
	//Enable Interrupt
	SET_BIT(ADCSRA,ADCSRA_ADIE);
	//Start Conversion
	SET_BIT(ADCSRA,ADCSRA_ADSC);
}
//===========================================================
void __vector_16(void)	//ISR 16 for ADC //Interrupt Vectors in ATmega32 Datasheet Page. 42//
{
	//check pointer validation
	if (ADC_GPFunction != NULL)
	{
		ADC_GPFunction();
	}
}
