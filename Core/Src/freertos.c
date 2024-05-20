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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

osMutexId_t mutexI2C1Handle;
const osMutexAttr_t mutexI2C1_attributes = {
		.name = "I2C1 Mutex",
		.attr_bits = 0,
		.cb_mem = NULL,
		.cb_size = 0,
};

osThreadId_t measureTaskHandle;
const osThreadAttr_t measureTask_attributes = {
		.name = "measureTask",
		.stack_size = 128 * 4,
		.priority = (osPriority_t) osPriorityNormal,
};

osThreadId_t lcdTaskHandle;
const osThreadAttr_t lcdTask_attributes = {
		.name = "lcdTask",
		.stack_size = 128 * 8,
		.priority = (osPriority_t) osPriorityNormal,
};

osThreadId_t ledTaskHandle;
const osThreadAttr_t ledTask_attributes = {
		.name = "ledTask",
		.stack_size = 128 * 4,
		.priority = (osPriority_t) osPriorityNormal,
};

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
extern void StartLedTask(void *argument);
extern void StartLCDTask(void *argument);
extern void StartMeasureTask(void *argument);

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
	mutexI2C1Handle = osMutexNew(&mutexI2C1_attributes);
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
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  ledTaskHandle = osThreadNew(StartLedTask, NULL, &ledTask_attributes);
  lcdTaskHandle = osThreadNew(StartLCDTask, NULL, &lcdTask_attributes);
  measureTaskHandle = osThreadNew(StartMeasureTask, NULL, &measureTask_attributes);

  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
#include <ARGB.h>
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	ARGB_Init();
	ARGB_Clear();
	while (ARGB_Show() == ARGB_OK);

  /* Infinite loop */
  for(;;)
  {
//	ARGB_FillRGB(0, 0, 0);
//    while (ARGB_Ready() == ARGB_BUSY); // Update - Option 4
//    ARGB_Show();
//    osDelay(1000);
//
//    ARGB_FillRGB(255, 0, 0);
//    while (ARGB_Ready() == ARGB_BUSY); // Update - Option 4
//    ARGB_Show();
//	osDelay(1000);
//
//    ARGB_FillRGB(0, 255, 0);
//    while (ARGB_Ready() == ARGB_BUSY); // Update - Option 4
//    ARGB_Show();
//	osDelay(1000);
//
//    ARGB_FillRGB(0, 0, 255);
//    while (ARGB_Ready() == ARGB_BUSY); // Update - Option 4
//    ARGB_Show();
//	osDelay(1000);
	  osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

