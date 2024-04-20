#define F_CPU_14745600

#include <avr/io.h>
#include <util/delay.h>

void Seg7Display(int idx, int number, int dot); // 7세그먼트 디스플레이 제어 함수
void Resets(); // 리셋시켜라 
int PushButtonDet(int number); // 버튼 눌렀니
void TimeDisplay(int idx, long unsigned int t); // 시간에 따라 표시

int main(void)
{
	int idx = 0; // 현재 FND 디스플레이 인덱스
	int number = 0; // 현재 디스플레이에 표시할 숫자
	int seg_delay = 4; // 디스플레이 갱신 간격(ms)
	long unsigned int t = 0; //스톱워치 시간 카운터
	int flag = 0; // 버튼 상태 확인
	int button1, prev_button1; // 0: off , 1 : on
	int button2, prev_button2;
	
	// DDRx 레지스터: 데이터 입출력 방향 결정/ 읽기쓰기 가능
	// PORTx 레지스터: 데이터 '출력' 레지스터/ 읽기쓰기 가능
	// PINx 레지스터: 데이터 '입력' 레지스터/ 읽기만 가능
	DDRB = 0xff;
	DDRE = 0xff;
	DDRD = 0x00;
	
	prev_button1 = 0;
	prev_button2 = 0;

    /* Replace with your application code */
    while (1)
    {	
		button1 = PushButtonDet(0);
		button2 = PushButtonDet(1);
		
		// 스톱워치 시작/정지 버튼 감지
		if ((prev_button1 == 0) && (button1 == 1)) {
			if (flag == 0)
				flag = 1;
			else
				flag = 0;
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
    }
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

int PushButtonDet(int number)
{
	if (((~PIND >> number) & 0x1) == 1)	
		return 1;
	else
		return 0;
}
