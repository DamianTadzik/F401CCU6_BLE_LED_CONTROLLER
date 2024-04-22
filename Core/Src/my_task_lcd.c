/*
 * my_task_lcd.c
 *
 *  Created on: Apr 19, 2024
 *      Author: brzan
 */

#include "main.h"
#include "cmsis_os2.h"
#include "my_menu.h"

/**
 * TIM4 set in combined encoder mode, filtering set to maximum value 0xF
 * TIM2 used in LED
 * TIM11 as debouncing timer for exti		// FIXME there must be easier and better way to do this shit
 * GPIO_EXTI5 falling edge trigger detection button
 */

typedef enum {
	FLAG_RESET = 0x00,
	FLAG_SET = 0x01
} FLAG_T;

static volatile FLAG_T _debouncing_flag = 0;
static const FLAG_T get_debouncing_flag(void)
{
	return _debouncing_flag;
}
static void set_debouncing_flag(const FLAG_T set_to)
{
	_debouncing_flag = set_to;
}

extern TIM_HandleTypeDef htim4;
static int32_t encoder_counter = 0;
static int32_t last_encoder_counter = 0;
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (TIM4 == htim->Instance)
	{
		encoder_counter = (int32_t)(__HAL_TIM_GET_COUNTER(htim)/4);
		if (encoder_counter > last_encoder_counter)
		{
			menu_next();
			last_encoder_counter = encoder_counter;
		}
		else if (encoder_counter < last_encoder_counter)
		{
			menu_prev();
			last_encoder_counter = encoder_counter;
		}
	}
}

extern TIM_HandleTypeDef htim11;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (BTN_Pin == GPIO_Pin && FLAG_RESET == get_debouncing_flag())
	{
		/* Set the flag */
		set_debouncing_flag(FLAG_SET);
		/* Start the timer for 100 ms */
		__HAL_TIM_SET_AUTORELOAD(&htim11, 100);
		HAL_TIM_Base_Start_IT(&htim11);
	}
}

void my_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (TIM11 == htim->Instance)
	{
		/* Stop the timer, clear the flag */
		set_debouncing_flag(FLAG_RESET);
		HAL_TIM_Base_Stop_IT(&htim11);
		/* If we're here - we debounced successfully */
		 if (HAL_GPIO_ReadPin(BTN_GPIO_Port, BTN_Pin) == GPIO_PIN_RESET)
		{
			menu_enter();
		}
	}
}

void StartLCDTask(void *argument)
{
	/* Start encoder timer */
	HAL_TIM_Encoder_Start_IT(&htim4, TIM_CHANNEL_ALL);

	/* Initialize the menu, the display driver is initialized in main() */
	menu_init();

	while (1)
	{
		menu_refresh();
		osDelay(100);

		// Check if user interacted within last N seconds
		// if so then menu_refresh();
		// else menu_plots();
	}
}
