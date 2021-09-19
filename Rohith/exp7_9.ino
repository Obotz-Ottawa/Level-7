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
    PORTC=0b00000100;
    PORTB=0b11111011;
    _delay_ms(100);
    for(int i=1; i<=30;i++)
    {
    PORTC=0b00000010;
    PORTB=0b11110001;
    _delay_ms(1);
    PORTC=0b00000100;
    PORTB=0b11110101;
    _delay_ms(1);
    PORTC=0b00001000;
    PORTB=0b11110001;
    _delay_ms(1);
    }
    for(int i=1; i<=30;i++)
    {
    PORTC=0b00000001;
    PORTB=0b11100000;
    _delay_ms(1);
    PORTC=0b00000010;
    PORTB=0b11101110;
    _delay_ms(1);
    PORTC=0b00000100;
    PORTB=0b11101110;
    _delay_ms(1);
    PORTC=0b00001000;
    PORTB=0b11101110;
    _delay_ms(1);
    PORTC=0b00010000;
    PORTB=0b11100000;
    _delay_ms(1);
    }
        for(int i=1; i<=30;i++)
    {
    PORTC=0b00000010;
    PORTB=0b11110001;
    _delay_ms(1);
    PORTC=0b00000100;
    PORTB=0b11110101;
    _delay_ms(1);
    PORTC=0b00001000;
    PORTB=0b11110001;
    _delay_ms(1);
    }
  }
}
