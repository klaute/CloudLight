/*
 * CloudLight.c
 *
 * Created: 22.09.2015 16:15:36
 *  Author: klaute - Kai Lauterbach - klaute@gmail.com
 */

/*****************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include "light_ws2812.h"

/*****************************************************************************/

#define LED_COUNT    10

#define COLOR_WHITE  16

/*****************************************************************************/

struct cRGB led[LED_COUNT];

/*****************************************************************************/

int main(void)
{

  //====================//

  uint8_t i;

  //====================//

#ifdef __AVR_ATtiny10__
  CCP    = 0xD8; // configuration change protection, write signature
  CLKPSR = 0;    // set cpu clock prescaler =1 (8Mhz) (attiny 4/5/9/10)

#else
  CLKPR = _BV(CLKPCE);
  CLKPR = 0; // set clock prescaler to 1 (attiny 25/45/85/24/44/84/13/13A)

#endif
  DDRB |= _BV(ws2812_pin);

  //====================//

  for (i = 0; i < LED_COUNT; i++)
  {
    led[i].r = COLOR_WHITE;
    led[i].g = COLOR_WHITE;
    led[i].b = COLOR_WHITE;
  }

  //====================//;

  while(1)
  {

    ws2812_sendarray((uint8_t *)&led[0], LED_COUNT  * 3); // Repeatedly send the colors to the led string.

    _delay_ms(50); // Issue reset and wait for 50 ms.

  }
}

/*****************************************************************************/
