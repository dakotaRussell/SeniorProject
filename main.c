#include </home/pi/SeniorProject/wiringPi/wiringPi/wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define	LED	1
int main (void)
{
  printf ("Raspberry Pi blink\n") ;

  wiringPiSetup () ;
  pinMode (LED, OUTPUT) ;

  for (;;)
  {
    digitalWrite (LED, HIGH) ;	// On
    delay (500) ;		// mS
    digitalWrite (LED, LOW) ;	// Off
    delay (500) ;
  }
  return 0 ;
}
