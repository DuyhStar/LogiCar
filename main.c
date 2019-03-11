/*
 * main.c
 * 左轮PWM：PB6 PB7
 * 右轮PWM：PB4 PB5
 * 按键1: PF4
 * 光电对管 :
 *    右：PA2
 *    左：PA3
 *    中：PA4
 *    边：PA5
 * I2C0:SCL PB2
 *      SDA PB3
 * UART1角度获得  RX:PB0
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
float    pitch, roll,  yaw;//欧拉角
uint16_t servoVal[6]={760,850,600,770,1475,1000};
uint8_t  servoUpdate = 0;
uint8_t  count_enter = 0;

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |  SYSCTL_XTAL_16MHZ);
    FPUEnable();
    FPULazyStackingEnable();

    SysTick_Init_ms(20);                //初始化一个滴答定时器
    UART0_Init(115200);                 //初始化串口0
    UART2_Init(9600);                   //初始化串口2，用来与串口屏通信
    PF123_RGB_Init();                   //指示灯初始化
    BlackDetect_Init();                 //黑线检测初始化
    Key1_init();                        //按键初始化
    Car_Init();                         //小车所用4路PWM初始化

    //按下按键,系统继续工作
    system_waitKey();
    IntMasterEnable();
    GREEN1;

    //小车出发至第一条线，然后原地右转90°,行驶至第一个十字交叉点。
    car_begin_goto_first_pos();

    //小车巡线前行，并开始计数，行驶至二维码处
    car_goto_n_black_line(6);

    //小车从二维码处后退，行驶至物料存放点
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

    //抓取
    system_waitKey();
    servo_init(servoVal);//初始化机械臂控制并设置其初始位置
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
        case 50://1秒
            Count_SysTick = 0;

            count_enter = 1;
            SysTickDisable();
            break;

        default:
            break;
    }
}

//用来获得GY25模块(MPU6050)所测量距离
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

    //将三个姿态角范围限制在0-360之间
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
