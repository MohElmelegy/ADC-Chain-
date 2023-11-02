#ifndef _ADC_REGISTER_H_
#define _ADC_REGISTER_H_

//------------------AVR ATmega32------------------------
#define ADCSRA		*((volatile u8*)0x26)  //ADC Control and Status Register A – ADEN ADSC ADATE ADIF ADIE ADPS2 ADPS1 ADPS0
#define ADMUX		*((volatile u8*)0x27)	// ADC Multiplexer Selection Register – REFS1 REFS0 ADLAR MUX4 MUX3 MUX2 MUX1 MUX0
//The ADC Data Register – ADCL and ADCH
#define ADCH			*((volatile u8*)0x25)		//ADC Data Register High Byte
#define ADCL			*((volatile u8*)0x24)		//ADC Data Register Low Byte
#define ADC_u16		*((volatile u16*)0x24)  // 16 bit to contain both ADCL-ADCH , read value at once
// ADC = ((VPOS – VNEG) * GAIN * 512) / VREF
//Special FunctionIO Register –SFIOR
#define SFIOR			*((volatile u8*)0x50) // ADTS2 ADTS1 ADTS0 – ACME PUD PSR2 PSR10
// ------------------------------------------------------------------------
void __vector_16(void)  __attribute__((signal));	//16 for ADC //Interrupt Vectors in ATmega32 Datasheet Page. 42//

#endif 	//_ADC_REGISTER_H_ //
