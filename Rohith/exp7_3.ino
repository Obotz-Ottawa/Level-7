#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#define setbit(x,y) (x|=y)
#define clearbit(x,y)(x&=~y)
#define checkbit(x,y) ((x) & (y))
#define bitn(p) (0x01 << (p))
int count,angle,count_angle;
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
    for(angle=90;angle<=150;angle++)
    {
      compare();
    }
    _delay_ms(1000);
    for(angle=150;angle>=90;angle--)
    {
      compare_slow();
    }
  }
}
void compare()
{
  count_angle=angle+46;
  _delay_us(3000);
 }
 void compare_slow()
{
  count_angle=angle+46;
  _delay_us(35000);
 }
 void homeposition()
 {
  angle=90;
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
}
