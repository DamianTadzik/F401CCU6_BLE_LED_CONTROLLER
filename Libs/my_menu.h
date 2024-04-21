/*
 * my_menu.h
 *
 *  Created on: Mar 3, 2024
 *      Author: brzan
 */

#ifndef INC_MY_MENU_H_
#define INC_MY_MENU_H_

#include <stdint.h>
#include <stdio.h>
#include "ssd1306.h"

#include "my_plot.h"

typedef struct menu_t{
	const char* name;				/* Name stored in flash */

	struct menu_t * next;			/* Pointer to next menu element */
	struct menu_t * prev;			/* Pointer to prev menu element */

	/* Only one of the three following must be provided */
	struct menu_t * go_to;			/* Pointer to change menu level */
	struct m_data_t * data;			/* Pointer to a constrained data type */
	void (*function)(void);			/* Pointer to a function */
} menu_t;

typedef struct m_data_t{
	int * data;
	int lower_bound;
	int upper_bound;
	int delta_per_step;
	const char * const * aliases;
} m_data_t;

typedef enum{
	menu_browse_mode,
	menu_data_edit_mode,
	menu_screensaver_mode
} m_mode_t;

/**
 *
 */
void menu_init(void);

/**
 *
 */
void menu_next(void);

/**
 *
 */
void menu_prev(void);

/**
 *
 */
void menu_enter(void);

/**
 *
 */
void menu_refresh(void);


#endif /* INC_MY_MENU_H_ */
