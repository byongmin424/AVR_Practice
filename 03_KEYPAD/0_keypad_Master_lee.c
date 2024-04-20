#define F_CPU_14745600

#include <avr/io.h>
#include <util/delay.h>

char row_scan(char row);
char key_scan();
void Seg7Display(int idx, int number, int dot);
int KEY_INFO[16] = {1,	 2,   3,	 100,
					4,	 5,   6,	 101,
					7,	 8,   9,	 102,
					200, 0,   201,   103};

int main(void)
{
	DDRB = 0xff; // port b 를 출력으로 설정
	DDRC = 0x0f; // port c 에서 0123(row)는 출력. 4567(col)은 입력으로 설정
	DDRE = 0xff; // port e 를 출력으로 설정
	char key;
	char disp_key;
	int idx = 0;
	int dot = 0;
	
	int state_0, state_1, state_2, state_3;
	
	/* Replace with your application code */
	Seg7Display(0,0,0);
	while (1)
	{	
		key = key_scan();
		if (key != 0xff){
			if ((KEY_INFO[key] >= 0) && (KEY_INFO[key] <= 9))
				disp_key = KEY_INFO[key];
			else if ((KEY_INFO[key] >= 100) && (KEY_INFO[key] <= 103))
				idx = KEY_INFO[key] - 100;
			else if (KEY_INFO[key] == 200)
				dot = 1;
			else if ((KEY_INFO[key] == 201))
				dot = 0;		
				
				Seg7Display(idx, disp_key, dot);
		}
	}
}

// 행 열 스캔
char key_scan()
{
	char row;
	char col;
	char key;
	
	for (row = 0; row < 4; row++){
		col = row_scan(row);
		
		if (col != 0xff) {
			// ex) row = 0 , col = 1 이면  key = 1
			//     row = 1 , col = 3 이면  key = 7
			//     row = 2 , col = 2 이면  key = 10
			key = row * 4 + col;
			return (key);
		}
	}
	
	return (0xff); // 아무것도 안눌렸다면 0xff로 나오도록
}

char row_scan(char row)
{
	char col = -1; //0xff 라는 쇠리
	char pin_info;
	
	if		(row == 0)	PORTC = 0b1110;
	else if (row == 1)	PORTC = 0b1101;
	else if (row == 2)	PORTC = 0b1011;
	else if (row == 3)	PORTC = 0b0111;
	
	_delay_ms(10);
	
	pin_info = PINC >> 4; // 4567에 있는 col 입력값을 0123으로 데려오기
	
	if		(pin_info == 0x1)	col = 0; // 0001
	else if (pin_info == 0x2)	col = 1; // 0010
	else if (pin_info == 0x4)	col = 2; // 0100
	else if (pin_info == 0x8)	col = 3; // 1000
	
	return (col);
}

// 7세그먼트 디스플레이 제어 함수
void Seg7Display(int idx, int number, int dot)
{
	// 인덱스에 따라 해당 디지트 선택
	if (idx == 0) PORTE = 0x80;
	else if (idx == 1) PORTE = 0x40;
	else if (idx == 2) PORTE = 0x20;
	else if (idx == 3) PORTE = 0x10;
	
	// 숫자에 따른 세그먼트 설정
	if (number == 0) PORTB = 0xc0; //0
	else if (number == 1) PORTB = 0xf9; //1
	else if (number == 2) PORTB = 0xa4; //2
	else if (number == 3) PORTB = 0xb0; //3
	else if (number == 4) PORTB = 0x99; //4
	else if (number == 5) PORTB = 0x92; //5
	else if (number == 6) PORTB = 0x82; //6
	else if (number == 7) PORTB = 0xd8; //7
	else if (number == 8) PORTB = 0x80; //8
	else if (number == 9) PORTB = 0x90; //9
	
	// 소수점 처리
	if (dot == 1) PORTB = PORTB - 0x80;
}