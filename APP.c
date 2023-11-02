/*
 * APP.c
 *
 * Created: 10/31/2023
 *  Author: Mohamed SAmi
 */
#define F_CPU 8000000
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "ADC_Interface.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#define clear 0b00000001
#define QUEUE_SIZE 100
int reading1 = 0;
int reading2 = 0;

u8 flag = 0;

void ADC_Interrupt(void);

typedef struct
{
  int buffer[QUEUE_SIZE];
  int head;
  int tail;
} queue_buffer_t;

void queue_buffer_init(queue_buffer_t *buffer)
{
  buffer->head = 0;
  buffer->tail = 0;
}

int queue_buffer_is_full(queue_buffer_t *buffer)
{
  return (buffer->head == buffer->tail + 1) || (buffer->head == 0 && buffer->tail == QUEUE_SIZE - 1);
}

int queue_buffer_is_empty(queue_buffer_t *buffer)
{
  return buffer->head == buffer->tail;
}

void queue_buffer_enqueue(queue_buffer_t *buffer, int data)
{
  if (queue_buffer_is_full(buffer))
  {
    return;
  }

  buffer->buffer[buffer->tail] = data;
  buffer->tail = (buffer->tail + 1) % QUEUE_SIZE;
}

int queue_buffer_dequeue(queue_buffer_t *buffer)
{
  if (queue_buffer_is_empty(buffer))
  {
    return -1;
  }

  int data = buffer->buffer[buffer->head];
  buffer->head = (buffer->head + 1) % QUEUE_SIZE;

  return data;
}

/*create two Queue Buffer*/
queue_buffer_t buffer1;
queue_buffer_t buffer2;

void ADC_Interrupt(void)
{
  if (flag == 0)
  {
    reading1 = ADC_VidGetDigitalValue(0);
    reading1 = (reading1 * 5000UL) / 1024;
    reading1 = reading1 / 10;
    queue_buffer_enqueue(&buffer1, reading1);
    ADC_VidStartConversionNonBlocking(1);
    flag = 1;
  }

  else if (flag == 1)
  {
    reading2 = ADC_VidGetDigitalValue(1);
    reading2 = (reading2 * 5000UL) / 1024;
    reading2 = reading2 / 10;
    queue_buffer_enqueue(&buffer2, reading2);
    ADC_VidStartConversionNonBlocking(0);
    flag = 0;
  }
}

int main(void)
{
  LCD_VidInit();
  ADC_VidInit();
  sei();
  ADC_VidInterrupt_Enable();
  LCD_ClearDisplay();
  _delay_ms(2);
  LCD_VidSetPosition(0, 0);
  LCD_VidWriteString("The Sys init");
  _delay_ms(500);
  /*Pass Local callback*/
  ADC_SetCallBack(ADC_Interrupt);
  ADC_VidStartConversionNonBlocking(0);
  /*Init the two Queue Buffer*/
  queue_buffer_init(&buffer1);
  queue_buffer_init(&buffer2);

  while (1)
  {
    LCD_ClearDisplay();
    LCD_VidSetPosition(0, 0);
    LCD_VidWriteNumber(queue_buffer_dequeue(&buffer1));
    LCD_VidSetPosition(1, 0);
    LCD_VidWriteNumber(queue_buffer_dequeue(&buffer2));
    _delay_ms(500);
  }
}
