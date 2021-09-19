#include<avr/io.h> //setup
#include<util/delay.h>
#include<avr/interrupt.h>
#define setbit(x,y) (x|=y)
#define clearbit(x,y)(x&=~y)
#define checkbit(x,y) ((x) & (y))
#define bitn(p) (0x01 << (p))
int count = 0;
int right_hip, count_angle, right_foot, count_angle1, left_hip, count_angle2, left_foot, count_angle3, left_hand, count_angle4, right_hand, count_angle5, neck, count_angle6;
int i=0;
long result,average;
int main(void) 
{
  Serial.begin(2000000);
  DDRD = 0xFC;//registers
  DDRC=0xFF;
  TCNT1 = 0x00;
  OCR1A = 21;
  TCCR1A = 0x00;
  TCCR1B = 0x0A;
  TIMSK1 = 0x02;
  SREG = 0x80;
  homeposition();
  compare();
  Serial.begin(2000000);
  while(1)
  {
    ADMUX=0x44; //keypad setup
    ADCSRA=0xC7;
   while(checkbit(ADCSRA, bitn(ADSC)));
   result = result + ADCW;
   i++;
   if(i>99){
    average=result/100;
    Serial.println(average);
    if (average == 1) //action 1(stretch)
    {
      stretch();
    }
    else if (average == 2)// action 2(run at place)
    {
      run_at_place();
    }
    else if (average == 3)//action 3 (hands rotate)
    {
      hand_rotate();
    }
    else if (average >=10)//action 4(jump)
    {
      jump();
    }
    else if (average == 8)
    {
      homeposition();
      compare();
    }
    result=0;
    average=0;
    i=0;
    
  }
}
}
void stretch()//bends to one side and puts an arm up
{
  for (int i = 1; i <= 30; i++)
  {
    right_foot--;
    left_foot--;
    compare();
  }
  for (right_hand = 40; right_hand <= 70; right_hand++)
  {
    compare();
  }
  _delay_ms(20);
  for (int i = 1; i <= 30; i++)
  {
    right_foot++;
    left_foot++;
    compare();
  }
   _delay_ms(20);
  for (right_hand = 70; right_hand >= 40; right_hand--)
  {
    compare();
  }
  _delay_ms(20);
  for (int i = 1; i <= 30; i++)
  {
    right_foot++;
    left_foot++;
    compare();
  }
  _delay_ms(20);
  for (left_hand = 140; left_hand >= 110; left_hand--)
  {
    compare();
  }
  _delay_ms(20);
  for (int i = 1; i <= 30; i++)
  {
    right_foot--;
    left_foot--;
    compare();
  }
  _delay_ms(20);
    for (left_hand = 110; left_hand <= 140; left_hand++)
  {
    compare();
  }
  _delay_ms(20);
}
void run_at_place()// moves feet and hands
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
void hand_rotate() //rotates hands
{
    for (int i = 1; i <= 40; i++)
  {
    right_hand--;
    left_hand++;
    compare();
  }
      for (int i = 1; i <= 180; i++)
  {
    right_hand++;
    left_hand--;
    compare();
  }
      for (int i = 1; i <= 140; i++)
  {
    right_hand--;
    left_hand++;
    compare();
  }
}
void jump() //charges up then does a tiptoe with it hips out
{
  for (int i = 1; i <= 30; i++)
  {
    right_foot++;
    left_foot--;
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
  for (int i = 1; i <= 90; i++)
  {
    right_foot--;
    left_foot++;
    compare();
  }
  _delay_ms(20);
  for (int i = 1; i <= 60; i++)
  {
    right_foot++;
    left_foot--;
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
void compare() //void compare
{
  count_angle = right_hip + 46;
  count_angle1 = right_foot + 46;
  count_angle2 = left_hip + 46;
  count_angle3 = left_foot + 46;
  count_angle4 = left_hand + 46;
  count_angle5 = right_hand + 46;
  count_angle6 = neck + 46;
  _delay_us(500);
}
void homeposition() //homeposition reset
{
  right_hip = 90;
  right_foot = 90;
  left_hip = 90;
  left_foot = 90;
  left_hand = 140;
  right_hand = 40;
  neck = 90;
}
ISR(TIMER1_COMPA_vect) //servo setup
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
