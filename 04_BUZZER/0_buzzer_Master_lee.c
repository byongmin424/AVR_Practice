/*
 * buzzer.c
 *
 * Created: 2024-05-10 오후 1:41:15
 * Author : TUK32
  */

#define F_CPU 14745600
#include <avr/io.h>
#include <avr/delay.h>

#define C_4 3822
#define D_4 3405
#define E_4 3033
#define F_4 2863
#define G_4 2551
#define A_4 2272
#define B_4 2025

#define C_5 1911
#define D_5 1702.621782
#define E_5 1516.863502
#define F_5 1431.72839
#define G_5 1275.525009
#define A_5 1136.363636
#define B_5 1012.38491

#define C_6 955.5643467
#define D_6 851.3108911
#define E_6 758.4318663
#define F_6 715.8641948
#define G_6 637.7624233
#define A_6 568.1818182
#define B_6 506.192506

int PushButtonDet(int number);
void MakeSound(int period);
void MakeSound2(int period, unsigned long int duration); // period 단위 : us

//학교종
/*
int NOTE[] = {G_4,G_4,A_4,A_4,G_4,G_4,E_4,G_4,G_4,E_4,E_4,D_4, G_4,G_4,A_4,A_4,G_4,G_4,E_4,G_4,E_4,D_4,E_4,C_4};

/ * 노가다
int NOTE_4[] = {G_4,G_4,A_4,A_4,G_4,G_4,E_4,G_4,G_4,E_4,E_4,D_4, G_4,G_4,A_4,A_4,G_4,G_4,E_4,G_4,E_4,D_4,E_4,C_4};
int NOTE_5[] = {G_5,G_5,A_5,A_5,G_5,G_5,E_5,G_5,G_5,E_5,E_5,D_5, G_5,G_5,A_5,A_5,G_5,G_5,E_5,G_5,E_5,D_5,E_5,C_5};
int NOTE_6[] = {G_6,G_6,A_6,A_6,G_6,G_6,E_6,G_6,G_6,E_6,E_6,D_6, G_6,G_6,A_6,A_6,G_6,G_6,E_6,G_6,E_6,D_6,E_6,C_6};
* /

int DUR[] =  {4,4,4,4,4,4,2,4,4,4,4,1,4,4,4,4,4,4,2,4,4,4,4,1};
*/


//반짝반짝 작은별
int NOTE[] = {C_4,C_4,G_4,G_4,A_4,A_4,G_4,F_4,F_4,E_4,E_4,D_4,D_4,C_4,G_4,G_4,F_4,F_4,E_4,E_4,
	D_4,G_4,G_4,F_4,F_4,E_4,E_4,D_4,C_4,C_4,G_4,G_4,A_4,A_4,G_4,F_4,F_4,E_4,E_4,D_4,D_4,C_4,};
int DUR[] = {4,4,4,4,4,4,2,4,4,4,4,4,4,2,4,4,4,4,4,4,2,4,4,4,4,4,4,2,4,4,4,4,4,4,2,4,4,4,4,4,4,2};


/*
//밤양갱
int NOTE[] = {};
int DUR[] = {};
	*/
unsigned long int BASE_T = 100000;

int main(void)
{
	DDRG = 0xff; // PORTG를 출력으로 설정 [BUZZER]
	DDRD = 0x00; // PORTD를 입력으로 설정 [BTN]
	
	int i;
	int j;
	int note_len;
	
	note_len = sizeof(NOTE)/sizeof(int); // 일일히 세지 않아도 배열의 사이즈/int사이즈로 개수를 알아버리기
	
     /*Replace with your application code*/    
	 while (1)
    {
		
		if (PushButtonDet(0)) {
			for (i=0; i < note_len; i++){
				MakeSound2(NOTE[i], BASE_T/DUR[i]);
			}
		}
		else if (PushButtonDet(1)) {
			for (i=0; i < note_len; i++){
				MakeSound2(NOTE[i]/2, BASE_T/DUR[i]);
			}
		}
		else if (PushButtonDet(2)) {
			for (i=0; i < note_len; i++){
				MakeSound2(NOTE[i]/4, BASE_T/DUR[i]);
			}
		}
		
	}
	
}

int PushButtonDet(int number)
{
	if (((~PIND >> number) & 0x1) == 1)
	return 1;
	else
	return 0;
}

// 구형파 생성
void MakeSound(int period)
{
	int i;
	int duty;
	duty = period >> 1; // 한칸 오른쪽 shift = 나누기 2
	
	// 1 출력
	PORTG = PORTG | (1 << 4); // 1출력은 or 연산
	// period 절반 시간 지남.
	for (i = 0; i < duty; i++) _delay_us(1); // delay 내에는 '상수'를 넣어라
	// 0 출력
	PORTG = PORTG & ~(1 << 4); // 0출력은 and 연산
	// period 절반 시간 지남.
	for (i = 0; i < duty; i++) _delay_us(1);
}

void MakeSound2(int period, unsigned long int duration)
{
	int i;
	unsigned long int t_elapsed = 0;
	int duty;
	duty = period >> 1; // 한칸 오른쪽 shift = 나누기 2
	
	while(1) {
		// 1 출력
		PORTG = PORTG | (1 << 4); // 1출력은 or 연산
		// period 절반 시간 지남.
		for (i = 0; i < duty; i++) _delay_us(1); // delay 내에는 '상수'를 넣어라
		// 0 출력
		PORTG = PORTG & ~(1 << 4); // 0출력은 and 연산
		// period 절반 시간 지남.
		for (i = 0; i < duty; i++) _delay_us(1);
		
		t_elapsed += period;
		if (t_elapsed >= duration) break;
	}
	_delay_ms(100);
}

/*
//초음파 센서 실습
#define  F_CPU 14745600UL
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int count;
unsigned int Duration;
unsigned int Distance;
unsigned int echo;
char buffer[20];

void USART_Init(void)
{
	UCSR1B = (1<<RXEN1) | (1<<TXEN1);
	UCSR1C |= (1<<UCSZ10) | (1<<UCSZ11);
	UBRR1H = 0;
	UBRR1L = 7;
	//baud rate: 115200 bps
}

void putch_USART1(char data)
{
	while(!(UCSR1A & (1<<UDRE1)) );
	UDR1 = data;
}

void str_USART1(char *str)
{
	while( *str != 0){
		putch_USART1(*str);
		str++;
	}
}

void Timer0_Init()
{
	TIMSK = (1<<TOIE0);
	TCCR0 = (1<<CS01);////일반모드 및  8분주 설정
	TCNT0 = 245;		// TCNT245가 그나마 근접

}

void Trig_trans()
{
	PORTD = 0x10;
	_delay_us(10); //datasheet 상 10us의 TTL
	PORTD = 0x00;
	
}

void interrupt_init()
{
	EIMSK =(1<<INT4);
	EICRB =(1<<ISC40);//INT4 falling , rising edge trigger
	EIFR = (1<<INTF4);
}

ISR(INT4_vect)
{
	
	switch(echo)
	{
		case 0 :
		count = 0;
		echo = 1;
		break;
		
		case 1 : Duration = count;
		Distance = (unsigned int)(Duration*0.17);
		sprintf(buffer,"dis:%3d cm",Distance);
		echo = 0;
		break;
		
	}
}

ISR(TIMER0_OVF_vect)
{
	//TCNT0 = 245;
	Timer0_Init();
	count++;
}

void port_init(void)
{
	DDRD = 0xFF;//Trig핀
	DDRE = 0x00;//Ehho핀
}
int main(void)
{
	PORTD = 0x00;
	echo =0;
	count =0;
	
	port_init();
	USART_Init();
	Timer0_Init();
	interrupt_init();
	sei();

	while(1)
	{
		Trig_trans();
		_delay_ms(60); //datasheet 60ms 주기
		str_USART1(buffer);//거리 값 출력
	}
}*/