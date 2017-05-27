#include </home/pi/SeniorProject/wiringPi/wiringPi/wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <softPwm.h>
#include <time.h>
#define	ALSB 0
#define	B 1
#define	C 2
#define	DMSB 3
#define	DATA 4
#define	EN1 5
#define	EN2 6

void PinPwmInit(int pinNum)
{
	srand(time(NULL));   // should only be called once
	  softPwmCreate(DATA, 0, 30);
}

// The angle goes from 0 to 180
void SetPwmAngle(int pinNum, int angle)
{
	
	
    softPwmWrite(DATA, angle);
}

int main (void)
{
  printf ("Raspberry Pi blink\n") ;

  wiringPiSetup () ;
  pinMode (ALSB, OUTPUT) ;
  pinMode (B, OUTPUT) ;
  pinMode (C, OUTPUT) ;
  pinMode (DMSB, OUTPUT) ;
  pinMode (DATA, OUTPUT) ;
  pinMode (EN1, OUTPUT) ;
  pinMode (EN2, OUTPUT) ;




  PinPwmInit(DATA);
  
  int i = 0;
  int b;
  for (i = 0; i < 2; i++)
  {
	  if (i == 0)
	  {
		  digitalWrite(EN1, 1);
		  digitalWrite(EN2, 0);
		  		  delay (1000);	
      }
      else
      {
		  digitalWrite(EN1, 0);
		  digitalWrite(EN2, 1);
		  		  delay (1000);	
		  i = 0; 		  
	  }
	      b = rand() % 15;
		  printf("%d \n", b);
		  digitalWrite (DMSB, (0x8 & b) == 8 ? HIGH : LOW);
		  printf("%d ", (0x8 & b) == 8 ? HIGH : LOW);
		  digitalWrite (C, (0x4 & b) == 4 ? HIGH : LOW);	// On
		  printf("%d ", (0x4 & b) == 4 ? HIGH : LOW);
		  digitalWrite (B, (0x2 & b) == 2 ? HIGH : LOW);	// On
		  printf("%d ", (0x2 & b) == 2 ? HIGH : LOW);
		  digitalWrite (ALSB, (0x1 & b) == 1 ? HIGH : LOW);
		  printf("%d \n", (0x1 & b) == 1 ? HIGH : LOW);
		  delay (2000);	
		  SetPwmAngle(DATA, 2);
		  delay (2000);		// mS
	  
	  

		  b = rand() % 15;
		  printf("%d \n", b);
		  digitalWrite (DMSB, (0x8 & b) == 8 ? HIGH : LOW);
		  printf("%d ", (0x8 & b) == 8 ? HIGH : LOW);
		  digitalWrite (C, (0x4 & b) == 4 ? HIGH : LOW);	// On
		  printf("%d ", (0x4 & b) == 4 ? HIGH : LOW);
		  digitalWrite (B, (0x2 & b) == 2 ? HIGH : LOW);	// On
		  printf("%d ", (0x2 & b) == 2 ? HIGH : LOW);
		  digitalWrite (ALSB, (0x1 & b) == 1 ? HIGH : LOW);
		  printf("%d \n", (0x1 & b) == 1 ? HIGH : LOW);
		  delay (2000);	
		  SetPwmAngle(DATA, 28);
		  delay (1000);		// mS
  }
  //for (i = 5; i <= 30; i + 5)
  //{
   // SetPwmAngle(DATA, i);
   // delay (1000);		// mS
  //}
  return 0;
}
