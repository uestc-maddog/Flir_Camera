/*-----------------------------------------------------------------
 * Name:      flir_menu.c
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
 
/********************************************************************************************************
 *                                               INCLUDES
 ********************************************************************************************************/
/* System ralted */
#include "stm32f4xx_hal.h"
#include "flir_focusing.h"
#include "flir_lcd.h"
#include "lepton.h"
#include "flir_menu.h"

/********************************************************************************************************
 *                                                 MACROS
 ********************************************************************************************************/


/********************************************************************************************************
 *                                               CONSTANTS
 ********************************************************************************************************/

/********************************************************************************************************
 *                                               GLOBAL VARIABLES
 ********************************************************************************************************/
#define RE_TH_1   26
#define RE_TH_1_2 37
#define RE_TH_2_2 53
#define RE_TH_3_2 69

/********************************************************************************************************
 *                                               EXTERNAL VARIABLES
 ********************************************************************************************************/

	
/********************************************************************************************************
 *                                               EXTERNAL FUNCTIONS
 ********************************************************************************************************/


/********************************************************************************************************
 *                                               LOCAL VARIABLES
 ********************************************************************************************************/
extern flir_reticle_sta reticle_sta;
const uint8_t RETH[4] = {RE_TH_1, RE_TH_1_2, RE_TH_2_2, RE_TH_3_2};
const uint8_t reticle [] ={ 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 207, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 254, 15, 192, 15, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 240, 63, 192, 15, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 193, 255, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 207, 255, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 193, 255, 254, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 224, 7, 255, 255, 255, 255, 255, 240, 63, 192, 15, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 224, 7, 255, 255, 255, 255, 255, 254, 
15, 192, 15, 255, 255, 255, 255, 255, 255, 255, 255, 255, 254, 247, 255, 255, 
255, 255, 255, 255, 207, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 254, 247, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 252, 247, 255, 255, 255, 255, 255, 224, 255, 224, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 240, 7, 255, 255, 255, 255, 255, 192, 
127, 192, 127, 255, 255, 255, 255, 255, 255, 255, 255, 255, 227, 15, 255, 255, 
255, 255, 255, 219, 127, 223, 127, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
239, 255, 255, 255, 255, 255, 255, 219, 127, 223, 127, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 200, 127, 192, 127, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 224, 7, 255, 255, 255, 255, 255, 232, 255,
 224, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 224, 7, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 239, 119, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
239, 119, 255, 255, 255, 255, 255, 192, 127, 192, 127, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 239, 119, 255, 255, 255, 255, 255, 192, 127, 192, 127, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 239, 119, 255, 255, 255, 255, 255, 255, 127, 255, 127, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
127, 255, 127, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 247, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 247, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 247, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 224, 7, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 224, 7, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 247, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 247, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
247, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 224, 7, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 224, 7, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
248, 31, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 240, 15, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 231, 231, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 239, 247, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 239, 247, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 239, 247,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 231, 231, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 247, 239, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 224, 7, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 224, 7, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 239, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 239, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 239, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 239, 255, 255, 255, 255, 192, 15, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 192, 15, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 238, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 224, 7, 255, 255, 255, 223, 127, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 224, 7, 255, 255, 255, 192, 127, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 239, 119, 255, 255, 255, 224,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 239, 119, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 239, 119,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 239, 119, 255, 255, 255, 230, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 195, 127, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 217, 127, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 221, 127, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 192, 127, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 192, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 224, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 192, 127, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 223, 127, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 223, 127, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 206, 127, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 238, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 192,
 15, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 192, 15, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 249, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 224, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 198, 127, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 223, 127, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};

const uint8_t reticle_enable[]={ 255, 255, 255, 128, 255, 255, 255, 128, 
255, 255, 255, 128, 255, 255, 255, 128, 255, 255, 255, 128, 254, 0, 127,
 128, 254, 0, 127, 128, 254, 102, 127, 128, 254, 102, 127, 128, 254, 102, 
127, 128, 254, 127, 255, 128, 255, 255, 255, 128, 254, 3, 255, 128, 254, 3,
 255, 128, 255, 247, 255, 128, 255, 243, 255, 128, 254, 3, 255, 128, 254, 
3, 255, 128, 255, 255, 255, 128, 255, 127, 255, 128, 254, 19, 255, 128, 254,
 19, 255, 128, 254, 83, 255, 128, 254, 83, 255, 128, 254, 3, 255, 128, 254,
 7, 255, 128, 255, 255, 255, 128, 255, 255, 255, 128, 254, 0, 127, 128, 254,
 0, 127, 128, 255, 119, 255, 128, 254, 115, 255, 128, 254, 115, 255, 128,
 254, 3, 255, 128, 255, 7, 255, 128, 255, 207, 255, 128, 255, 255, 255, 128,
 254, 0, 127, 128, 254, 0, 127, 128, 255, 255, 255, 128, 255, 255, 255, 128,
 255, 7, 255, 128, 254, 3, 255, 128, 254, 83, 255, 128, 254, 83, 255, 128, 
254, 67, 255, 128, 254, 71, 255, 128, 255, 207, 255, 128, 255, 159, 255, 128,
 255, 7, 255, 128, 254, 3, 255, 128, 254, 115, 255, 128, 254, 115, 255, 128,
 255, 55, 255, 128, 254, 0, 127, 128, 254, 0, 127, 128, 255, 255, 255, 128,
 255, 255, 255, 128, 255, 255, 255, 128, 255, 255, 255, 128, 255, 255, 255,
 128, 255, 255, 255, 128, 255, 255, 255, 128, 255, 255, 255, 128};

const uint8_t reticle_disable[] ={ 255, 255, 255, 192, 255, 255, 255, 192, 
255, 255, 255, 192, 255, 255, 255, 192, 255, 255, 255, 192, 255, 255, 255, 
192, 255, 0, 63, 192, 255, 0, 63, 192, 255, 63, 63, 192, 255, 63, 63, 192, 
255, 63, 63, 192, 255, 30, 63, 192, 255, 128, 127, 192, 255, 192, 127, 192,
 255, 241, 255, 192, 255, 255, 255, 192, 255, 1, 63, 192, 255, 1, 63, 192,
 255, 255, 255, 192, 255, 255, 255, 192, 255, 35, 255, 192, 255, 33, 255,
 192, 255, 9, 255, 192, 255, 9, 255, 192, 255, 159, 255, 192, 255, 191, 255, 
192, 255, 9, 255, 192, 255, 9, 255, 192, 255, 41, 255, 192, 255, 41, 255,
 192, 255, 1, 255, 192, 255, 3, 255, 192, 255, 255, 255, 192, 255, 255, 
255, 192, 255, 0, 63, 192, 255, 0, 63, 192, 255, 187, 255, 192, 255, 57,
 255, 192, 255, 57, 255, 192, 255, 1, 255, 192, 255, 131, 255, 192, 255,
 231, 255, 192, 255, 255, 255, 192, 255, 0, 63, 192, 255, 0, 63, 192, 255,
 255, 255, 192, 255, 255, 255, 192, 255, 131, 255, 192, 255, 1, 255, 192,
 255, 41, 255, 192, 255, 41, 255, 192, 255, 33, 255, 192, 255, 35, 255, 
192, 255, 231, 255, 192, 255, 207, 255, 192, 255, 131, 255, 192, 255, 1, 
255, 192, 255, 57, 255, 192, 255, 57, 255, 192, 255, 155, 255, 192, 255,
 0, 63, 192, 255, 0, 63, 192, 255, 255, 255, 192, 255, 255, 255, 192, 255,
 255, 255, 192, 255, 255, 255, 192, 255, 255, 255, 192, 255, 255, 255, 192,
 255, 255, 255, 192, 255, 255, 255, 192, 255, 255, 255, 192};

const uint8_t front_number[19][14] = {
	
	{ 255, 192, 216, 192, 144, 64, 183, 64, 128, 64, 192, 192, 255, 192},
	{ 255, 192, 196, 192, 128, 64, 187, 64, 128, 64, 196, 192, 255, 192},
	{ 255, 192, 255, 64, 135, 64, 129, 64, 248, 64, 254, 64, 255, 192},
	{ 255, 192, 192, 192, 128, 64, 187, 64, 130, 64, 198, 192, 255, 192},
	{ 255, 192, 209, 192, 152, 64, 186, 64, 131, 64, 199, 64, 255, 192},
	{ 255, 192, 231, 192, 233, 192, 238, 192, 128, 64, 128, 64, 239, 192},
	{ 255, 192, 222, 192, 158, 64, 187, 64, 128, 64, 196, 192, 255, 192},
	{ 255, 192, 158, 192, 142, 64, 167, 64, 176, 64, 184, 192, 255, 192},
	{ 255, 192, 249, 192, 252, 192, 128, 64, 128, 64, 255, 192, 255, 192},	
	{ 255, 192, 192, 192, 128, 64, 191, 64, 128, 64, 192, 192, 255, 192},
	{ 255, 192, 249, 192, 252, 192, 128, 64, 128, 64, 255, 192, 255, 192},
	{ 255, 192, 158, 192, 142, 64, 167, 64, 176, 64, 184, 192, 255, 192},
	{ 255, 192, 222, 192, 158, 64, 187, 64, 128, 64, 196, 192, 255, 192},
	{ 255, 192, 231, 192, 233, 192, 238, 192, 128, 64, 128, 64, 239, 192},
	{ 255, 192, 209, 192, 152, 64, 186, 64, 131, 64, 199, 64, 255, 192},
	{ 255, 192, 192, 192, 128, 64, 187, 64, 130, 64, 198, 192, 255, 192},
	{ 255, 192, 255, 64, 135, 64, 129, 64, 248, 64, 254, 64, 255, 192},
	{ 255, 192, 196, 192, 128, 64, 187, 64, 128, 64, 196, 192, 255, 192},
	{ 255, 192, 216, 192, 144, 64, 183, 64, 128, 64, 192, 192, 255, 192},
};

const uint8_t po_and_negive[2][14] = {                                        // + -号
	{ 255, 192, 243, 192, 243, 192, 243, 192, 243, 192, 243, 192, 243, 192},
	{ 255, 192, 243, 192, 243, 192, 192, 192, 192, 192, 243, 192, 243, 192},
};
	



 //bool Focus_en=1;   //表示瞄准器状态。
 
 uint8_t Hor=9;   //瞄准器水平坐标  0-19  对应-9到9
 uint8_t Ver=9;		//瞄准器竖直坐标	0-19  对应-9到9

 
/********************************************************************************************************
 *                                               LOCAL FUNCTIONS
 ********************************************************************************************************/

 
/********************************************************************************************************
 *                                               PUBLIC FUNCTIONS
 ********************************************************************************************************/
/*********************************************************************
 * @fn      Show_focusing
 *
 * @brief   show focusing lines
 *
 * @param   none
 *
 * @return  
 */
void Add_focusing(int *Offset)
{
	int i = 0;
	int Offset_X1 = focus_x1 + Offset[0];           // X轴偏移  短轴
	int Offset_X2 = focus_x2 + Offset[0];
	int Offset_Y1 = focus_y1 + Offset[1];           // Y轴偏移  长轴
	int Offset_Y2 = focus_y2 + Offset[1];
	
	
	for(i = 0; i < focus_lenth; i++)          // 分别围绕4个顶点画对焦线（2像素）   
	{
		rowBuf[Offset_X1][Offset_Y1+i] = ~rowBuf[Offset_X1][Offset_Y1+i];
		rowBuf[Offset_X1+1][Offset_Y1+i] = ~rowBuf[Offset_X1+1][Offset_Y1+i];  
		
		rowBuf[Offset_X1+i][Offset_Y1] = ~rowBuf[Offset_X1+i][Offset_Y1];
		rowBuf[Offset_X1+i][Offset_Y1+1] = ~rowBuf[Offset_X1+i][Offset_Y1+1];
	}
	
	for(i = 0; i < focus_lenth; i++)
	{
		rowBuf[Offset_X1][Offset_Y2-i] = ~rowBuf[Offset_X1][Offset_Y2-i];
		rowBuf[Offset_X1+1][Offset_Y2-i] = ~rowBuf[Offset_X1+1][Offset_Y2-i];
		rowBuf[Offset_X1+i][Offset_Y2] = ~rowBuf[Offset_X1+i][Offset_Y2];
		rowBuf[Offset_X1+i][Offset_Y2+1] = ~rowBuf[Offset_X1+i][Offset_Y2+1];
	}
	
	for(i = 0; i < focus_lenth; i++)
	{
		rowBuf[Offset_X2][Offset_Y1+i] = ~rowBuf[Offset_X2][Offset_Y1+i];
		rowBuf[Offset_X2+1][Offset_Y1+i] = ~rowBuf[Offset_X2+1][Offset_Y1+i];
		rowBuf[Offset_X2-i][Offset_Y1] = ~rowBuf[Offset_X2-i][Offset_Y1];
		rowBuf[Offset_X2-i][Offset_Y1+1] = ~rowBuf[Offset_X2-i][Offset_Y1+1];
	}
	
	for(i = 0; i < focus_lenth; i++)
	{
		rowBuf[Offset_X2][Offset_Y2-i] = ~rowBuf[Offset_X2][Offset_Y2-i];
		rowBuf[Offset_X2+1][Offset_Y2-i] = ~rowBuf[Offset_X2+1][Offset_Y2-i];
		rowBuf[Offset_X2-i][Offset_Y2] = ~rowBuf[Offset_X2-i][Offset_Y2];
		rowBuf[Offset_X2-i][Offset_Y2+1] = ~rowBuf[Offset_X2-i][Offset_Y2+1];
	}
}

void setreticle_display(void)
{
	uint8_t i,index;
	uint8_t m;   //显示正负号中间量
	uint8_t menuTHstart, menuTHend;
				//显示一到三行
	
	if((uint8_t)(reticle_sta) < 4&&(uint8_t)(reticle_sta) > 0)
	{
		// use the enum define to get the const array value
		menuTHstart = RETH[3-(uint8_t)(reticle_sta)];
			// use the enum define to get the const array value
		menuTHend = RETH[4-(uint8_t)(reticle_sta)];
	}
	else
	{
		menuTHstart = 0;
		menuTHend = 0;
	}
	
	
	for(index = 1;index < 128; index++)
	{
		for(i = 1; i < 160 ;i ++)
		{
			if((i < menuTHstart) || (i > menuTHend))
			{
				if(((reticle[(index * 160 + i) >> 3] >> (7 - (index * 160 + i)%8))&0x01) != 0x01)
					rowBuf[index][i]=WHITE;
			}
			else
			{
				if(((reticle[(index * 160 + i) >> 3] >> (7 - (index * 160 + i)%8))&0x01) != 0x01)
					rowBuf[index][i]=0xe0ff;
			}
		}
	}
	if(flir_conf.flir_sys_Focus == focus_enable)    //如果瞄准框是开启就显示enable否则显示disable
	//if(Focus_en==focus_enable)   //如果瞄准框是开启就显示enable否则显示disable
	{
		for(index = 0;index < 64; index++)
		{
			for(i = 0; i < 25 ;i ++)
			{
				if(((reticle_enable[(index * 32 + i) >> 3] >> (7 - (index * 32 + i)%8))&0x01) != 0x01)
				{
					if(reticle_sta == reticle_able)
						rowBuf[index+12][i+120]=0xe0ff;
					else
						rowBuf[index+12][i+120]=WHITE;
				}
			}
		}
	}
	else
	{
		for(index = 0;index < 64; index++)
		{
			for(i = 0; i < 25 ;i ++)
			{
				if(((reticle_disable[(index * 32 + i) >> 3] >> (7 - (index * 32 + i)%8))&0x01) != 0x01)
				{
					if(reticle_sta == reticle_able)
						rowBuf[index+12][i+120]=0xe0ff;
					else
						rowBuf[index+12][i+120]=WHITE;
				}
			}
		}		
	}
	//显示HOR正负号
	for(index = 0;index < 7; index++)
	{
			if(Hor==18)
				m=17;   //显示正号
			else
				m=Hor;
		for(i = 0; i < 10 ;i ++)
		{ 
			if((((po_and_negive[(m)/9][(index * 16 + i) >> 3] >> (7 - (index * 16 + i)%8))&0x01) != 0x01)&&m != 9)
				{
					if(reticle_sta == reticle_Hor)
						rowBuf[index+35][i+58]=0xe0ff;
					else
						rowBuf[index+35][i+58]=WHITE;
				}
		}
	}
	//显示HOR值
	for(index = 0;index < 7; index++)
	{
		for(i = 0; i < 10 ;i ++)
		{
			if(((front_number[Hor][(index * 16 + i) >> 3] >> (7 - (index * 16 + i)%8))&0x01) != 0x01)
				{
					if(reticle_sta == reticle_Hor)
						rowBuf[index+42][i+58]=0xe0ff;
					else
						rowBuf[index+42][i+58]=WHITE;
				}
		}
	}
		//显示VER正负号
	for(index = 0;index < 7; index++)
	{
			if(Ver==18)
				m=17;   //显示正号
			else
				m=Ver;
		for(i = 0; i < 10 ;i ++)
		{
			
			if((((po_and_negive[(m)/9][(index * 16 + i) >> 3] >> (7 - (index * 16 + i)%8))&0x01) != 0x01)&&m != 9)
				{
					if(reticle_sta == reticle_Ver)
						rowBuf[index+35][i+42]=0xe0ff;
					else
						rowBuf[index+35][i+42]=WHITE;
				}
		}
	}
		//显示VER值
	for(index = 0;index < 7; index++)
	{
		for(i = 0; i < 10 ;i ++)
		{
			if(((front_number[Ver][(index * 16 + i) >> 3] >> (7 - (index * 16 + i)%8))&0x01) != 0x01)
				{
					if(reticle_sta == reticle_Ver)
						rowBuf[index+42][i+42]=0xe0ff;
					else
						rowBuf[index+42][i+42]=WHITE;
				}
		}
	}
	

}
 /********************************************************************************************************
 *                                               LOCAL FUNCTIONS
 ********************************************************************************************************/

/*********************************************************************
 * @fn      
 *
 * @brief   
 *
 * @param   
 *
 * @return  
 */


/*********************************************************************
 */

