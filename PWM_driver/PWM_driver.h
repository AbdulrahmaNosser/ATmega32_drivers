#ifndef MCAL_PWM_H_
#define MCAL_PWM_H_

//registers & pins
#define PWM_CTRL_REG    TCCR0
#define COUNTER_REG     TCNT0
#define DUTY_CYCLE      OCR0
#define OUTPUT_DDRREG   DDRB
#define OUTPUT_PORT     PORTB
#define OUPUT_PIN       PB3

//waveforme generation modes
#define PHASE_CORRECT   0X40
#define FAST            0X48

//compare output mode
#define NIN_INVERTING   0X20
#define INVERTING       0X30       

void pwm0_init(unsigned char generation_mode, unsigned char compare_mode);

void pwm0_duty(unsigned char duty);

#endif