/*
 * MPU6050.c
 *
 *  Created on: 2018��4��14��
 *      Author: DuYihao
 */
#include "MPU6050.h"

void MPU6050_Init(void)
{
    // 1.��ʼ�� IIC �ӿ�
    I2C0_Init();

    // 2.��λ MPU6050
    I2CWriteRegOneByte(I2C0_BASE,0x68,0x6B,0x80);//��λ
    delay_ms(200);
    I2CWriteRegOneByte(I2C0_BASE,0x68,0x6B,0x00);//����

    // 3.���ý��ٶȴ������ͼ��ٶȴ������������̷�Χ
    I2CWriteRegOneByte(I2C0_BASE,0x68,0x1B,0x03);//������:��2000dps��16.4LSB/S
    I2CWriteRegOneByte(I2C0_BASE,0x68,0x1C,0x00);//���ٶ�:��2g��16384LSB/S

    // 4.������������
    I2CWriteRegOneByte(I2C0_BASE,0x68,0x38,0x00);//�ر��ж�
    I2CWriteRegOneByte(I2C0_BASE,0x68,0x6A,0x00);//�رչر� AUX IIC �ӿ�
    I2CWriteRegOneByte(I2C0_BASE,0x68,0x23,0x00);//��ֹ FIFO
    I2CWriteRegOneByte(I2C0_BASE,0x68,0x19,0x13);//�����ǲ�����:50Hz
    I2CWriteRegOneByte(I2C0_BASE,0x68,0x1A,0x04);//���ֵ�ͨ�˲���(DLPF):20Hz

    // 5.����ϵͳʱ��Դ��ʹ�ܽ��ٶȴ������ͼ��ٶȴ�����
    I2CWriteRegOneByte(I2C0_BASE,0x68,0x6B,0x01);//ѡ�� x ������ PLL ��Ϊʱ��Դ
    I2CWriteRegOneByte(I2C0_BASE,0x68,0x6C,0x00);//ʹ�ܽ��ٶȴ������ͼ��ٶȴ�����
}
void MPU6050_AcceGet(int16_t *AcceX,int16_t *AcceY,int16_t *AcceZ)
{
    uint8_t  Buffer[6];
    uint16_t Bit8_High, Bit8_Low;
    int16_t  temp;

    //��ȡ���ٶȼĴ���
    I2CReadRegMultiByte(I2C0_BASE,0x68,0x3B,Buffer,6);

    Bit8_High = (uint16_t)Buffer[0]<<8;
    Bit8_Low  = (uint16_t)Buffer[1];
    temp      = (int16_t)(Bit8_High+Bit8_Low);//X��ԭʼֵ
    *AcceX     = temp;// /163.84;

    Bit8_High = (uint16_t)Buffer[2]<<8;
    Bit8_Low  = (uint16_t)Buffer[3];
    temp      = (int16_t)(Bit8_High+Bit8_Low);//Y��ԭʼֵ
    *AcceY     = temp;// /163.84;

    Bit8_High = (uint16_t)Buffer[4]<<8;
    Bit8_Low  = (uint16_t)Buffer[5];
    temp      = (int16_t)(Bit8_High+Bit8_Low);//Z��ԭʼֵ
    *AcceZ     = temp;// /163.84;
}

void MPU6050_GyroGet(int16_t *GyroX,int16_t *GyroY,int16_t *GyroZ)
{
    uint8_t  Buffer[6];
    uint16_t Bit8_High, Bit8_Low;
    int16_t  temp;

    //��ȡ���ٶȼĴ���
    I2CReadRegMultiByte(I2C0_BASE,0x68,0x43,Buffer,6);

    Bit8_High = (uint16_t)Buffer[0]<<8;
    Bit8_Low  = (uint16_t)Buffer[1];
    temp      = (int16_t)(Bit8_High+Bit8_Low);//X��ԭʼֵ
    *GyroX     = temp;// /16.4;

    Bit8_High = (uint16_t)Buffer[2]<<8;
    Bit8_Low  = (uint16_t)Buffer[3];
    temp      = (int16_t)(Bit8_High+Bit8_Low);//Y��ԭʼֵ
    *GyroY     = temp;// /16.4;

    Bit8_High = (uint16_t)Buffer[4]<<8;
    Bit8_Low  = (uint16_t)Buffer[5];
    temp      = (int16_t)(Bit8_High+Bit8_Low);//Z��ԭʼֵ
    *GyroZ     = temp;// /16.4;
}

int16_t MPU6050_TemptureGet(void)
{
    uint8_t  Buffer[2];
    uint16_t Bit8_High, Bit8_Low;
    int16_t  temp, Tempture;

    //��ȡ�¶ȼĴ���
    I2CReadRegMultiByte(I2C0_BASE,0x68,0x41,Buffer,2);

    Bit8_High = (uint16_t)Buffer[0]<<8;       //ȡ���߰�λ
    Bit8_Low  = (uint16_t)Buffer[1];          //ȡ���Ͱ�λ
    temp      = (int16_t)(Bit8_High+Bit8_Low);//��ӵ�ԭʼֵ

    Tempture  = temp/340.0+36.53;//����Ϊ�����¶�

    return Tempture;
}

//��ֲ��Ҫ-->
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


