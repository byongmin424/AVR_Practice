#include <avr/io.h>
#include <util/delay.h>

void LedTimeOnOff(unsigned t); // 시간에 따라 led 켜라
void LedOnOff(int number, int onoff); // led 켜라
int PushButtonDet(int number); // 몇번 눌렀냐

int main(void)
{
	DDRB = 0xff; // 출력
	DDRD = 0x00; // 입력	
	
	PORTB = 0xff; // high
	
	int time = 0;

	while(1)
	{	
		_delay_ms(1);
		if(PushButtonDet(0)){
			time++;
			LedTimeOnOff(time);
		}
		else {
			time = 0;
		}
	}
}

// 시간에 따른 led 출력
void LedTimeOnOff(unsigned t)
{
	int i;
	unsigned t_s;
	t_s = t / 3000;
	
	for (i=0; i < 8; i++) LedOnOff(i, 0);
	
	if ((t_s >= 1) && (t_s <= 8)) // 한칸씩 증가되는 led  8초동안
	LedOnOff(t_s - 1, 1); 
	else if (t_s == 9) { // 9초
		PORTB = 0xF0;
		//for (i=0; i < 4; i++) LedOnOff(i,1);
	}
	else if (t_s == 10) { // 10초
		PORTB = 0x0F;
		//for (i=4; i < 4; i++) LedOnOff(i,1);
	}
	else if (t_s == 11) { // 11초
		PORTB = 0x00;
		//for (i=0; i < 8; i++) LedOnOff(i,1);
	}
}

void LedOnOff(int number, int onoff)
{
	char led_state;
	led_state = ~PORTB; // 현재 PORTB의 출력값을 가져와라
	
	if (onoff == 1) {
		led_state = led_state | (1 << number);
		PORTB = ~led_state;
	}
	else
	{
		led_state = led_state & ~(1 << number);
		PORTB = ~led_state;
	}
}

int PushButtonDet(int number)
{
	if (((~PIND >> number) & 0x1) == 1)
		return 1;
	else
		return 0;
}