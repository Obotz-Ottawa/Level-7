#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#define setbit(x,y) (x|=y)
#define clearbit(x,y)(x&=~y)
#define checkbit(x,y) ((x) & (y))
#define bitn(p) (0x01 << (p))
int count=0;
int right_hip,count_angle,right_foot,count_angle1,left_hip,count_angle2,left_foot,count_angle3,left_hand,count_angle4,right_hand,count_angle5,neck,count_angle6;
int main(void) {
  Serial.begin(2000000);
  DDRD = 0xFF;
  TCNT1= 0x00;
  OCR1A= 21;
  TCCR1A = 0x00;
  TCCR1B = 0x0A;
  TIMSK1=0x02;
  SREG=0x80;
  homeposition();
  compare();
  while (1)//while loop
  {
    Serial.print("uploaded");
        _delay_ms(10);
      for(int i=1;i<=45 ;i++)
    {
      neck++;
      right_foot++;
      compare();
    }
        _delay_ms(20);
        homeposition();
        _delay_ms(20);
          for(int i=1;i<=45 ;i++)
    {
      neck--;
      left_foot--;
      compare();
    }
        _delay_ms(20);
        homeposition();
        _delay_ms(20);
}
}
void compare()
{
  count_angle=right_hip+46;
  count_angle1=right_foot+46;
  count_angle2=left_hip+46;
  count_angle3=left_foot+46;
  count_angle4=left_hand+46;
  count_angle5=right_hand+46;
  count_angle6=neck+46;
  _delay_us(500);
 }
 void homeposition()
 {
  right_hip=90;
  right_foot=90;
  left_hip=90;
  left_foot=90;
  left_hand=140;
  right_hand=40;
  neck=90;
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
  if(count <= count_angle1)
  {
    setbit(PORTD,bitn(5));
  }
  else if ((count>count_angle1)&&(count<1818))
  {
    clearbit(PORTD,bitn(5));
  }
    if(count <= count_angle2)
  {
    setbit(PORTD,bitn(6));
  }
  else if ((count>count_angle2)&&(count<1818))
  {
    clearbit(PORTD,bitn(6));
  }
    if(count <= count_angle3)
  {
    setbit(PORTD,bitn(7));
  }
  else if ((count>count_angle3)&&(count<1818))
  {
    clearbit(PORTD,bitn(7));
  }
    if(count <= count_angle4)
  {
    setbit(PORTD,bitn(3));
  }
  else if ((count>count_angle4)&&(count<1818))
  {
    clearbit(PORTD,bitn(3));
  }
    if(count <= count_angle5)
  {
    setbit(PORTD,bitn(2));
  }
  else if ((count>count_angle5)&&(count<1818))
  {
    clearbit(PORTD,bitn(2));
  }
      if(count <= count_angle6)
  {
    setbit(PORTD,bitn(1));
  }
  else if ((count>count_angle6)&&(count<1818))
  {
    clearbit(PORTD,bitn(1));
  }
}