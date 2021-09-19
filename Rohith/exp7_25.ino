#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#define setbit(x,y) (x|=y)
#define clearbit(x,y)(x&=~y)
#define checkbit(x,y) ((x) & (y))
#define bitn(p) (0x01 << (p))
char data;
int count = 0;
int right_hip, count_angle, right_foot, count_angle1, left_hip, count_angle2, left_foot, count_angle3, left_hand, count_angle4, right_hand, count_angle5, neck, count_angle6;
int main(void) {
  Serial.begin(2000000);
  DDRD = 0xFC;
  DDRB=0xFF;
  UCSR0A=0x00;
  UCSR0B=0x10;
  UCSR0C=0x06;
  UBRR0H=0x00;
  UBRR0L=(16000000UL/(16UL*9600))-1;
  TCNT1 = 0x00;
  OCR1A = 21;
  TCCR1A = 0x00;
  TCCR1B = 0x0A;
  TIMSK1 = 0x02;
  SREG = 0x80;
  homeposition();
  compare();
  while (1)//while loop
  {
    while (!(UCSR0A & (1 << RXC0)));
    data = UDR0;
    if (data == '1')
    {
      foot_tap();
    }
    else if (data == '2')
    {
      leg_sweep();
    }
    else if (data == '3')
    {
      hips_out();
    }
    else if (data == '4')
    {
      hips_in();
    }
    else if (data == '5')
    {
      hand_up();
    }
    else if (data == '6')
    {
      robot_march();
    }
    if (data == '0')
    {
      homeposition();
      compare();
    }
  }
}
void foot_tap()
{
  for (right_foot = 70; right_foot <= 90; right_foot++)
  {
    compare();
  }
  _delay_ms(20);
  for (right_foot = 90; right_foot >= 70; right_foot--)
  {
    compare();
  }
  _delay_ms(20);
  for (left_foot = 90; left_foot >= 70; left_foot--)
  {
    compare();
  }
  _delay_ms(20);
  for (left_foot = 70; left_foot <= 90; left_foot++)
  {
    compare();
  }
  _delay_ms(20);
}
void leg_sweep()
{
  for (left_hip = 70; left_hip <= 90; left_hip++)
  {
    compare();
  }
  _delay_ms(20);
  for (left_hip = 90; left_hip >= 70; left_hip--)
  {
    compare();
  }
  _delay_ms(20);
  for (right_hip = 90; right_hip <= 110; right_hip++)
  {
    compare();
  }
  _delay_ms(20);
  for (right_hip = 110; right_hip >= 90; right_hip--)
  {
    compare();
  }
  _delay_ms(20);
}
void hips_out()
{
  for (int i = 1; i <= 20; i++)
  {
    right_hip--;
    left_hip++;
    compare();
  }
  _delay_ms(20);
  for (int i = 1; i <= 20; i++)
  {
    right_hip++;
    left_hip--;
    compare();
  }
  _delay_ms(20);
}
void hips_in()
{
  for (int i = 1; i <= 20; i++)
  {
    right_hip++;
    left_hip--;
    compare();
  }
  _delay_ms(20);
  for (int i = 1; i <= 20; i++)
  {
    right_hip--;
    left_hip++;
    compare();
  }
  _delay_ms(20);
}
void hand_up()
{
  for (right_hand = 40; right_hand <= 70; right_hand++)
  {
    compare();
  }
  _delay_ms(20);
  for (right_hand = 70; right_hand >= 40; right_hand--)
  {
    compare();
  }
  _delay_ms(20);
  for (left_hand = 110; left_hand <= 140; left_hand++)
  {
    compare();
  }
  _delay_ms(20);
  for (left_hand = 140; left_hand >= 110; left_hand--)
  {
    compare();
  }
  _delay_ms(20);
}
void robot_march()
{
  for (int i = 1; i <= 50; i++)
  {
    right_foot--;
    compare();
  }
  _delay_ms(20);
  for (int i = 1; i <= 40; i++)
  {
    left_hand++;
    compare();
  }
  _delay_ms(20);
  for (int i = 1; i <= 50; i++)
  {
    right_foot++;
    compare();
  }
  _delay_ms(20);
  for (int i = 1; i <= 40; i++)
  {
    left_hand--;
    compare();
  }
  _delay_ms(20);
  for (int i = 1; i <= 50; i++)
  {
    left_foot++;
    compare();
  }
  _delay_ms(20);
  for (int i = 1; i <= 40; i++)
  {
    left_hand--;
    compare();
  }
  _delay_ms(20);
  for (int i = 1; i <= 50; i++)
  {
    left_foot--;
    compare();
  }
  _delay_ms(20);
  for (int i = 1; i <= 40; i++)
  {
    left_hand++;
    compare();
  }
  _delay_ms(20);
}
void compare()
{
  count_angle = right_hip + 46;
  count_angle1 = right_foot + 46;
  count_angle2 = left_hip + 46;
  count_angle3 = left_foot + 46;
  count_angle4 = left_hand + 46;
  count_angle5 = right_hand + 46;
  count_angle6 = neck + 46;
  _delay_us(1500);
}
void homeposition()
{
  right_hip = 90;
  right_foot = 90;
  left_hip = 90;
  left_foot = 90;
  left_hand = 140;
  right_hand = 40;
  neck = 90;
}
ISR(TIMER1_COMPA_vect)
{
  count++;
  if (count <= count_angle)
  {
    setbit(PORTD, bitn(4));
  }
  else if ((count > count_angle) && (count < 1818))
  {
    clearbit(PORTD, bitn(4));
  }
  else if (count >= 1818)
  {
    count = 0;
  }
  if (count <= count_angle1)
  {
    setbit(PORTD, bitn(5));
  }
  else if ((count > count_angle1) && (count < 1818))
  {
    clearbit(PORTD, bitn(5));
  }
  if (count <= count_angle2)
  {
    setbit(PORTD, bitn(6));
  }
  else if ((count > count_angle2) && (count < 1818))
  {
    clearbit(PORTD, bitn(6));
  }
  if (count <= count_angle3)
  {
    setbit(PORTD, bitn(7));
  }
  else if ((count > count_angle3) && (count < 1818))
  {
    clearbit(PORTD, bitn(7));
  }
  if (count <= count_angle4)
  {
    setbit(PORTD, bitn(3));
  }
  else if ((count > count_angle4) && (count < 1818))
  {
    clearbit(PORTD, bitn(3));
  }
  if (count <= count_angle5)
  {
    setbit(PORTD, bitn(2));
  }
  else if ((count > count_angle5) && (count < 1818))
  {
    clearbit(PORTD, bitn(2));
  }
  if (count <= count_angle6)
  {
    setbit(PORTD, bitn(0));
  }
  else if ((count > count_angle6) && (count < 1818))
  {
    clearbit(PORTD, bitn(0));
  }
}
