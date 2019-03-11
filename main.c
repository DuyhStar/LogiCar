/*
 * main.c
 * ����PWM��PB6 PB7
 * ����PWM��PB4 PB5
 * ����1: PF4
 * ���Թ� :
 *    �ң�PA2
 *    ��PA3
 *    �У�PA4
 *    �ߣ�PA5
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
int      turn_speed    = 50;
int      forward_speed = 40;
float    pitch, roll,  yaw;//ŷ����
uint16_t servoVal[6]={760,850,600,770,1475,1000};
uint8_t  servoUpdate = 0;
uint8_t  count_enter = 0;

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |  SYSCTL_XTAL_16MHZ);
    FPUEnable();
    FPULazyStackingEnable();

    SysTick_Init_ms(20);                //��ʼ��һ���δ�ʱ��
    UART0_Init(115200);                 //��ʼ������0
    UART2_Init(9600);                   //��ʼ������2�������봮����ͨ��
    PF123_RGB_Init();                   //ָʾ�Ƴ�ʼ��
    BlackDetect_Init();                 //���߼���ʼ��
    Key1_init();                        //������ʼ��
    Car_Init();                         //С������4·PWM��ʼ��

    //���°���,ϵͳ��������
    system_waitKey();
    IntMasterEnable();
    GREEN1;

    //С����������һ���ߣ�Ȼ��ԭ����ת90��,��ʻ����һ��ʮ�ֽ���㡣
    car_begin_goto_first_pos();

    //С��Ѳ��ǰ�У�����ʼ��������ʻ����ά�봦
    car_goto_n_black_line(6);

    //С���Ӷ�ά�봦���ˣ���ʻ�����ϴ�ŵ�
    delay_s(1);
    Car_GoBack(forward_speed);
    uint8_t count_4 = 0;
    while(1){
        if(SideBlack()&&(count_enter == 1)){
            count_4++;
            count_enter = 0;
            SysTickEnable();
        }
        if(count_4 == 3){
            count_enter = 0;
            Car_Stop();
            CarStop_back();
            break;
        }
    }

    //ץȡ
    system_waitKey();
    servo_init(servoVal);//��ʼ����е�ۿ��Ʋ��������ʼλ��
    delay_ms(500);
    //hand_set_servo();
    goto_pos_1_middle();

    system_waitKey();
    Car_TurnLeft_Stay(turn_speed);
    delay_s(1);
    while(1){
        if(RightBlack()){
            CarStop_turnLeft();
            break;
        }
    }

    Car_GoForward(forward_speed);
    delay_ms(500);
    car_goto_n_black_line(2);

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
