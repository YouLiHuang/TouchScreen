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
#include "mygui.h"
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
extern uint16_t Vertical;
extern uint16_t Horizon;
extern key_state_t IRQ;

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
    /*该线程用于检测触摸屏坐标*/
    taskENTER_CRITICAL();
    if (TOUCH_IRQ_READ) IRQ = RELEASE;
    else IRQ = PRESSED;
    Vertical = getcoordinate(CMD_READX);
    Horizon = getcoordinate(CMD_READY);
    taskEXIT_CRITICAL();

    /*其他的任务（如：串口shell任务等）*/

    osDelay(SCAN_PREIOD);
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
  //lv_mainstart();
  my_test_demo();
  /* Infinite loop */
  for (;;)
  {
    /*为了保证线程安全，采用互斥锁*/
    osMutexAcquire(myMutexlvHandle, 0xffff);
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

