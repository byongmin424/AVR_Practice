#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB = 0xff; // 출력
	DDRD = 0x00; // 입력	
	
	PORTB = 0xff; // high
	
	unsigned char btn_state;

	
	while(1)
	{	
		
		btn_state = PIND; // PIND 상태 저장
		
		_delay_ms(1);
		if((PIND == 0xfe) && (btn_state == 0xff)){ // 누른 시점에 동작 <-> 때는 시점에 동작 (PIND == 0xff) && (btn_state == 0xfe)
			PORTB =  ~PORTB;
			PIND = 0xff;
			_delay_ms(100);
		}
			
	}
}

// 0번 버튼을 누르면 on 다시 누르면 off