/*-----------------------------------------------------------------
 * Name:      menufounction.h
 * Purpose:   
 *-----------------------------------------------------------------
 * 
 * Copyright (c) *reserve
 
||                       _      _               ||
||    /\  /\  __  _  __ | | __ | | ____  ___ _  ||
||   /  \/  \/ _ ` |/ _ ` |/ _ ` |/ _  \/ _ ` | ||
||  / /\  /\  (_|    (_|    (_|    (_)   (_)  | ||
|| /_/  \/  \_.__, |\__, _|\__, _|\____/\___. | ||
|| =====================================|____/  ||
||                                              ||

 -----------------------------------------------------------------*/
 #ifndef MENUFOUNCTING_H_
 #define MENUFOUNCTING_H_
 
/********************************************************************************************************
 *                                     

INCLUDES
 ********************************************************************************************************/
/* System ralted */
#include "stm32f4xx_hal.h"
#include "flir_lcd.h"

#define enable_iwdg 1             // 开启IWDG看门狗
//#define enable_iwdg 0             // 关闭IWDG看门狗

void Brightnesschosen(void);
void Sleepchosen(void);
void Versionchosen(void);
void set_reticle(void);

extern bool set_reticle_mark;

#endif


