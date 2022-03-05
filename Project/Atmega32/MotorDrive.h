#include "pwm_generation.h"

/**
 * you must call this method once before using any other method
 */
void init_motor_pins()
{
    DDRA |= 0x0F;
    init_pwm0_phase_mode_non_inverted();
    init_pwm2_phase_mode_non_inverted();
}

/**
 * input: left_wheel, right_wheel -> percentege of speed(-100 to 100, if negative motor will rotate in the opposite direction)
 */
void set_speed(unsigned char left_wheel, unsigned char right_wheel)
{
    if (left_wheel >= 0)
    {
        PORTA |= (1 << PORTA0);
        PORTA &= ~(1 << PORTA1);
        set_duty0_non_inverted(left_wheel);
    }
    else
    {
        PORTA |= (1 << PORTA1);
        PORTA &= ~(1 << PORTA0);
        set_duty0_non_inverted(left_wheel);
    }
    if (right_wheel >= 0)
    {
        PORTA |= (1 << PORTA2);
        PORTA &= ~(1 << PORTA3);
        set_duty2_non_inverted(right_wheel);
    }
    else
    {
        PORTA |= (1 << PORTA3);
        PORTA &= ~(1 << PORTA2);
        set_duty2_non_inverted(right_wheel);
    }
}

void stop_left_motor()
{
    PORTA &= (~(1 << PORTA0) & ~(1 << PORTA1));
}
void stop_right_motor()
{
    PORTA &= (~(1 << PORTA3) & ~(1 << PORTA2));
}
