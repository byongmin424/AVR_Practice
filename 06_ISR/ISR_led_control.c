#define F_CPU 14745600

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void InterruptInit();
ISR(INT0_vect);
ISR(INT1_vect);
int PushButtonDet(int number);
int ClickDet(int number, int polarity);

int BtnPressed;

void InterruptInit()
{
	// PORTD 0 = INT0 외부 인터럽트 사용 설저아 하강 에지 감지
	// PORTD 1 = INT1 외부 인터럽트 사용 설저아 상승 에지 감지
	EICRA = (2 << ISC00) | (3 << ISC10);
	// EICRA = 0b00001110; // 0번 10 -> 하강에지, 1번 11 -> 상승에지, EICR(External Interrupt Control) 0000_0010 으로 세팅
						   // interrupt 위치에 따라서 설정해줘야 한다. 0000 0010 이면 0번, 0000 1000 이면 1번, 0010 0000 이면 2번 이런식
	
	EIMSK = (1 << INT0) | (1 << INT1);
	// EIMSK = 0b00000011; // INT0, INT1 사용 허가, EIMSK(External Interrupt Mask Register)
						   // 0000_0001 이면 0번, 0000_0010 이면 1번, .. 이런식
	
	sei(); // CPU가 인터럽트에 반응하게 해라
}

ISR(INT0_vect)
{
	// 100ms 후에도 버튼이 눌려있어야 눌러졌다고 판단.
	_delay_ms(100);
	if (PushButtonDet(0))
	BtnPressed = 1;
	
	// 불안정한 신호에 의해서 발생한 인터럽트는 무시.
	EIFR = 1 << INTF0; // 인터럽트 플래그 Clear, EIFR(Enternal Interrupt Flag Register), 0번일 경우
}

ISR(INT1_vect)
{
	// 100ms 후에도 버튼이 눌려있어야 눌러졌다고 판단.
	_delay_ms(100);
	if (~PushButtonDet(1))
	BtnPressed = 1;
	
	// 불안정한 신호에 의해서 발생한 인터럽트는 무시.
	EIFR = 1 << INTF1; // 인터럽트 플래그 Clear, EIFR(Enternal Interrupt Flag Register), 1번일 경우
}

int main(void)
{
	DDRB = 0xff;
	DDRD = 0x0;
	
	PORTB = 0xff;
	BtnPressed = 0;
	
	InterruptInit();
	
    while (1) 
    {
		if (BtnPressed) {
			PORTB = ~PORTB;
			BtnPressed = 0;
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

int ClickDet(int number, int polarity)
{
	int button;
	
	if (polarity == 1) 
	{
		button = PushButtonDet(number);
		if (button == 0) {
			_delay_ms(1);
			button = PushButtonDet(number);
			if (button == 1) {
				return 1;
			}
		}
	}
	else {
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