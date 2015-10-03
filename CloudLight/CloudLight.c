/*
 * CloudLight.c
 *
 * Created: 22.09.2015 16:15:36
 *  Author: klaute - Kai Lauterbach - klaute@gmail.com
 */

/*****************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdlib.h>

#include <util/delay.h>

#include "light_ws2812.h"

/*****************************************************************************/

#define LED_COUNT    10

#define COLOR_WHITE  10

#define RAND_NUM_TIMEOUT 20 // multiplied with 50 ms + the time to update the LED strip

#define NO_RAND_NUM 255

/*****************************************************************************/

struct cRGB led[1];

/*****************************************************************************/

int main(void)
{

  //====================//

  uint8_t i;
  uint8_t tmp = 0;
  uint8_t gen_new_rand_num_timeout = RAND_NUM_TIMEOUT;
  uint8_t rand_num = NO_RAND_NUM;
  uint8_t anim = 0;

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

  while(1)
  {

    if (gen_new_rand_num_timeout == 0 && rand_num == NO_RAND_NUM)
    {
      gen_new_rand_num_timeout = RAND_NUM_TIMEOUT + (rand() % 100);

      rand_num = rand() % LED_COUNT;
      if (rand_num >= LED_COUNT)
        rand_num = NO_RAND_NUM;
    }

    if (rand_num < LED_COUNT)
    {
      /**/
      if (anim == 0)
        tmp = -1;
      else if (anim == 1)
        tmp = -2;
      else if (anim == 2)
        tmp = -4;
      else if (anim == 3)
        tmp = -2;
      else if (anim == 4)
        tmp = 2;
      else if (anim == 5)
        tmp = 4;
      else if (anim == 6)
        tmp = 2;
      else if (anim == 7)
        tmp = 1;
      else if (anim == 9)
        tmp = -1;
      else if (anim == 10)
        tmp = -2;
      else if (anim == 11)
        tmp = 2;
      else if (anim == 12)
        tmp = -2;
      else if (anim == 14)
        tmp = 4;
      else
      {
        anim = 0;
        rand_num = NO_RAND_NUM;
      }
      /**/

      anim++;
    }

    if (rand_num == NO_RAND_NUM)
      gen_new_rand_num_timeout--;

    for (i = 0; i < LED_COUNT; i++)
    {
      if (i != rand_num)
      {

        led[0].r = COLOR_WHITE;
        led[0].g = COLOR_WHITE;
        led[0].b = COLOR_WHITE;

      } else {

        led[0].r += tmp;
        led[0].g = led[0].r;
        led[0].b = led[0].r;

      }

      ws2812_sendarray((uint8_t *)&led[0], 3); // Repeatedly send the colors to the led string.

    }

    _delay_ms(50); // Issue reset and wait for 50 ms.

  }
}

/*****************************************************************************/

