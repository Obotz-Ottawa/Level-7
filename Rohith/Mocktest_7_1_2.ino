#include<avr/io.h>
#include<avr/interrupt.h>
#include<avr/interrupt.h>
#define setbit(x,y) (x|=y)
#define clearbit(x,y)(x&=~y)
#define checkbit(x,y) ((x) & (y))
#define bitn(p) (0x01 << (p))
int i=0;
long result,average;
int main(void)
{
  DDRB=0b1111111;
  DDRC=0b1111111;
  PORTB=0b11111111;
  PORTC=0b00000000;
  while(1)
  {
    ADMUX=0x40; //keypad setup
    ADCSRA=0xC7;
   while(checkbit(ADCSRA, bitn(ADSC)));
   result = result + ADCW;
   i++;
   if(i>99){
    average=result/100;
    Serial.println(average);
    if(average==1)
    {
    for(int i=1; i<=300;i++)
    {
    PORTC=0b00000010;
    PORTB=0b11101101;
    _delay_ms(1);
    PORTC=0b00000100;
    PORTB=0b11100000;
    _delay_ms(1);
    PORTC=0b00001000;
    PORTB=0b11101111;
    _delay_ms(1);
    }
    for(int i=1; i<=300;i++)
    {
    PORTC=0b00000010;
    PORTB=0b11100010;
    _delay_ms(1);
    PORTC=0b00000100;
    PORTB=0b11101010;
    _delay_ms(1);
    PORTC=0b00001000;
    PORTB=0b11101000;
    _delay_ms(1);
    }
     for(int i=1; i<=300;i++)
    {
    PORTC=0b00000010;
    PORTB=0b11101010;
    _delay_ms(1);
    PORTC=0b00000100;
    PORTB=0b11101010;
    _delay_ms(1);
    PORTC=0b00001000;
    PORTB=0b11100000;
    _delay_ms(1);
    }
     for(int i=1; i<=300;i++)
    {
    PORTC=0b00000010;
    PORTB=0b11111000;
    _delay_ms(1);
    PORTC=0b00000100;
    PORTB=0b11111011;
    _delay_ms(1);
    PORTC=0b00001000;
    PORTB=0b11100000;
    _delay_ms(1);
    }
         for(int i=1; i<=300;i++)
    {
    PORTC=0b00000010;
    PORTB=0b11101000;
    _delay_ms(1);
    PORTC=0b00000100;
    PORTB=0b11101010;
    _delay_ms(1);
    PORTC=0b00001000;
    PORTB=0b11100010;
    _delay_ms(1);
    }
    }
    result=0;
    average=0;
    i=0;
   }
  }
}
