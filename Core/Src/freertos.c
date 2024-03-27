/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_demo_benchmark.h"
#include "touch.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SYSLED (LED_GPIO_Port->BSRR = (((LED_GPIO_Port->ODR & LED_Pin) << 16U) | (~LED_GPIO_Port->ODR & LED_Pin)))
void SysLed()
{
    /* Set selected pins that were at low level, and reset ones that were high */
    LED_GPIO_Port->BSRR = ((LED_GPIO_Port->ODR & LED_Pin) << 16U) | (~LED_GPIO_Port->ODR & LED_Pin);
}
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
osMutexDef(lv);
static int32_t x;
static int32_t y;
static uint8_t IRQ;
/* USER CODE END Variables */
/* Definitions for userThread */
osThreadId_t userThreadHandle;
const osThreadAttr_t userThread_attributes = {
  .name = "userThread",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for lvGuiThread */
osThreadId_t lvGuiThreadHandle;
const osThreadAttr_t lvGuiThread_attributes = {
  .name = "lvGuiThread",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for ledThread */
osThreadId_t ledThreadHandle;
const osThreadAttr_t ledThread_attributes = {
  .name = "ledThread",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for myMutexlv */
osMutexId_t myMutexlvHandle;
const osMutexAttr_t myMutexlv_attributes = {
  .name = "myMutexlv"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void startTask(void *argument);
void lvGuiTask(void *argument);
void ledTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);
void vApplicationIdleHook(void);
void vApplicationTickHook(void);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{
}

__weak unsigned long getRunTimeCounterValue(void)
{
    return 0;
}
/* USER CODE END 1 */

/* USER CODE BEGIN 2 */
void vApplicationIdleHook(void)
{
    /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
    to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
    task. It is essential that code added to this hook function never attempts
    to block in any way (for example, call xQueueReceive() with a block time
    specified, or call vTaskDelay()). If the application makes use of the
    vTaskDelete() API function (as this demo application does) then it is also
    important that vApplicationIdleHook() is permitted to return to its calling
    function, because it is the responsibility of the idle task to clean up
    memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/* USER CODE BEGIN 3 */
void vApplicationTickHook(void)
{
    /* This function will be called by each tick interrupt if
    configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h. User code can be
    added here, but the tick hook is called from an interrupt context, so
    code must not attempt to block, and only the interrupt safe FreeRTOS API
    functions can be used (those that end in FromISR()). */
    lv_tick_inc(1);
}
/* USER CODE END 3 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

    // lv_demo_benchmark();
  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of myMutexlv */
  myMutexlvHandle = osMutexNew(&myMutexlv_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */

  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of userThread */
  userThreadHandle = osThreadNew(startTask, NULL, &userThread_attributes);

  /* creation of lvGuiThread */
  lvGuiThreadHandle = osThreadNew(lvGuiTask, NULL, &lvGuiThread_attributes);

  /* creation of ledThread */
  ledThreadHandle = osThreadNew(ledTask, NULL, &ledThread_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
    /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_startTask */
/**
 * @brief  Function implementing the startThread thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_startTask */
void startTask(void *argument)
{
  /* USER CODE BEGIN startTask */

    /* Infinite loop */
    for (;;)
    {
        /*do some thing here*/
        taskENTER_CRITICAL();
        x = getcoordinate(CMD_READX);
        x = x * 320 / 4096;
        y = getcoordinate(CMD_READY);
        y = y * 240 / 4096;
        IRQ = TOUCH_IRQ_READ;
        taskEXIT_CRITICAL();
        osDelay(100);
    }
  /* USER CODE END startTask */
}

/* USER CODE BEGIN Header_lvGuiTask */
/**
 * @brief Function implementing the lvGuiThread thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_lvGuiTask */
void lvGuiTask(void *argument)
{
  /* USER CODE BEGIN lvGuiTask */
    // lv_demo_benchmark();
    static lv_style_t style_area; // 创建样式
    lv_style_init(&style_area);   // 初始化样式
    lv_style_set_text_font(&style_area, &lv_font_montserrat_20);
    lv_style_set_text_color(&style_area, lv_color_hex(0xffff));
    lv_style_set_bg_color(&style_area, lv_color_hex(0x1145));
    lv_style_set_bg_opa(&style_area, 200);
    lv_style_set_border_color(&style_area, lv_color_hex(0xff00));
    lv_style_set_border_width(&style_area, 2);

    /*主布局*/
    lv_obj_t *par = lv_obj_create(lv_scr_act());
    lv_obj_set_size(par, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));
    lv_obj_set_style_bg_color(par, lv_color_hex(0x0000), LV_STATE_DEFAULT);
    lv_obj_set_pos(par, 0, 0);

    /*第一个区域显示x*/
    lv_obj_t *area1 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(area1, lv_obj_get_width(lv_scr_act()) * 4 / 5, lv_obj_get_height(lv_scr_act()) / 5);
    lv_obj_add_style(area1, &style_area, 0);
    lv_obj_align(area1, LV_ALIGN_TOP_MID, 0, 0);

    /*第二个区域显示y*/
    lv_obj_t *area2 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(area2, lv_obj_get_width(lv_scr_act()) * 4 / 5, lv_obj_get_height(lv_scr_act()) / 5);
    lv_obj_add_style(area2, &style_area, 0);
    lv_obj_align(area2, LV_ALIGN_BOTTOM_MID, 0, 0);

    /*第三个区域显示IRQ*/
    lv_obj_t *area3 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(area3, lv_obj_get_width(lv_scr_act()) * 4 / 5, lv_obj_get_height(lv_scr_act()) / 5);
    lv_obj_add_style(area3, &style_area, 0);
    lv_obj_align(area3, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *label = lv_label_create(area1);
    lv_label_set_text_fmt(label, "XValue is :%d", 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *label2 = lv_label_create(area2);
    lv_label_set_text_fmt(label2, "YValue is :%d", 0);
    lv_obj_align(label2, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *label3 = lv_label_create(area3);
    lv_obj_align(label3, LV_ALIGN_CENTER, 0, 0);

    /* Infinite loop */
    for (;;)
    {
        /*为了保证线程安全，采用互斥锁*/

        osMutexAcquire(myMutexlvHandle, 0xff);

        if (IRQ)
        {
            lv_label_set_text(label3, "not press!");
            lv_label_set_text_fmt(label, "XValue is :%5d", 0);
            lv_label_set_text_fmt(label2, "YValue is :%5d", 0);
        }
        else
        {
            lv_label_set_text(label3, "pressed!");
            lv_label_set_text_fmt(label, "XValue is :%d", x);
            lv_label_set_text_fmt(label2, "YValue is :%d", y);
        }

        lv_task_handler();
        osMutexRelease(myMutexlvHandle);
        vTaskDelay(5);
    }
  /* USER CODE END lvGuiTask */
}

/* USER CODE BEGIN Header_ledTask */
/**
 * @brief Function implementing the ledThread thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_ledTask */
void ledTask(void *argument)
{
  /* USER CODE BEGIN ledTask */

    /* Infinite loop */
    for (;;)
    {
        taskENTER_CRITICAL();
        SYSLED;
        taskEXIT_CRITICAL();
        osDelay(1000);
    }
  /* USER CODE END ledTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/*sw callback*/
void sw_callback(lv_event_t *e)
{
}

/* USER CODE END Application */

