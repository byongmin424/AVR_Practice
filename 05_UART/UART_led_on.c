/*
 * uart.c
 *
 * Created: 2024-05-17 오후 2:05:33
 * Author : TUK32
 */ 

#include <avr/io.h>

void Init_USART1(); // baud_rate 설정
// RXEN1 : Receiver Enable 1 로 설정 (UART 수진 동작 활성화)
// TXEN1 : Transmitter Enable 1로 설정(UART 송신 동작 활성화)
// Baud Rate = 115200
void putch_USART1(char data); // '문자 하나' 출력
void puts_USART1(char *str); // '문자열' 출력
unsigned char getch_USART1(); // UCSR1A 레지스터의 RXC1이 1이면 (= 수신 문자가 있음) UDR1 레지스터의 데이터를 반환한다.

void LedOnOff(int number, int onoff);

int main(void)
{
    DDRB = 0xff;
	PORTB = 0xff;
	
	Init_USART1();

	/* // 문자열 출력
	char string[] = "Hello\r\n";
	
	
	for (int i = 0; i < 5; i++) {
		puts_USART1(string);
	}
	*/

	char rx_data;
    
	puts_USART1("\r\n\n");
	puts_USART1("******************************* \r\n");
	puts_USART1("*****   LED ON Program   ****** \r\n");
	puts_USART1("******************************* \r\n");
	
	while (1) 
    {
		rx_data = getch_USART1();
		putch_USART1(rx_data);
		if (rx_data == '\r') putch_USART1('\n');
		
		if ((rx_data >= '0') & (rx_data <= '7')) {
			LedOnOff(rx_data - '0', 1);
		}
		else if (rx_data == 'q') {
			PORTB = 0xff;
		}
    }
}

void Init_USART1() // baud_rate 설정
{
    UCSR1B |= 0b00011000; // UCSR1B = UCSR1B | (0b00011000);
	UBRR1L = 95; // UBRR = (f_osc / 16 * BAUD) - 1
}

void putch_USART1(char data) // 문자 '하나'만 출력
{
	while (1) {
		if (UCSR1A & 0b00100000) { // 5번째 비트가 0이면 0, 1이면 1(송신 가능 상태)
			UDR1 = data; // 송신
			break;
		}
	}
}

void puts_USART1(char *str)
{
	// 전문가 스러운 고인물 스러운 창준씨 스타일 
	while (*str != 0)
	{
		putch_USART1(*str);
		str++;
	}
}

unsigned char getch_USART1()
{
	while (1) { // 글자가 들어올떄까지 계속 이 안에 맴돌겠지?
		if (UCSR1A & 0b10000000) { // RXCn = 1
			return (UDR1);
		}
	}
}

void LedOnOff(int number, int onoff)
{
	char led_state;
	led_state = ~PORTB;
	
	if (onoff == 1) {
		led_state = led_state | (1 << number);
		PORTB = ~led_state;
	}
	else {
		led_state = led_state & ~(1 << number);
		PORTB = ~led_state;
	}
}