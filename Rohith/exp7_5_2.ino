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
    PORTC=0b00000001;
    PORTB=0b11111101;
    _delay_ms(10);
    PORTC=0b00010000;
    PORTB=0b11111011;
    _delay_ms(10);
  }
}
