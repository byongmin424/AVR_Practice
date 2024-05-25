// MIDDLE_CODE //

#define F_CPU_14745600

#include <avr/io.h>
#include <util/delay.h>

// BTN
int PushButtonDet(int number); // 몇번 버튼을 눌렀는지 판단하는 함수
int ClickDet(int number, int polarity); // 몇번 버튼을 , 눌렀을때? 떘을때?

// LED 
void LedOnOff(int number, int onoff); // LED on/off 함수
void LedTimeOnOff(unsigned t); // LED time

// FND
void Seg7Display(int idx, int number, int dot); 
void TimeDisplay(int idx, long unsigned int t); 

//KEYPAD
char row_scan(char row);
char key_scan();

// 전역 배열 정의 [KEY PAD 번호 자리 정의]
/*
 int KEY_INFO[16] = {1, 2, 3, 100,
					4, 5, 6, 101,
					7, 8, 9, 102,
					200, 0, 201, 103};*/


int main(void)
{
	// 포트 설정 /////////////////////////////////////////////////////////
	DDRB = 0xFF; // PORTB를 출력으로 설정 [LED]
	DDRC = 0x0F; // PC0-PC3를 출력, PC4-PC7를 입력으로 설정 [KEY PAD]
	DDRE = 0xFF; // PORTE를 출력으로 설정 [FND]
	DDRD = 0x00; // PORTD를 입력으로 설정 [BTN]
	
	PORTB = 0xff;
	/////////////////////////////////////////////////////////////////////
	
	// BTN_LED
	/*int i = 0;
	int count = 0;
	int time = 0;
	unsigned char inc = 1;*/
	
	// STOP_WATCH	
	/*int idx = 0; // 현재 FND 디스플레이 인덱스
	int number = 0; // 현재 디스플레이에 표시할 숫자
	int seg_delay = 4; // 디스플레이 갱신 간격(ms)
	long unsigned int t = 0; //스톱워치 시간 카운터
	int flag = 0; // 버튼 상태 확인
	int button1, prev_button1; // 0: off , 1 : on
	int button2, prev_button2;*/
	
	
	// CALCULATOR
	/*char key;
	int num1 = 0, num2 = 0;
	char op = 0;
	int result = 0;
	int state = 0;*/
	

	/////////////////////////////////////////////////////////////////////
	
	
	while(1)
	{	
		
		
		
		
		
		//BTN_LED_OLNL
		/*if (PushButtonDet(0))
		{
			if (inc == 1)
			{
				LedOnOff(count, 1);
				count++;
				if(count == 8){
					inc = 0;
					count = 7;
				}
			}
			else
			{
				LedOnOff(count, 0);
				count--;
				if (count < 0){
					inc = 1;
					count = 0;
				}
			}
		
			_delay_ms(1000);
		}*/
		
		// BTN_STATE_LED
		/*if (PushButtonDet(0)){
			time++;
			LedTimeOnOff(time);
		}
		else {
			time = 0;
		}*/
		
		// STOP_WATCH
		/*button1 = PushButtonDet(0);
		button2 = PushButtonDet(1);
		
		// 스톱워치 시작/정지 버튼 감지
		if ((prev_button1 == 0) && (button1 == 1)) {
			if (flag == 0)
				flag = 1;
			else
				flag = 0;
		
			//while (PushButtonDet(0));
		}
		
		TimeDisplay(idx, t);	
		
		// 마지막 인덱스에서 다시 처음으로 돌아가도록 인덱스 업데이트
		if (idx == 3)
			idx = 0;
		else
			idx++;

		if (flag == 1){
			//_delay_ms(seg_delay);
			t = t + seg_delay;
		}		
		else {
			if((prev_button2 == 0) && (button2 == 1))
				t = 0;
		}
		
		_delay_ms(seg_delay);
		prev_button1 = button1;
		prev_button2 = button2;
		*/
		
		// CALCULATOR
		/*key = key_scan(); // 키 입력을 스캔

		if (key != 0xFF) { // 키가 눌렸다면
			int key_value = KEY_INFO[key]; // 실제 키 값
			//////////////////////////////////////////////////////////////////////////////
			if (key_value < 10) { // 숫자 키
				if (state == 0 || state == 2) {
					if (state == 0) {
						num1 = key_value;
						Seg7Display(0,num1,0);
						} else {
						num2 = key_value;
						Seg7Display(0,num2,0);
					}
				}
			}
			else if (state == 0 && key_value >= 100 && key_value <= 103) { // 연산자 키
				op = key_value; // 연산자 설정
				state = 2;
			}
			else if (key_value == 200) { // '#' 키
				// 특수 기능 구현 (예: 결과 초기화)
				num1 = 0; num2 = 0; result = 0;
				state = 0;
				Seg7Display(0, 0, 0); // 디스플레이 초기화
			}
			else if (state == 2 && key_value == 201) { // '*' 키
				// 특수 기능 구현 ('=')// 결과 계산
				switch(op) {
					case 100: result = num1 + num2; break; // +
					case 101: result = num1 - num2; break; // -
					case 102: result = num1 * num2; break; // *
					case 103: result = num1 / num2; break; // /
				}
				_delay_ms(10);
				Seg7Display(0, result, 0); // 결과 표시
				_delay_ms(10000);
				state = 3;
			}
			//////////////////////////////////////////////////////////////////////////////
			
			/////////////////////// [state] 에 따른 자리 변화 /////////////////////////////
			if (state == 3 && key_value >= 0 && key_value <= 9) {
				state = 0;
				_delay_ms(10);
			}

			_delay_ms(200); // 디바운싱 대기 시간
		}*/
		
	}
}



// BTN /////////////////////////////////////////////////////////
int PushButtonDet(int number)
{
	if (((~PIND >> number) & 0x1) == 1)
	return 1;
	else
	return 0;
}

int ClickDet(int number, int polarity)
{
	int button;
	
	if (polarity == 1) { // 버튼을 누를 때를 감지
		button = PushButtonDet(number); // 버튼 눌렸는지 호출
		if (button == 0) { //button 상태가 0 인 상태에서
			_delay_ms(1); //지연 시키고
			button = PushButtonDet(number); // 버튼 눌렸는지 호출
			if (button == 1) { //button 상태가 1일때
				return 1; // 1 반환
			}
		}
	}
	else  { // 버튼이 떨어질 때
		button = PushButtonDet(number); // 버튼 눌렸는지 호출
		if (button == 1) { //button 상태가 1 인 상태에서
			_delay_ms(1); // 지연 시키고
			button = PushButtonDet(number); // 버튼 눌렸는지 호출
			if (button == 0) { //button 상태가 0일때
				return 1; //1 반환
			}
		}
	}
	return 0;
}


// LED /////////////////////////////////////////////////////////
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

void LedTimeOnOff(unsigned t)
{
	int i;
	unsigned t_s;
	t_s = t / 3000;
	
	for (i=0; i < 8; i++) LedOnOff(i,0);
	
	if ((t_s >= 1) && (t_s <= 8))
		LedOnOff(t_s - 1, 1);
	else if ((t_s >= 9) && (t_s <= 16))
		LedOnOff((t_s - 1), 1);
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

// FND /////////////////////////////////////////////////////////
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

void TimeDisplay(int idx, long unsigned int t)
{
	int number = 0;
	
	// 현재 인덱스에 따라 표시할 숫자 결정
	if (idx == 0)
	number = (t / 100) % 10;
	else if (idx == 1)
	number = (t / 1000) % 10;
	else if (idx == 2)
	number = (t / 10000) % 10;
	else if (idx == 3)
	number = (t / 100000) % 10;
	
	// 소수점 처리: idx 가 2일때만 dot 을 활성화
	if (idx != 2)
	Seg7Display(idx, number, 0);
	else
	Seg7Display(idx, number, 1);
}


// KEY_PAD /////////////////////////////////////////////////////
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
	char col = -1; //0xff 라는 소리
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