#define	F_CPU_14745600

#include <avr/io.h>
#include <util/delay.h>

int PushButtonDet(int number); // 몇번 버튼을 눌렀는지 판단하는 함수
int ClickDet(int number, int polarity); // 눌렀는지 떘는지 확인하는 함수
void LedOnOff(int number, int onoff); // LED on/off 함수
void LedTimeOnOff(unsigned t); // 시간에 따른 led 출력

int main(void)
{
	DDRB = 0xFF;
	PORTB = 0xFF;
	
	DDRD = 0x0;
	/* Replace with your application code */
	int led_state = 0;
	int btn_state = 0;
	int i;
	unsigned int count;
	int current = PushButtonDet(0);
	int time = 0;
	
	
	while (1)
	{	

	}
}

void LedTimeOnOff(unsigned t)
{
	int i;
	unsigned t_s;
	t_s = t / 3000;
	
	for (i=0; i < 8; i++) LedOnOff(i,0);
	
	if ((t_s >= 1) && (t_s <= 8))
	LedOnOff(t_s - 1, 1);
	else if (t_s == 9) {
		PORTB = 0xF0;
		//for (i=0; i < 4; i++) LedOnOff(i,1);
	}
	else if (t_s == 10) {
		PORTB = 0x0F;
		//for (i=4; i < 4; i++) LedOnOff(i,1);
	}
	else if (t_s == 11) {
		PORTB = 0x00;
		//for (i=0; i < 8; i++) LedOnOff(i,1);
	}
}

int ClickDet(int number, int polarity)
{
	int button;
	
	if (polarity == 1) { // 버튼을 누를 때를 감지
		button = PushButtonDet(number);
		if (button == 0) {
			_delay_ms(1);
			button = PushButtonDet(number);
			if (button == 1) {
				return 1;
			}
		}
	}
	else  { // 버튼이 떨어질 때
		button = PushButtonDet(number);
		if (button == 1) {
			_delay_ms(1);
			button = PushButtonDet(number);
			if (button == 0) {
				return 1;
			}
		}
	}
	
	return 0;
}

int PushButtonDet(int number)
{
	if (((~PIND >> number) & 0x1) == 1)
	    return 1;
	else
	    return 0;
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
