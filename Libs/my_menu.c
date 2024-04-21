/*
 * my_menu.c
 *
 *  Created on: Mar 3, 2024
 *      Author: brzan
 */

#include "my_menu.h"

static m_mode_t mode;

static void _m_set_mode(const m_mode_t set_mode)
{
	mode = set_mode;
}

static const m_mode_t _m_get_mode(void){
	return mode;
}

static menu_t NONE_MENU = {"----NONE----", NULL, NULL, NULL, NULL, NULL}; /* Default menu_t element */
static menu_t *menu_current_ptr;		/* Global static current menu_t pointer */
static uint8_t cursor_position;			/* Global static cursor position */

// TODO parametrize below functions with x y1 y2 y3 and so on!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// todo in order to move them lower and incerase menu size ;)
// post this code on github!!!
static const uint8_t x = 0, d = 5;
static const uint8_t y1 = 1, y2 = 12, y3 = 23;
static void _my_draw_cursor(void)
{
	ssd1306_FillRectangle(x, y1, x+d, y3+d, White);
	switch (cursor_position) {
	case 0:
		ssd1306_FillRectangle(x, y1, x+d, y1+d, Black);
		ssd1306_DrawRectangle(x, y2, x+d, y2+d, Black);
		ssd1306_DrawRectangle(x, y3, x+d, y3+d, Black);
		break;
	case 1:
		ssd1306_DrawRectangle(x, y1, x+d, y1+d, Black);
		ssd1306_FillRectangle(x, y2, x+d, y2+d, Black);
		ssd1306_DrawRectangle(x, y3, x+d, y3+d, Black);
		break;
	case 2:
		ssd1306_DrawRectangle(x, y1, x+d, y1+d, Black);
		ssd1306_DrawRectangle(x, y2, x+d, y2+d, Black);
		ssd1306_FillRectangle(x, y3, x+d, y3+d, Black);
		break;
	}
}

static menu_t *top_line_ptr;
static menu_t *mdl_line_ptr;
static menu_t *btm_line_ptr;

static void _my_draw_menu(void)
{
	/* Clear screen */
	ssd1306_FillRectangle(10, 0, 127, 31, White);

	ssd1306_SetCursor(7, 0);
	if (top_line_ptr) ssd1306_WriteString(top_line_ptr->name, Font_7x10, Black);
	else ssd1306_WriteString("ERROR", Font_7x10, Black);

	ssd1306_SetCursor(7, 11);
	if (mdl_line_ptr) ssd1306_WriteString(mdl_line_ptr->name, Font_7x10, Black);
	else ssd1306_WriteString("ERROR", Font_7x10, Black);

	ssd1306_SetCursor(7, 22);
	if (btm_line_ptr) ssd1306_WriteString(btm_line_ptr->name, Font_7x10, Black);
	else ssd1306_WriteString("ERROR", Font_7x10, Black);
}

static void _my_draw_data(void)
{
	const uint8_t characters = 4;
	char buf[characters];

	if (top_line_ptr->data)
	{
		ssd1306_SetCursor(128 - 7 * characters, 0);
		if (top_line_ptr->data->aliases && top_line_ptr->data->aliases[*(top_line_ptr->data->data)])
		{
			sprintf(buf, "%s", top_line_ptr->data->aliases[*(top_line_ptr->data->data)]);
		}
		else
		{
			sprintf(buf, "%04d", *(top_line_ptr->data->data));
		}

		if (_m_get_mode() && menu_current_ptr == top_line_ptr)
		{
			ssd1306_WriteString(buf, Font_7x10, White);
		}
		else
		{
			ssd1306_WriteString(buf, Font_7x10, Black);
		}
	}
	if (mdl_line_ptr->data)
	{
		ssd1306_SetCursor(128 - 7 * characters, 11);
		if (mdl_line_ptr->data->aliases && mdl_line_ptr->data->aliases[*(mdl_line_ptr->data->data)])
		{
			sprintf(buf, "%s", mdl_line_ptr->data->aliases[*(mdl_line_ptr->data->data)]);
		}
		else
		{
			sprintf(buf, "%04d", *(mdl_line_ptr->data->data));
		}

		if (_m_get_mode() && menu_current_ptr == mdl_line_ptr)
		{
			ssd1306_WriteString(buf, Font_7x10, White);
		}
		else
		{
			ssd1306_WriteString(buf, Font_7x10, Black);
		}
	}
	if (btm_line_ptr->data)
	{
		ssd1306_SetCursor(128 - 7 * characters, 22);
		if (btm_line_ptr->data->aliases && btm_line_ptr->data->aliases[*(btm_line_ptr->data->data)])
		{
			sprintf(buf, "%s", btm_line_ptr->data->aliases[*(btm_line_ptr->data->data)]);
		}
		else
		{
			sprintf(buf, "%04d", *(btm_line_ptr->data->data));
		}

		if (_m_get_mode() && menu_current_ptr == btm_line_ptr)
		{
			ssd1306_WriteString(buf, Font_7x10, White);
		}
		else
		{
			ssd1306_WriteString(buf, Font_7x10, Black);
		}
	}
}

static void _my_plot(void)
{
	// TODO finish this plot and all
	ssd1306_Fill(White);
}


/* ---------------- Idle mode detection SECTION BEGIN ---------------- */
static uint8_t _tick_counter = 0;
static const uint8_t _tick_compare = 50;

/**
 * @brief 		Handles counter increment and mode switch when counter finishes
 * @note 		this could be incremented in appropriate function invoked from timer ISR
 */
static void _tick_update(void)
{
	if (_tick_counter < _tick_compare) _tick_counter++;
	else if (_tick_counter == _tick_compare) _m_set_mode(menu_screensaver_mode);
}

/**
 * @brief 		Handles counter reset when user interacts
 */
static void _tick_reset(void)
{
	_tick_counter = 0;
	if (menu_screensaver_mode == _m_get_mode()) _m_set_mode(menu_browse_mode);
}
/* ---------------- Idle mode detection SECTION END ---------------- */


/* ---------------- Interface layer SECTION BEGIN ---------------- */
// TODO remove those menu_t instances from here
extern menu_t MM1, MM2, MM3;
void menu_init(void)
{
	top_line_ptr = &MM1;
	mdl_line_ptr = &MM2;
	btm_line_ptr = &MM3;

	menu_current_ptr = top_line_ptr;
	cursor_position = 0;

	_m_set_mode(menu_browse_mode);
}

void menu_next(void)
{
	_tick_reset();
	if (menu_data_edit_mode == _m_get_mode())
	{
		if ((*(menu_current_ptr->data->data) + menu_current_ptr->data->delta_per_step)
				<= (menu_current_ptr->data->upper_bound))
		{
			*(menu_current_ptr->data->data) += (menu_current_ptr->data->delta_per_step);
		}
	}
	else if (menu_browse_mode == _m_get_mode() && menu_current_ptr->next)
	{
		menu_current_ptr = menu_current_ptr->next;
		if (cursor_position < 2)
		{
			cursor_position++;
		}
		else if (cursor_position == 2)
		{
			top_line_ptr = top_line_ptr->next;
			mdl_line_ptr = mdl_line_ptr->next;
			btm_line_ptr = btm_line_ptr->next;
		}
	}
}

void menu_prev(void)
{
	_tick_reset();
	if (menu_data_edit_mode == _m_get_mode())
	{
		if ((*(menu_current_ptr->data->data) - menu_current_ptr->data->delta_per_step)
				>= (menu_current_ptr->data->lower_bound))
		{
			*(menu_current_ptr->data->data) -= menu_current_ptr->data->delta_per_step;
		}
	}
	else if (menu_browse_mode == _m_get_mode() && menu_current_ptr->prev)
	{
		menu_current_ptr = menu_current_ptr->prev;
		if (cursor_position > 0)
		{
			cursor_position--;
		}
		else if (cursor_position == 0)
		{
			top_line_ptr = top_line_ptr->prev;
			mdl_line_ptr = mdl_line_ptr->prev;
			btm_line_ptr = btm_line_ptr->prev;
		}
	}
}

void menu_enter(void)
{
	_tick_reset();
	if (menu_current_ptr->data)
	{
		/* Data edit mode enter/exit */
		if (menu_data_edit_mode == _m_get_mode()) _m_set_mode(menu_browse_mode);
		else if (menu_browse_mode == _m_get_mode()) _m_set_mode(menu_data_edit_mode);
	}
	if (menu_current_ptr->go_to)
	{
		/* Goto specific menu, typically enter to menu or return from one */
		menu_current_ptr = menu_current_ptr->go_to;

		/* Display configuration */
		if (menu_current_ptr->next)
		{
			if (menu_current_ptr->next->next)
			{
				// current element is top, next two exists
				cursor_position = 0;
				top_line_ptr = menu_current_ptr;
				mdl_line_ptr = menu_current_ptr->next;
				btm_line_ptr = menu_current_ptr->next->next;
			}
			else if (menu_current_ptr->prev)
			{
				// current element is mdl, next and prev exists
				cursor_position = 1;
				top_line_ptr = menu_current_ptr->prev;
				mdl_line_ptr = menu_current_ptr;
				btm_line_ptr = menu_current_ptr->next;
			}
			else
			{
				// current element is top, next exists
				cursor_position = 0;
				top_line_ptr = menu_current_ptr;
				mdl_line_ptr = menu_current_ptr->next;
				btm_line_ptr = &NONE_MENU;
			}
		}
		else if (menu_current_ptr->prev)
		{
			if (menu_current_ptr->prev->prev)
			{
				// current element is btm, prev two exists
				cursor_position = 2;
				top_line_ptr = menu_current_ptr->prev->prev;
				mdl_line_ptr = menu_current_ptr->prev;
				btm_line_ptr = menu_current_ptr;
			}
			else
			{
				// current element is mdl, prev exists
				cursor_position = 1;
				top_line_ptr = menu_current_ptr->prev;
				mdl_line_ptr = menu_current_ptr;
				btm_line_ptr = &NONE_MENU;
			}
		}
		else
		{
			// current element is top, no next, no prev
			cursor_position = 0;
			top_line_ptr = menu_current_ptr;
			mdl_line_ptr = &NONE_MENU;
			btm_line_ptr = &NONE_MENU;
		}
	}
	if (menu_current_ptr->function)
	{
		/* Run a function */
		menu_current_ptr->function();
	}
}

void menu_refresh(void)
{
	/* This code fragment is responsible for idle detection */
	_tick_update();

	/* This fragment displays appropriate things based on mode */
	if (_m_get_mode() == menu_browse_mode || _m_get_mode() == menu_data_edit_mode)
	{
		_my_draw_cursor();
		_my_draw_menu();
		_my_draw_data();
	}
	if (_m_get_mode() == menu_screensaver_mode)
	{
		_my_plot();
	}

	ssd1306_UpdateScreen();
}
/* ---------------- Interface layer SECTION END ---------------- */
