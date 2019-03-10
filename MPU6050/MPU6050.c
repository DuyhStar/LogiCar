/*
 * MPU6050.c
 *
 *  Created on: 2018年4月14日
 *      Author: DuYihao
 */
#include "MPU6050.h"

void MPU6050_Init(void)
{
    // 1.初始化 IIC 接口
    I2C0_Init();

    // 2.复位 MPU6050
    I2CWriteRegOneByte(I2C0_BASE,0x68,0x6B,0x80);//复位
    delay_ms(200);
    I2CWriteRegOneByte(I2C0_BASE,0x68,0x6B,0x00);//唤醒

    // 3.设置角速度传感器和加速度传感器的满量程范围
    I2CWriteRegOneByte(I2C0_BASE,0x68,0x1B,0x03);//陀螺仪:±2000dps，16.4LSB/S
    I2CWriteRegOneByte(I2C0_BASE,0x68,0x1C,0x00);//加速度:±2g，16384LSB/S

    // 4.设置其他参数
    I2CWriteRegOneByte(I2C0_BASE,0x68,0x38,0x00);//关闭中断
    I2CWriteRegOneByte(I2C0_BASE,0x68,0x6A,0x00);//关闭关闭 AUX IIC 接口
    I2CWriteRegOneByte(I2C0_BASE,0x68,0x23,0x00);//禁止 FIFO
    I2CWriteRegOneByte(I2C0_BASE,0x68,0x19,0x13);//陀螺仪采样率:50Hz
    I2CWriteRegOneByte(I2C0_BASE,0x68,0x1A,0x04);//数字低通滤波器(DLPF):20Hz

    // 5.配置系统时钟源并使能角速度传感器和加速度传感器
    I2CWriteRegOneByte(I2C0_BASE,0x68,0x6B,0x01);//选择 x 轴陀螺 PLL 作为时钟源
    I2CWriteRegOneByte(I2C0_BASE,0x68,0x6C,0x00);//使能角速度传感器和加速度传感器
}
void MPU6050_AcceGet(int16_t *AcceX,int16_t *AcceY,int16_t *AcceZ)
{
    uint8_t  Buffer[6];
    uint16_t Bit8_High, Bit8_Low;
    int16_t  temp;

    //读取加速度寄存器
    I2CReadRegMultiByte(I2C0_BASE,0x68,0x3B,Buffer,6);

    Bit8_High = (uint16_t)Buffer[0]<<8;
    Bit8_Low  = (uint16_t)Buffer[1];
    temp      = (int16_t)(Bit8_High+Bit8_Low);//X轴原始值
    *AcceX     = temp;// /163.84;

    Bit8_High = (uint16_t)Buffer[2]<<8;
    Bit8_Low  = (uint16_t)Buffer[3];
    temp      = (int16_t)(Bit8_High+Bit8_Low);//Y轴原始值
    *AcceY     = temp;// /163.84;

    Bit8_High = (uint16_t)Buffer[4]<<8;
    Bit8_Low  = (uint16_t)Buffer[5];
    temp      = (int16_t)(Bit8_High+Bit8_Low);//Z轴原始值
    *AcceZ     = temp;// /163.84;
}

void MPU6050_GyroGet(int16_t *GyroX,int16_t *GyroY,int16_t *GyroZ)
{
    uint8_t  Buffer[6];
    uint16_t Bit8_High, Bit8_Low;
    int16_t  temp;

    //读取角速度寄存器
    I2CReadRegMultiByte(I2C0_BASE,0x68,0x43,Buffer,6);

    Bit8_High = (uint16_t)Buffer[0]<<8;
    Bit8_Low  = (uint16_t)Buffer[1];
    temp      = (int16_t)(Bit8_High+Bit8_Low);//X轴原始值
    *GyroX     = temp;// /16.4;

    Bit8_High = (uint16_t)Buffer[2]<<8;
    Bit8_Low  = (uint16_t)Buffer[3];
    temp      = (int16_t)(Bit8_High+Bit8_Low);//Y轴原始值
    *GyroY     = temp;// /16.4;

    Bit8_High = (uint16_t)Buffer[4]<<8;
    Bit8_Low  = (uint16_t)Buffer[5];
    temp      = (int16_t)(Bit8_High+Bit8_Low);//Z轴原始值
    *GyroZ     = temp;// /16.4;
}

int16_t MPU6050_TemptureGet(void)
{
    uint8_t  Buffer[2];
    uint16_t Bit8_High, Bit8_Low;
    int16_t  temp, Tempture;

    //读取温度寄存器
    I2CReadRegMultiByte(I2C0_BASE,0x68,0x41,Buffer,2);

    Bit8_High = (uint16_t)Buffer[0]<<8;       //取出高八位
    Bit8_Low  = (uint16_t)Buffer[1];          //取出低八位
    temp      = (int16_t)(Bit8_High+Bit8_Low);//相加得原始值

    Tempture  = temp/340.0+36.53;//换算为摄氏温度

    return Tempture;
}

//移植需要-->
uint32_t TM4_MPU6050_DMP_I2C_Write(unsigned char slave_addr, unsigned char reg_addr,
                               unsigned char length,     unsigned char *data)
{
    if(length==1)
        return I2CWriteRegOneByte(I2C0_BASE,slave_addr,reg_addr,*data);
    else
        return I2CWriteRegMultiByte(I2C0_BASE,slave_addr,reg_addr,data,length);
}

uint32_t TM4_MPU6050_DMP_I2C_Read(unsigned char slave_addr, unsigned char reg_addr,
                              unsigned char length,     unsigned char *data)
{
    if(length==1)
        return I2CReadRegOneByte(I2C0_BASE,slave_addr,reg_addr,data);
    else
        return I2CReadRegMultiByte(I2C0_BASE,slave_addr,reg_addr,data,length);
}

void TM4_MPU6050_DMP_delayms(unsigned long num_ms)
{
    delay_ms(num_ms);
}

void TM4_MPU6050_DMP_getms(unsigned long *count)
{
    //void
}


