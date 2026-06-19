#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "ultrasonic.h"  

#define TRIG_PIN PE4
#define ECHO_PIN PE5 

void sensor_init(void)
{
    DDRE |= (1 << TRIG_PIN); //Needs to send output to echo
    DDRE &= ~(1 << ECHO_PIN); //Echo takes the burst as input
    PORTE &= ~(1 << TRIG_PIN);
}

void trigger_sensor(void)
{
    PORTE &= ~(1 << TRIG_PIN);
    _delay_us(2);
    PORTE |= (1 << TRIG_PIN);
    _delay_us(10);
    PORTE &= ~(1 << TRIG_PIN);
}

uint16_t grab_distance(void)
{
    uint16_t duration = 0;

    trigger_sensor();
    while (!(PINE & (1 << ECHO_PIN)));

    while (PINE & (1 << ECHO_PIN))
    {
        duration++;
        _delay_us(1);
    }

    return duration;
}

float distance_cm(void)
{
    return (float)(grab_distance()/ 58);
}

float distance_inches(void)
{
    return (float)(grab_distance()/ 148);
}
