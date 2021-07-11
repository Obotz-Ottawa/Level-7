#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#define setbit(x,y) (x|=y)
#define clearbit(x,y)(x&=~y)
#define checkbit(x,y) ((x) & (y))
#define bitn(p) (0x01 << (p))
int count,angle,angle1,count_angle,count_angle1;
int main(void) {
  Serial.begin(2000000);
  DDRD = 0xFF;//initializes DDRD
  TCNT1= 0x00;
  OCR1A= 21;
  TCCR1A = 0x00;//initializes TCCR2A & TCCR0A to normal mode
  TCCR1B = 0x0A;//sets prescaler to 64
  TIMSK1=0x02;
  SREG=0x80;
  homeposition();
  _delay_ms(2000);
  while (1)//while loop
  {
    Serial.print("uploaded");
    for(int i=1;i<=90;i++)
    {
      angle++;
      angle1++;
      compare();
    }
    _delay_ms(1000);
    for(int j=1; j <=90; j++)
    {
      angle--;
      angle1--;
      compare();
    }
  }
}
void compare()
{
  count_angle=angle+46;
  count_angle1=angle1+46;
  _delay_us(5000);
 }
 void homeposition()
 {
  angle=90;
  angle1=90;
 }
ISR(TIMER1_COMPA_vect)
{
  count++;
  if(count <= count_angle)
  {
    setbit(PORTD,bitn(4));
  }
  else if ((count>count_angle)&&(count<1818))
  {
    clearbit(PORTD,bitn(4));
  }
  else if (count>=1818)
  {
    count=0;
  }
  if(count <= count_angle)
  {
    setbit(PORTD,bitn(5));
  }
  else if ((count>count_angle)&&(count<1818))
  {
    clearbit(PORTD,bitn(5));
  }
}
