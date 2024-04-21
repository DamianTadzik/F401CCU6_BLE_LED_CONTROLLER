/*
 * my_plot.h
 *
 *  Created on: Apr 21, 2024
 *      Author: brzan
 */

#ifndef MY_PLOT_H_
#define MY_PLOT_H_

#include "ssd1306.h"

#define BUF_SZ 1 << 8

void plot_axes(void);

typedef enum {
	p_tsc_default,
	p_tsc_2h,
	p_tsc_1h	// todo finish this
} plot_timescale_t;

#endif /* MY_PLOT_H_ */
