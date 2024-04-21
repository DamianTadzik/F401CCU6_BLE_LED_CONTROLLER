/*
 * my_menu_structure.h
 *
 *  Created on: Mar 6, 2024
 *      Author: brzan
 */

#ifndef INC_MY_MENU_STRUCTURE_H_
#define INC_MY_MENU_STRUCTURE_H_

#include "my_menu.h"
//#include "hm10.h"

extern menu_t MM1, MM2, MM3, MM4, MM5, MM6;
extern menu_t AM1, AM2, AM3;
extern menu_t EEM1, EEM2, EEM3;

extern m_data_t D_E, D_ATC;

//extern void send_AT_command(void);

// TODO update menu init fucntion so MM2 MM3 and MM1 are not used xd

#define ASSERT_ENUM_ALIASES(sarray, max) \
  typedef char assert_sizeof_##max[(sizeof(sarray)/sizeof(sarray[0]) == (max)) ? 1 : -1]

#endif /* INC_MY_MENU_STRUCTURE_H_ */
