/*
 * led_shift.c
 *
 * Created: 2024-04-18 오후 9:07:17
 * Author : TUK28
 */ 
#define	F_CPU_14745600

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xff; // PORT B 를 출력으로 할당
	PORTB = 0xff; // PORT B 에 HIGH 값 전압 인가하여 초기화
	
	int i;
	
    /* Replace with your application code */
    while (1) 
    {
		
		PORTB = ~(1 << i); // 1111_1111 -> 1111_1110 -> 1111_1101 -> 1111_1011 이런식으로 간다는 말
		
		if (i == 7){
			i = 0;
		}
		else
			i++;
		_delay_ms(500);
	}
}