#include <avr/io.h>
#include <avr/interrupt.h>
#define setbit(x,y)(x|=y)
#define clearbit(x,y) (x&=~y)
int right_hip, right_foot, left_hip, left_foot, right_hand, left_hand;
int count, count_angle, count_angle1, count_angle2, count_angle3, count_angle4, count_angle5;

void homePosition() {
  right_hip = 90;
  right_foot = 90;
  left_hip = 80;
  left_foot = 90;
  left_hand = 140;
  right_hand = 40;
}
void showArrow() {
  PORTC = 0x01;
  PORTB = 0xFB;
  _delay_us(200);
  PORTC = 0x02;
  PORTB = 0xF1;
  _delay_us(200);
  PORTC = 0x04;
  PORTB = 0xEA;
  _delay_us(200);
  PORTC = 0x08;
  PORTB = 0xFB;
  _delay_us(200);
  PORTC = 0x10;
  _delay_us(200);
}
void convert() {
  count_angle =  right_hip + 46;
  count_angle1 = right_foot + 46;
  count_angle2 = left_hip + 46;
  count_angle3 = left_foot + 46;
  count_angle4 = left_hand + 46;
  count_angle5 = right_hand + 46;
  _delay_us(500);

}

int main(void) {
  DDRD = 0xFF;
  DDRB = 0xFF;
  DDRC = 0xFF;
  PORTB = 0xFF;
  PORTC = 0x00;

 TCNT1 = 0x00;
  OCR1A = 21;
  TCCR1A = 0x00;
  TCCR1B = 0x0A;
  TIMSK1 = 0x02;
  SREG = 0x80;
  homePosition();
  convert();

  while (true) {





    for (left_foot = 90; left_foot >= 50; left_foot--) {
      convert();
      showArrow();
    }

    for (right_foot = 90; right_foot >= 80; right_foot--) {
      convert();
      showArrow();
    }

    for (int c = 0; c <= 30 ; c++) {
      right_hip--;
      left_hip--;
      left_hand++;
      right_hand++;
      convert();
      showArrow();
    }

    for (right_foot = 80; right_foot <= 90; right_foot++) {
      convert();
      showArrow();
    }

    for (left_foot = 50; left_foot <= 90; left_foot++) {
      convert();
      showArrow();
    }

    for (int c = 0; c <= 30; c++) {
      right_hip++;
      left_hip++;
      left_hand--;
      right_hand--;
      convert();
      showArrow();
    }
  }
}

ISR (TIMER1_COMPA_vect) {
  count++;
  if (count <= count_angle) {
    setbit(PORTD, bit(0));
  }
  else if ((count > count_angle) && (count < 1818)) {
    clearbit(PORTD, bit(0));
  }
  else if (count >= 1818) {
    count = 0;
  }
  if (count <= count_angle1) {
    setbit(PORTD, bit(1));
  }
  else if ((count > count_angle1) && (count < 1818)) {
    clearbit(PORTD, bit(1));
  }
  if (count <= count_angle2) {
    setbit(PORTD, bit(2));
  }
  else if ((count > count_angle2) && (count < 1818)) {
    clearbit(PORTD, bit(2));
  }
  if (count <= count_angle3) {
    setbit(PORTD, bit(3));
  }
  else if ((count > count_angle3) && (count < 1818)) {
    clearbit(PORTD, bit(3));
  }
  if (count <= count_angle4) {
    setbit(PORTD, bit(4));
  }
  else if ((count > count_angle4) && (count < 1818)) {
    clearbit(PORTD, bit(4));
  }
  if (count <= count_angle5) {
    setbit(PORTD, bit(5));
  }
  else if ((count > count_angle5) && (count < 1818)) {
    clearbit(PORTD, bit(5));
  }
}
