/*
 * I2C_Configure.c
 *
 *  Created on: 2018年4月13日
 *      Author: DuYihao
 */
#include "I2C_Init.h"

//
//I2C Driver
//
void I2C0_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);

    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), true);//true,400Kbps. false,100Kbps.
}
void I2C1_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA6_I2C1SCL);
    GPIOPinConfigure(GPIO_PA7_I2C1SDA);
    GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);

    I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet(), true);//true,400Kbps. false,100Kbps.
}

// 功能说明: I2C写寄存器函数, Single Byte Write *寄存器地址和值均为8bit
// 返  回  值: ui32ErrFlag -- 错误标志位,0 -- success ,else fail
//           ____________________________________________
// MASTER: *| S | AD+W |     | RA |     | DATA |　           | P |*
// SLAVE : *|   |      | ACK |    | ACK |      | ACK |   |*
uint32_t I2CWriteRegOneByte(uint32_t ui32I2CBase,uint8_t ui8SlaAddr,uint8_t ui8RegAddr, uint8_t ui8RegData)
{
    uint32_t ui32ErrFlag = 0;
    while(I2CMasterBusy(ui32I2CBase))
        ;

    I2CMasterSlaveAddrSet(ui32I2CBase, ui8SlaAddr, false);
    I2CMasterDataPut(ui32I2CBase, ui8RegAddr);
    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(ui32I2CBase))
        ;
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
    {
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_ERROR_STOP);
        while(I2CMasterBusy(ui32I2CBase))
            ;
        return ui32ErrFlag;
    }

    I2CMasterDataPut(ui32I2CBase, ui8RegData);
    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while(I2CMasterBusy(ui32I2CBase))
        ;
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
        return ui32ErrFlag;

    return I2C_MASTER_ERR_NONE;
}

// 功能说明: I2C写寄存器函数, 向8bit寄存器写多个字节数据
// 返  回  值: ui32ErrFlag -- 错误标志位,0 -- success ,else fail
//           ____________________________________________________________________
// MASTER: *| S | AD+W |     | RA |     | DATA |     | ... |　        | DATA |     | P |*
// SLAVE : *|   |      | ACK |    | ACK |      | ACK |     |... |      | ACK |   |*
uint32_t I2CWriteRegMultiByte(uint32_t ui32I2CBase,uint8_t ui8SlaAddr,uint8_t ui8RegAddr,uint8_t *pui8RegData,uint32_t ui32WriteCount)
{
    uint32_t ui32Counter = 0;        /* 计数器 */
    uint32_t ui32ErrFlag = 0;        /* 错误标志位 */
    if(ui32WriteCount < 2)
        return 2;
    while(I2CMasterBusy(ui32I2CBase))
        ;

    I2CMasterSlaveAddrSet(ui32I2CBase, ui8SlaAddr, false);
    I2CMasterDataPut(ui32I2CBase, ui8RegAddr);
    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(ui32I2CBase))
        ;
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
    {
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_ERROR_STOP);
        while(I2CMasterBusy(ui32I2CBase))
            ;
        return ui32ErrFlag;
    }

    I2CMasterDataPut(ui32I2CBase, pui8RegData[0]);
    for(ui32Counter=0; ui32Counter<ui32WriteCount-1; ui32Counter++)
    {
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_CONT);
        while(I2CMasterBusy(ui32I2CBase))
            ;
        ui32ErrFlag = I2CMasterErr(ui32I2CBase);
        if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
        {
            I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_ERROR_STOP);
            while(I2CMasterBusy(ui32I2CBase))
                ;
            return ui32ErrFlag;
        }

        I2CMasterDataPut(ui32I2CBase, pui8RegData[ui32Counter+1]);
    }

    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while(I2CMasterBusy(ui32I2CBase))
        ;
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
    {
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_ERROR_STOP);
        while(I2CMasterBusy(ui32I2CBase))
            ;
        return ui32ErrFlag;
    }

    return I2C_MASTER_ERR_NONE;
}

// 说明: I2C读寄存器函数,  从一个8bit寄存器读一字节数据
// 返  回  值: ui32ErrFlag -- 错误标志位,0 -- success ,else fail
//          ______________________________________________________________
// MASTER: | S | AD+W |     | RA |     | S | AD+R |　           |      | NACK | P |
// SLAVE : |   |      | ACK |    | ACK |   |      | ACK | DATA |      |   |
uint32_t I2CReadRegOneByte(uint32_t ui32I2CBase,uint8_t ui8SlaAddr,uint8_t ui8RegAddr,uint8_t *pui8RegData)
{
    uint32_t ui32ErrFlag = 0;          /* 错误标志位 */

    while(I2CMasterBusy(ui32I2CBase))
        ;

    I2CMasterSlaveAddrSet(ui32I2CBase, ui8SlaAddr, false);
    I2CMasterDataPut(ui32I2CBase, ui8RegAddr);
    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(ui32I2CBase))
        ;
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
    {
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_ERROR_STOP);
        while(I2CMasterBusy(ui32I2CBase))
            ;
        return ui32ErrFlag;
    }

    I2CMasterSlaveAddrSet(ui32I2CBase, ui8SlaAddr, true);
    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_SINGLE_RECEIVE);
    while(I2CMasterBusy(ui32I2CBase))
        ;
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
    {
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP);
        while(I2CMasterBusy(ui32I2CBase))
            ;
        return ui32ErrFlag;
    }
    *pui8RegData = (uint8_t)I2CMasterDataGet(ui32I2CBase);

    return I2C_MASTER_ERR_NONE;
}

// 功能说明: I2C读寄存器函数,  从一个8bit寄存器读多个字节数据
// 返  回  值: ui32ErrFlag -- 错误标志位, 0 -- success, else fail
//           ________________________________________________________________________________
// MASTER: *| S | AD+W |     | RA |     | S | AD+R |　           |      | ACK |     | ... | NACK | P |*
// SLAVE : *|   |      | ACK |    | ACK |   |      | ACK | DATA |     | ... |     |      |   |*
uint32_t I2CReadRegMultiByte(uint32_t ui32I2CBase,uint8_t ui8SlaAddr,uint8_t ui8RegAddr,uint8_t *pui8RegData, uint32_t ui32ReadCount)
{
    uint32_t ui32Counter    = 0;       /* 计数器 */
    uint32_t ui32ErrFlag    = 0;       /* 错误标志位 */
    if(ui32ReadCount < 2)
        return 2;
    while(I2CMasterBusy(ui32I2CBase))
        ;

    I2CMasterSlaveAddrSet(ui32I2CBase, ui8SlaAddr, false);
    I2CMasterDataPut(ui32I2CBase, ui8RegAddr);
    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(ui32I2CBase))
        ;
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
    {
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_SEND_ERROR_STOP);
        while(I2CMasterBusy(ui32I2CBase))
            ;
        return ui32ErrFlag;
    }

    I2CMasterSlaveAddrSet(ui32I2CBase, ui8SlaAddr, true);
    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_RECEIVE_START);
    while(I2CMasterBusy(ui32I2CBase))
        ;
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
    {
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP);
        while(I2CMasterBusy(ui32I2CBase))
            ;
        return ui32ErrFlag;
    }
    pui8RegData[0] = (uint8_t)I2CMasterDataGet(ui32I2CBase);

    for(ui32Counter=0; ui32Counter<ui32ReadCount-2; ui32Counter++)
    {
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
        while(I2CMasterBusy(ui32I2CBase))
            ;
        ui32ErrFlag = I2CMasterErr(ui32I2CBase);
        if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
        {
            I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP);
            while(I2CMasterBusy(ui32I2CBase))
                ;
            return ui32ErrFlag;
        }
        pui8RegData[ui32Counter+1] = (uint8_t)I2CMasterDataGet(ui32I2CBase);
    }

    I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
    while(I2CMasterBusy(ui32I2CBase))
        ;
    ui32ErrFlag = I2CMasterErr(ui32I2CBase);
    if(ui32ErrFlag != I2C_MASTER_ERR_NONE)
    {
        I2CMasterControl(ui32I2CBase, I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP);
        while(I2CMasterBusy(ui32I2CBase))
            ;
        return ui32ErrFlag;
    }
    pui8RegData[ui32ReadCount-1] = (uint8_t)I2CMasterDataGet(ui32I2CBase);

    return I2C_MASTER_ERR_NONE;
}




