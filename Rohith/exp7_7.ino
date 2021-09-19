#include<avr/io.h>
#include<avr/interrupt.h>

int main(void)
{
  DDRB=0b1111111;
  DDRC=0b1111111;
  PORTB=0b11111111;
  PORTC=0b00000000;
  while(1)
  {
    for(int j=0; j<=4; j++)
    {
      PORTB=~(1<<(j));
      for(int i=0; i<=4; i++)
      {
         PORTC=1<<(i);
        _delay_ms(50);
      }
    }
  }
}
