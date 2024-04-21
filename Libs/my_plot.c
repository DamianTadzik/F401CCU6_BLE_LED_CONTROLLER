/*
 * my_plot.c
 *
 *  Created on: Apr 21, 2024
 *      Author: brzan
 */

#include "my_plot.h"

/*
 * @note 	display used in this project has first 16 rows of pixels yellow [0 15] and rest is blue [16 63]
 * 			and horizontally it has 128 columns [0 127]
 */

//static uint8_t display_buffer[200];

static plot_timescale_t _tsc_temp = p_tsc_default;


void plot_axes(void)
{
	/* Draw vertical axis */
	const uint8_t _x = 10;
	ssd1306_Line(_x, 16, _x, 63, Black);
	/* Draw ticks on vertical axis */
	const uint8_t y0 = 63, y1 = 16;
	ssd1306_Line(_x-2, y0, _x+2, y0, Black);
	ssd1306_Line(_x-2, y1, _x+2, y1, Black);

	/* Draw horizontal axis */
	const uint8_t _y = 13;
	ssd1306_Line(0, _y, 127, _y, Black);
	/* Draw ticks on horizontal axis */
	const uint8_t x0 = 126, x1 = _x;
	ssd1306_Line(x0, _y-2, x0, _y+2, Black);
	ssd1306_Line(x1, _y-2, x1, _y+2, Black);

	/* Draw numbers on vertical axis */
	ssd1306_SetCursor(0, 16);
	ssd1306_WriteString("b", Font_6x8, Black);
	ssd1306_SetCursor(0, 56);
	ssd1306_WriteString("a", Font_6x8, Black);

	/* Draw numbers on horizontal axis */
	switch (_tsc_temp)
	{
	case p_tsc_default:
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("-t", Font_7x10, Black);
		ssd1306_SetCursor(121, 0);
		ssd1306_WriteString("0", Font_7x10, Black);
		break;
	default:
		break;
	}
}
