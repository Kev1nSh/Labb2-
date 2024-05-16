/*

FIRST ASSIGNMENT!!

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

/*
    SECOND ASSIGNMENT!!

    #include <stdint.h>
    #include <stdio.h>

    volatile uint8_t* DDRB  = (volatile uint8_t*)0x24;
    volatile uint8_t* PortB = (volatile uint8_t*)0x25;
    volatile uint8_t* DDRD  = (volatile uint8_t*)0x2A;
    volatile uint8_t* PortD  = (volatile uint8_t*)0x2B;

    uint16_t i = 0;

    void setup() {

  // Set pin 7-4 (PD7-PD4) as an output
  *DDRD |= (0b00001111 << 2);
    }

    void loop() {
  i++;
  // Turn on leds in with separate patterns.
  if (i % 13 == 0) {
    *PortD |= (0b00000001 << 5);
    delay(50);
  }
  if (i % 29 == 0) {
    *PortD |= (0b00000001 << 4);
    delay(50);
  }
  if (i % 47 == 0) {
    *PortD |= (0b00000001 << 3);
    delay(50);
  }
  if (i % 71 == 0) {
    *PortD |= (0b00000001 << 2);
    delay(50);
  }

  *PortB = *PortD;

  // Turn off leds with reverse separate patterns.
  if (i % 13 == 0) {
    *PortD &= 0;
  }
  if (i % 29 == 0) {
    *PortD &= 0;
  }
  if (i % 47 == 0) {
    *PortD &= 0;
  }
  if (i % 71 == 0) {
    *PortD &= 0;
  }
  // PORTB gets PORTD.
  *PortB = *PortD;

  // Reset i to avoid overflow.
  if (i == 2222) {
    i = 0;
  }
}


*/

/*
    THIRD ASSIGNMENT!!

    #include <stdint.h>
    #include <stdio.h>

    volatile uint8_t* DDRN  = (volatile uint8_t*)0x24;
    volatile uint8_t* PortB = (volatile uint8_t*)0x25;
    volatile uint8_t* DDRD  = (volatile uint8_t*)0x2A;
    volatile uint8_t* PortD  = (volatile uint8_t*)0x2B;
    volatile uint8_t* PinD = (volatile uint8_t*)0x29;



    void setup() {

  // Set pin 7-4 (PD7-PD4) as an output
  *DDRD |= (0b00001111 << 2);
}

    void loop() {
  uint16_t i = 0;

  i++;
  // Turn on leds in with separate patterns.
  if(((*PinD & 0b00100000)!= 0 )&& i & 13 == 0){
    *PortD |= (0b00000001 << 5);
    delay(50);
  }
  if(((*PinD & 0b00010000)!= 0 ) && i % 29 == 0) {
    *PortD |= (0b00000001 << 4);
    delay(50);
  }
  if(((*PinD & 0b00001000) !=0) && i % 47 == 0) {
    *PortD |= (0b00000001 << 3);
    delay(50);
  }
  if (((*PinD & 0b00000100) != 0) && i % 71 == 0) {
    *PortD |= (0b00000001 << 2);
    delay(50);
  }
  *PortB = *PortD;

  // Turn off leds with reverse separate patterns.
  if (i % 13 == 0) {
    *PortD &= 0;
  }
  if (i % 29 == 0) {
    *PortD &= 0;
  }
  if (i % 47 == 0) {
    *PortD &= 0;
  }
  if (i % 71 == 0) {
    *PortD &= 0;
  }
  // PORTB gets PORTD.
  *PortB = *PortD;

  delay(50);

  // Reset i every now and then.
  if (i == 1000){
    i = 0;
  }
}


*/

/*
  Fourth Assignment!!

#include <stdint.h>

#define THREESEC 3000
#define iFREQ 40
#define DEBOUNCETIME 7

volatile uint8_t* ddrb  = (volatile uint8_t*)0x24;
volatile uint8_t* portb = (volatile uint8_t*)0x25;
volatile uint8_t* ddrd  = (volatile uint8_t*)0x2A;
volatile uint8_t* portd = (volatile uint8_t*)0x2B;
volatile uint8_t* pind  = (volatile uint8_t*)0x29;

uint32_t iPreviousTime;
uint32_t lastGLedTime;
uint32_t lastDebounceTime;
uint32_t currentTime;
uint16_t i = 0;
uint8_t clickCount = 0;
bool tenClicksFlag = false;
uint8_t previousState = 0b00000000;
uint8_t prePreviousState = 0b00000000;
uint8_t buttonState = 0;

uint8_t debounce() {
  uint8_t debounceCheck = *pind;
  currentTime = millis();
  if (currentTime - lastDebounceTime >= DEBOUNCETIME) {
    if (previousState != debounceCheck) {
    lastDebounceTime = currentTime;
    prePreviousState = previousState;
    previousState = debounceCheck;
    }
  }
  return debounceCheck;
}

// Listens for an change in input.
bool changeListener() {
  uint8_t currentRead = *pind;
  if (currentRead != previousState) {
    return true;
  }
  return false;
}

// Listens if either 0, 1 or several buttons are pressed.
uint8_t buttonListener() {
  uint8_t buttonCount = 0;
  uint8_t debouncedInput = debounce();
  
  if (debouncedInput & 0b00100000) {
    buttonCount++;
    if (!(prePreviousState & 0b00100000))
      clickCount++;
  }
  if (debouncedInput & 0b00010000) {
    buttonCount++;
    if (!(prePreviousState & 0b00010000))
      clickCount++;
  }
  if (debouncedInput & 0b00001000) {
    buttonCount++;
    if (!(prePreviousState & 0b00001000))
      clickCount++;
  }
  if (debouncedInput & 0b00000100) {
    buttonCount++;
    if (!(prePreviousState & 0b00000100))
      clickCount++;
  }
  if (buttonCount > 1) 
    return 2;
  if (buttonCount == 1) 
    return 1;
  return 0;
}

void setup() {
  // Set pin 10-13 (PB1-PB5) as outputs.
  *ddrb |= (0b00111110);
  iPreviousTime = lastGLedTime = lastDebounceTime = millis();
}

void loop() {
  currentTime = millis();

  // Increment i at set intervall.
  if (currentTime - iPreviousTime >= iFREQ) {
    iPreviousTime = currentTime;
    i++;
  }

  // Increment i at set interval.
  if (currentTime - iPreviousTime >= iFREQ) {
    iPreviousTime = currentTime;
    i++;
  }

   // Check for button state changes to update buttonState.
  if (changeListener()) {
    buttonState = buttonListener();
  }

  if (tenClicksFlag) {
    if (currentTime - lastGLedTime < THREESEC) {
      *portd |= (0b00000010);
    } else {
      *portd &= ~(0b00000010);
      tenClicksFlag = false;
    }
  } else if (buttonState == 2) {
    *portd |= (0b00000010);
  } else {
    *portd &= ~(0b00000010);
  }

  // Logic to count clicks and trigger the ten clicks behavior.
  if (clickCount >= 10) {
    clickCount = 0; 
    tenClicksFlag = true; 
    lastGLedTime = currentTime; 
    *portd |= (0b00000010);
  }

  // PORTB gets PORTD.
  *portb = *portd;

  // Turn LEDs on with separate patterns when corresponding button is held down.
  // Pin 10
  if (((*pind & 0b00000100) != 0) && i %  37 == 0) {
    *portd |= (0b00000100);
  }
  // Pin 11
  if (((*pind & 0b00001000) != 0) && i % 41 == 0) {
    *portd |= (0b00001000);
  }
  // Pin 12
  if (((*pind & 0b00010000) != 0) && i % 43 == 0) {
    *portd |= (0b00010000);
  }
  // Pin 13
  if (((*pind & 0b00100000) != 0) && i % 47 == 0) {
    *portd |= (0b00100000);
  }

  *portb = *portd;

  // Turn LEDs off with reverse separate patterns.
  // Pin 10
  if (i % 37 == 0) {
    *portd &= ~(0b00000100);  
  }
  // Pin 11
  if (i % 41 == 0) {
    *portd &= ~(0b00001000);
  }
  // Pin 12
  if (i % 43 == 0) {
    *portd &= ~(0b00010000);
  }
  // Pin 13
  if (i % 47 == 0) {
    *portd &= ~(0b00100000);  
  }

  *portb = *portd;

  // Reset i every now and then.
  if (i == 1027) {
    i = 0;
  }

}


*/