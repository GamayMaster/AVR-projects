#include "macro.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>

#define F_CPU 8000000UL
#define BAUD_RATE 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD_RATE)) - 1)

volatile char gps_data[128];
volatile uint8_t gps_index = 0;
volatile uint8_t gps_message_complete = 0;


void USART_Init(void)
{
    UBRRH   = (byte)(UBRR_VALUE>>8);
    UBRRL   = (byte)UBRR_VALUE;

    SET_BIT(UCSRB, TXEN);
    SET_BIT(UCSRB, RXEN);

    SET_BIT(UCSRC, UCSZ0);
    SET_BIT(UCSRC, UCSZ1);
    SET_BIT(UCSRC, URSEL);
}

void USART_SendByte(byte data)
{
    while (READ_BIT(UCSRA, UDRE) == 0);
    UDR = data;
}

void USART_SendString(const char* str) {
    for (int i = 0; i < strlen(str); i++) {
        USART_SendByte(str[i]);
    }
}

// USART Receive Complete interrupt service routine
ISR(USART_RX_vect) {
    char received_char = UDR;

    if (received_char == '\n') {
        gps_data[gps_index] = '\0'; // Null-terminate the received GPS message
        gps_message_complete = 1;
        gps_index = 0;
    } else if (gps_index < sizeof(gps_data) - 1) {
        gps_data[gps_index++] = received_char;
    }
}

int main() {
    USART_Init();
    sei(); // Enable global interrupts

    while (1) {
        if (gps_message_complete) {
            // Process the received GPS data here
            USART_SendString("GPS Data: ");
            USART_SendString(gps_data);
            USART_SendString("\n");

            gps_message_complete = 0;
        }
    }
}
