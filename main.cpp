/*

#include <stdio.h>
#include <stdint.h>


volatile uint8_t* DDRB = (volatile uint8_t*)0x24;
volatile uint8_t* PortB = (volatile uint8_t*)0x25;

volatile uint8_t* DDRD = (volatile uint8_t*)0x2A;
volatile uint8_t* PortD = (volatile uint8_t*)0x2B;

#define TIMER_MAX 6

int timer[TIMER_MAX] = {7000,1000,3000,4000,5000,6000};
int i = -1;

void setup()
{
  // Set pin 13 (PB5) as an output
  *DDRB |= (0b00000001 << 5);

  // Set pin 7 (PD7) as an output
  *DDRD |= (0b00000001 <<7);
  
}

void loop()
{
  i++;
  if (i == TIMER_MAX) { i = 0; }

  // Set all portd high (turn on the LED)
  *portd = ~*portd;
  delay(timer[i]);

  *portb =*portd;

  // Set all portd low (turn off the LED)
  *portd = 0;

  delay(timer[i]);

  *portb =*portd;
  
  
}

*/