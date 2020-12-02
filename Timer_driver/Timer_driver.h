#ifndef MCAL_TIMER_H_
#define MCAL_TIMER_H

//waveform generation mode
#define NORMAL      0X00
#define PWM         0X40
#define CTC         0X08
#define FPWM        0X48

//compare output mode
#define OFF         0X00
#define TOGGLE      0X10
#define CLEAR       0X20
#define SET         0X30

//clock source
#define OFF         0X00
#define CLK1        0X01
#define CLK8        0X02
#define CLK64       0X03
#define CLK256      0X04
#define CLK1024     0X05
#define EXT_FALL    0X06
#define EXT_RISE    0X07


extern void timer0_init(unsigned char mode);
extern void timer0_compare_out_mode(unsigned char mode);
extern void timer0_start(unsigned char clk);
extern unsigned long long timer0_read(void);

#endif