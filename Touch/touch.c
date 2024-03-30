#include "touch.h"

volatile uint16_t Vertical = 0;
volatile uint16_t Horizon = 0;
volatile key_state_t IRQ = RELEASE;

static void delayus(uint16_t us)
{
    __HAL_TIM_SetCounter(&htim1, 0); // 清零
    HAL_TIM_Base_Start(&htim1);      // 开启定时器
    while (__HAL_TIM_GetCounter(&htim1) < (20 * us))
    {
    };
    HAL_TIM_Base_Stop(&htim1); // 关闭定时器
}

void Touch_init(void)
{
    ;
}

static void write_byte(uint8_t data)
{
    for (uint8_t count = 0; count < 8; count++)
    {
        CLK_L;
        if (data & 0x80)
            DO_H;
        else
            DO_L;
        data <<= 1;
        CLK_H; // 上升沿有效
    }
}

/*
 *cmd :CMD_READX/CMD_READY
 *return :raw coordinate value
 */
static uint16_t getcoordinate_xy(uint16_t cmd)
{

    int32_t data = 0;
    /*片选*/
    CS_L;
    CLK_L; // 拉低时钟线（复位）
    DO_L;  // 拉低数据线（复位）

    write_byte(cmd); // 发送指令
    delayus(6);      // 等待转换完成

    /*一个时钟清除busy*/
    CLK_L;
    delayus(1);
    CLK_H;

    /*读取数据16位*/
    data &= 0x0000;
    for (uint8_t count = 0; count < 16; count++)
    {
        data <<= 1;
        CLK_L;
        CLK_H;
        if (DI_READ)
            data |= 0x01;
    }
    data >>= 4; // 12位有效
    /*释放片选*/
    CS_H;
    /*坐标转换*/
    if (cmd == CMD_READX)
        data = (data - 300) / 11.25 + VERTICALOFFSET;
    else if (cmd == CMD_READY)
        data = (data - 300) / 15 + HORIZONYOFFSET;
    return data;
}

uint16_t getcoordinate(uint16_t cmd)
{

#if FILTER == 1
    uint16_t buffer[5];
    for (uint8_t count = 0; count < 5; count++)
    {
        buffer[count] = getcoordinate_xy(cmd);
    }
    uint16_t sum;
    for (uint8_t i = 0; i < 5; i++)
    {
        sum += buffer[i];
    }
    sum /= 5;

    /*坐标转换*/
    if (cmd == CMD_READX)
        sum = (sum - 300) / 11.25 + VERTICALOFFSET;
    else if (cmd == CMD_READY)
        sum = (sum - 300) / 15 + HORIZONYOFFSET;
    return sum;
#else 
    getcoordinate_xy(cmd);
#endif
}

uint8_t press_scan(void)
{
    uint8_t res = 0;
    if (!TOUCH_IRQ_READ)
    {
        HAL_Delay(15);
        if (!TOUCH_IRQ_READ)
            res = 1;
    }
    return res;
}
