#include <avr/io.h>
#include <avr/power.h>
#include <string.h>
#include "avr_uart.h"

#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#define BAUD 300
#define UBRR_VAL ((F_CPU / (16UL * BAUD)) - 1)

// Initialize the UART
void avr_uart_init(void)
{
	// Enable bidirectional UART
	UCSR1B |= _BV(RXEN1) | _BV(TXEN1);
	// Use 8-bit characters
	UCSR1C |= _BV(UCSZ10) | _BV(UCSZ11);
	// Set the Baud rate
	UBRR1H = (UBRR_VAL >> 8);
	UBRR1L = UBRR_VAL;
}

// Get one char if available, otherwise -1
char avr_uart_receive_byte(void)
{
	if((UCSR1A & _BV(RXC1)) != 0)
	{
		return UDR1;
	}
	else
	{
		return '-';
	}
}


// Send one char (blocking)
void avr_uart_send_byte(char tx_byte)
{
	// Wait to be able to transmit
	while((UCSR1A & _BV(UDRE1)) == 0)
	asm volatile("nop"::);
	// Put the data into the send buffer
	UDR1 = tx_byte;
}

// send string of MAX_UART_LEN length 
void avr_uart_write(char data[MAX_UART_LEN])
{
	avr_uart_send_byte('\n');
	avr_uart_send_byte('\r');
	for(uint8_t i = 0; i < strlen(data); i++)
	{
		avr_uart_send_byte(data[i]);	
	}
	avr_uart_send_byte('\n');
	avr_uart_send_byte('\r');	
}


