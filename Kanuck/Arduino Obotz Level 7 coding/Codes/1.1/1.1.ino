#include<avr/io.h>
#include<avr/interrupt.h>
#define setbit(x,y)(x|=y)
#define clearbit(x,y)(x&=~y)
#define bitn(p)(0x01<(p))
int count, angle, count_angle;
int main(void)
{
  Serial.begin(2000000);
  DDRD = 0xFF;
  TCNT1 = 0x00;
  OCR1A = 21;
  TCCR1A = 0x00;
  TCCR1B = 0x0A;
  TIMSK1 = 0x02;
  SREG = 0x80;
  Serial.println("Uploaded");
  while (true)
  {
    for (angle = 90; angle <= 150; angle++)
    {
      convert();
    }
    for (angle = 150; angle >= 90; angle--)
    {
      convert();
    }
  }
}
void convert()
{
  count_angle = angle + 46;
  _delay_us(5000);
}
ISR(TIMER1_COMPA_vect)
{
  count++;
  if (count <= count_angle)
  {
    setbit(PORTD, bitn(5));
  }
  else if ((count > count_angle) && (count < 1818))
  {
    clearbit(PORTD, bitn(5));
  }
  else if (count >= 1818)
  {
    count = 0;
  }
}
