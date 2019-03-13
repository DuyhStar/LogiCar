/*
 * main.c
 * ����PWM��PB6 PB7
 * ����PWM��PB4 PB5
 * ����1: PF4
 * ���Թ� :
 *    ǰ�ң�PA2
 *    ǰ��PA3
 *    ���У�PA4
 *    ����PA5
 *    ���ң�PE3
 * I2C0:SCL PB2
 *      SDA PB3
 * UART1�ǶȻ��  RX:PB0
 *            TX:PB1
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

#include "GPIO_Init.h"
#include "UART_Init.h"
#include "car.h"
#include "delay.h"
#include "sensor.h"
#include "systemtick.h"
#include "ServoCtl.h"

#define STOP while(1);

uint16_t distance;
int      turn_speed    = 50;                            //
int      forward_speed = 40;                            //
float    pitch, roll,  yaw;                             //ŷ����
uint16_t servoVal[6]   = {760,850,600,770,1475,1000};   //�����ʼ���Ƕ�ֵ
uint8_t  servoUpdate   = 0;                             //
uint8_t  count_enter   = 0;                             //

uint8_t  task[3]       = {1,2,3};                       //�Ӷ�ά���ж�ȡ��������Ϣ(1:��. 2:��. 3:��.)
uint8_t  color[3]      = {3,2,1};                       //���ڷŵ���ɫ˳��

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |  SYSCTL_XTAL_16MHZ);
    FPUEnable();
    FPULazyStackingEnable();

    SysTick_Init_ms(20);                //��ʼ��һ���δ�ʱ��
    UART0_Init(115200);                 //��ʼ������0
    UART2_Init(9600);                   //��ʼ������2�������봮����ͨ��
    PF123_RGB_Init();                   //ָʾ�Ƴ�ʼ��
    black_detect_init();                //���߼���ʼ��
    key1_init();                        //������ʼ��
    car_init();                         //С������4·PWM��ʼ��

    //���°���,��ʼ����
    system_waitKey();
    IntMasterEnable();
    GREEN1;

    //С����������һ���ߣ�Ȼ��ԭ����ת90��,��ʻ����һ��ʮ�ֽ���㡣
    car_begin_goto_first_pos();

    //С��Ѳ��ǰ�У�����ʼ��������ʻ����ά�봦
    car_forward_goto_n_black_line(6);

    //ɨ���ά�룬��ȡ������Ϣ
    //TODO

    //С���Ӷ�ά�봦���ˣ���ʻ�����ϴ�ŵ�
    car_forward_goto_n_black_line(3);

    //ԭ����ת90��,��������
    car_turn_left_90_degree();

    system_waitKey();
    servo_init(servoVal);//��ʼ����е�ۿ��Ʋ��������ʼλ��

    //��ȡ���ڷŵ���ɫ˳��
    //TODO

    //hand_set_servo();
    int i = 0;
    for(;i<3;i++)
    {
        //TODO
        //��ȡ��i������

        car_forward_goto_n_black_line(3);

        //TODO
        //���õ�i������

        if(i == 2)
            break;
        car_forward_goto_n_black_line(3);
    }


    //����
    car_turn_left_90_degree();
    car_forward_goto_n_black_line(3);
    car_turn_left_90_degree();
    car_forward_goto_n_black_line(3);
    car_turn_right(turn_speed);
    delay_ms(500);
    car_forward(forward_speed);
    delay_ms(500);
    car_stop();
    STOP;
}

void IntHandler_SysTick(void)
{
    static uint32_t Count_SysTick = 0;
    Count_SysTick++;

    switch(Count_SysTick)
    {
        case 50://1��
            Count_SysTick = 0;

            count_enter = 1;
            SysTickDisable();
            break;

        default:
            break;
    }
}

//�������GY25ģ��(MPU6050)����������
void IntHandler_UART1(void)
{
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART1_BASE, true);
    UARTIntClear(UART1_BASE, ui32Status);

    uint8_t buffer[8], i = 0, ch, begin = 0;
    while(UARTCharsAvail(UART1_BASE))
    {
        ch = UARTCharGetNonBlocking(UART1_BASE);
        if(ch == 0xAA)
        {
            begin = 1;
        }
        if(begin == 1)
        {
            buffer[i]  = ch;
            i++;
            if(i == 8)
                break;
        }
    }
    if( (buffer[0] == 0xAA)&&(buffer[7] == 0x55) )
    {
        yaw   = ((buffer[1]<<8) + buffer[2])/100;
        pitch = ((buffer[3]<<8) + buffer[4])/100;
        roll  = ((buffer[5]<<8) + buffer[6])/100;
    }

    //��������̬�Ƿ�Χ������0-360֮��
    if(yaw > 180)
        yaw -= 295;
    if(pitch > 180)
        pitch -= 295;
    if(roll > 180)
        roll  -= 295;
}

void IntHandler_UART2(void)
{
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART2_BASE, true);
    UARTIntClear(UART2_BASE, ui32Status);

    uint8_t i = 0, begin = 0;
    char ch, buffer[7];
    while(UARTCharsAvail(UART2_BASE))
    {
        ch = UARTCharGetNonBlocking(UART2_BASE);
        if(ch == '{')
        {
            begin = 1;
        }
        if(begin == 1)
        {
            buffer[i]  = ch;
            i++;
            if(i == 7)
                break;
        }
    }
    if( (buffer[0] == '{')&&(buffer[6] == '}') )
    {
        servoVal[buffer[1]-48] = 1000*(buffer[2]-48)+100*(buffer[3]-48)+10*(buffer[4]-48)+(buffer[5]-48);
        servoUpdate = 1;
    }
}
