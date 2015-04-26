#ifndef _AVR_UART_H_
#define _AVR_UART_H_

#define MAX_UART_LEN 16
#define UART_ERROR  '-'

void avr_uart_init(void);
void avr_uart_send_byte(char tx_byte);
char avr_uart_receive_byte(void);
void avr_uart_write(char data[MAX_UART_LEN]);

#endif
