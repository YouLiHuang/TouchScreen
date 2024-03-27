#include "touch.h"

static void delayus(uint16_t us)
{
    __HAL_TIM_SetCounter(&htim1,0);//清零
    HAL_TIM_Base_Start(&htim1);//开启定时器
    while(__HAL_TIM_GetCounter(&htim1)<(20*us)){};
    HAL_TIM_Base_Stop(&htim1);//关闭定时器
}

static void write_byte(uint8_t data)
{
    for (uint8_t count = 0; count < 8; count++)
    {
        if (data & 0x80)
            DO_H;
        else
            DO_L;
        data <<= 1;
        CLK_L;
        CLK_H; // 上升沿有效
    }
}

/*
 *cmd :CMD_READX/CMD_READY
 *return :raw coordinate value
 */
int32_t getcoordinate(uint16_t cmd)
{
    int32_t data=0;
    CLK_L; // 先拉低时钟
    DO_L;  // 拉低数据线
    /*片选*/
    CS_L;
    write_byte(cmd);
    delayus(6);
    CLK_L;
    delayus(1);
    /*一个时钟清除busy*/
    CLK_H;
    CLK_L;
    data&=0x0000;
    for (uint8_t count= 0; count < 12; count++) // 读出12位数据
    {
        data<<=1;
        /*下降沿有效*/
        CLK_H;
        CLK_L;       
        if (DI_READ)  data|=0x01;// 读引脚电平
    }
    CS_H;
    return data;
}

uint16_t getcoordinate_filter(uint16_t cmd)
{
    uint16_t buffer[5];

    for (uint8_t count = 0; count < 5; count ++)
    {
        uint16_t data=0;
        CLK_L; // 初始复位先拉低时钟
        DO_L;  // 初始复位拉低数据线

        /*一次数据读写*/
        /*片选*/
        CS_L;
        write_byte(cmd);
        HAL_Delay(6);
        CLK_L;
        HAL_Delay(1);
        /*一个时钟清除busy*/
        CLK_H;
        CLK_L;
        for (uint8_t i= 0; i < 16; i++) // 读出16位数据,只有高12位有效
        {
            data <<= 1;
            CLK_H;
            CLK_L;       // 下降沿有效
            if (DI_READ) // 读引脚电平
                data++;
        }
        data >>= 4; // 只有高12位有效.
        CS_H;


        buffer[count]=data;
    }

    uint16_t sum;
    for (uint8_t i = 0; i < 5; i++)
    {
        sum+=buffer[i];
    }
    sum/=5;
    
    return sum;
}


