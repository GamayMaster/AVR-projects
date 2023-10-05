#include "macro.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Define macros for Ultrasonic Sensor Pins
#define TRIG_PIN    2    // Trigger pin (PD2)
#define ECHO_PIN    3    // Echo pin (PD3)

volatile unsigned long pulse_duration = 0;

void init() {
    // Set TRIG_PIN as output
    DDRD |= (1 << TRIG_PIN);
    // Set ECHO_PIN as input
    DDRD &= ~(1 << ECHO_PIN);
    
    // Initialize Timer1
    TCCR1B |= (1 << ICES1); // Input capture on rising edge
    TCCR1B |= (1 << CS11);  // Prescaler 8
    TIMSK |= (1 << TICIE1); // Enable input capture interrupt
    
    // Initialize UART for serial communication (for debugging)
    // Configure baud rate as needed (e.g., 9600)
    UBRRH = 0;
    UBRRL = 51; // for 9600 baud rate
    
    UCSRB = (1 << RXEN) | (1 << TXEN);   // Enable transmitter and receiver
    UCSRC = (1 << UCSZ1) | (1 << UCSZ0); // 8-bit data format
}

void trigger_pulse() {
    PORTD |= (1 << TRIG_PIN);  // Set TRIG_PIN high
    _delay_us(10);             // Wait for 10 microseconds
    PORTD &= ~(1 << TRIG_PIN); // Set TRIG_PIN low
}

int main() {
    init();
    sei(); // Enable global interrupts
    
    while (1) {
        trigger_pulse();
        _delay_ms(100); // Wait for 100 milliseconds
        
        // Calculate distance in centimeters
        float distance_cm = pulse_duration / 58.0;
        
        // Send distance data over UART (for debugging)
        printf("Distance: %.2f cm\n", distance_cm);
    }
    
    return 0;
}

ISR(TIMER1_CAPT_vect) {
    static unsigned long start_time = 0;
    
    if (TCCR1B & (1 << ICES1)) {
        // Rising edge detected, record start time
        start_time = ICR1;
        TCCR1B &= ~(1 << ICES1); // Change edge to falling
    } else {
        // Falling edge detected, calculate pulse duration
        unsigned long end_time = ICR1;
        pulse_duration = end_time - start_time;
        TCCR1B |= (1 << ICES1);  // Change edge to rising
    }
}
