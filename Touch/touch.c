#include "touch.h"

static void delayus(uint16_t us)
{
    __HAL_TIM_SetCounter(&htim1,0);//����
    HAL_TIM_Base_Start(&htim1);//������ʱ��
    while(__HAL_TIM_GetCounter(&htim1)<(20*us)){};
    HAL_TIM_Base_Stop(&htim1);//�رն�ʱ��
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
        CLK_H; // ��������Ч
    }
}

/*
 *cmd :CMD_READX/CMD_READY
 *return :raw coordinate value
 */
int32_t getcoordinate(uint16_t cmd)
{
    int32_t data=0;
    CLK_L; // ������ʱ��
    DO_L;  // ����������
    /*Ƭѡ*/
    CS_L;
    write_byte(cmd);
    delayus(6);
    CLK_L;
    delayus(1);
    /*һ��ʱ�����busy*/
    CLK_H;
    CLK_L;
    data&=0x0000;
    for (uint8_t count= 0; count < 12; count++) // ����12λ����
    {
        data<<=1;
        /*�½�����Ч*/
        CLK_H;
        CLK_L;       
        if (DI_READ)  data|=0x01;// �����ŵ�ƽ
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
        CLK_L; // ��ʼ��λ������ʱ��
        DO_L;  // ��ʼ��λ����������

        /*һ�����ݶ�д*/
        /*Ƭѡ*/
        CS_L;
        write_byte(cmd);
        HAL_Delay(6);
        CLK_L;
        HAL_Delay(1);
        /*һ��ʱ�����busy*/
        CLK_H;
        CLK_L;
        for (uint8_t i= 0; i < 16; i++) // ����16λ����,ֻ�и�12λ��Ч
        {
            data <<= 1;
            CLK_H;
            CLK_L;       // �½�����Ч
            if (DI_READ) // �����ŵ�ƽ
                data++;
        }
        data >>= 4; // ֻ�и�12λ��Ч.
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


