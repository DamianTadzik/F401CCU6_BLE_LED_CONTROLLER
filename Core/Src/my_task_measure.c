/*
 * my_task_measure.c
 *
 *  Created on: May 16, 2024
 *      Author: brzan
 */
#include "main.h"
#include "cmsis_os2.h"

extern osMutexId_t mutexI2C1Handle;
extern I2C_HandleTypeDef hi2c1;
const uint8_t bme280_address = (0x76 << 1);

void StartMeasureTask(void *argument)
{
	osDelayUntil(1000);
	HAL_StatusTypeDef status;

	while (osMutexAcquire(mutexI2C1Handle, 0) != osOK)
	{
		osDelay(1);
	}
	// config 0xF5
		// [7:5] t_sb[2:0]			0x05 - 1000 ms standby
		// [4:2] filter[2:0] 		0x02 - Filter coef. 4
		// [0]   spi3w_en[0]		0x00 - SPI off
	// ctrl_hum 0xF2
		// [2:0] osrs_h[2:0]		0x03 - x4 over sampling
	// ctrl_meas 0xF4
		// [7:5] osrs_t[2:0]		0x03 - x4 over sampling
		// [4:2] osrs_p[2:0]		0x03 - x4 over sampling
		// [1:0] mode[1:0]			0x03 - Normal mode
	status = HAL_I2C_Mem_Write(&hi2c1, bme280_address, MemAddress, 1, pData, 1, Timeout);

	osMutexRelease(mutexI2C1Handle);

	while (1)
	{
		if (osMutexAcquire(mutexI2C1Handle, 20) == osOK)
		{
//			status = HAL_I2C_Mem_Read(&hi2c1, bme280_address, 0xF3, 1, &data, 1, 100);


			UNUSED(status);
			osMutexRelease(mutexI2C1Handle);
		}
		osDelay(1000);
	}
}
