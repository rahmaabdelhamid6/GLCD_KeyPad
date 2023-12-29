/******************************************************************************
 * Module: GLCD Helper
 *
 * File Name: app_GLCDHelper.h
 *
 * Description: Header file for the helper GLCD
 *
 * Author: Rahma Abdelhamid
 *
 * Created on: Nov 19, 2023
 *******************************************************************************/

#ifndef MENU_GLCD_APP_APP_GLCDHELPER_INC_APP_GLCDHELPER_H_
#define MENU_GLCD_APP_APP_GLCDHELPER_INC_APP_GLCDHELPER_H_

#include "hal_GLCD.h"

/*******************************************************************************
*                                Definitions                                  *
*******************************************************************************/


#define  GLCD_RECTANGLE_WIDTH      127
#define  GLCD_RECTANGLE_HEIGHT     10
#define  GLCD_RECTANGLE_START_X    3

/***********************************************128*64***********************************/
///***********SCREEN 1*******************/
//#define  GLCD_TITLE_X              53
//#define  GLCD_TITLE_Y              1
//#define  GLCD_GPS_X                3
//#define  GLCD_GPS_Y                19
//#define  GLCD_BAT_PERC_X           104
//#define  GLCD_BAT_PERC_Y           19
//#define  GLCD_KEY_INDEX_X          57
//#define  GLCD_KEY_INDEX_Y          37
//#define  GLCD_DATA_SRC_X           1
//#define  GLCD_DATA_SRC_Y           55
//#define  GLCD_OP_MODE_X            49
//#define  GLCD_OP_MODE_Y            55
//#define  GLCD_STATE_X              116
//#define  GLCD_STATE_Y              55
//
///***********SCREEN 2*******************/
//#define  GLCD_SET_KEY_X            48
//#define  GLCD_SET_KEY_Y            2
//#define  GLCD_KEY_VALUE_X1         54
//#define  GLCD_KEY_VALUE_X2         61  //54+5(font)+2(space)
//#define  GLCD_KEY_VALUE_X3         68   //61+5+2
//#define  GLCD_KEY_VALUE_Y          19
//#define  GLCD_KEY_VALUE_Y_LINE     32
//
///***********SCREEN 3*******************/
//#define  GLCD_SET_MODE_X            46
//#define  GLCD_SET_MODE_Y            1       //2
//#define  GLCD_PLAIN_MODE_X          52
//#define  GLCD_PLAIN_MODE_Y          19
//#define  GLCD_CIPHER_MODE_X         49
//#define  GLCD_CIPHER_MODE_Y         37
//#define  GLCD_APPLIED_MODE_X        47
//#define  GLCD_APPLIED_MODE_Y        55
//
//#define  GLCD_STAR_X                2

/***********************************************128*32***********************************/

/***********SCREEN 1*******************/
#define  GLCD_TITLE_X              53
#define  GLCD_TITLE_Y              0
#define  GLCD_GPS_X                3
#define  GLCD_GPS_Y                1
#define  GLCD_BAT_PERC_X           104
#define  GLCD_BAT_PERC_Y           1
#define  GLCD_KEY_INDEX_X          57
#define  GLCD_KEY_INDEX_Y          2
#define  GLCD_DATA_SRC_X           1
#define  GLCD_DATA_SRC_Y           3
#define  GLCD_OP_MODE_X            49
#define  GLCD_OP_MODE_Y            3
#define  GLCD_STATE_X              116
#define  GLCD_STATE_Y              3

/***********SCREEN 2*******************/
#define  GLCD_SET_KEY_X            48
#define  GLCD_SET_KEY_Y            0
#define  GLCD_KEY_VALUE_X1         54
#define  GLCD_KEY_VALUE_X2         61  //54+5(font)+2(space)
#define  GLCD_KEY_VALUE_X3         68   //61+5+2
#define  GLCD_KEY_VALUE_Y          1
#define  GLCD_KEY_VALUE_Y_LINE     20

/***********SCREEN 3*******************/
#define  GLCD_SET_MODE_X            46
#define  GLCD_SET_MODE_Y            0      //2
#define  GLCD_PLAIN_MODE_X          52
#define  GLCD_PLAIN_MODE_Y          1
#define  GLCD_CIPHER_MODE_X         49
#define  GLCD_CIPHER_MODE_Y         2
#define  GLCD_APPLIED_MODE_X        47
#define  GLCD_APPLIED_MODE_Y        3

#define  GLCD_STAR_X                2

/***********SCREEN 4*******************/
#define  GLCD_SET_DATA_SRC_X        44
#define  GLCD_SET_DATA_SRC_Y        1
#define  GLCD_AUDIO_X               52
#define  GLCD_AUDIO_Y               2
#define  GLCD_ETHERNET_X            44
#define  GLCD_ETHERNET_Y            3


/*******************************************************************************
*                               Types Declaration                             *
*******************************************************************************/
typedef enum {
	TITLE,
	GPS,
	BATTERY_PERCENTAGE,
	KEY_INDEX,
	DATA_SRC,
	OPERATION_MODE,
	STATE,
	SET_KEY,
	KEY_VALUE,
	SET_MODE,
	PLAIN,
	CIPHER,
	SET_DATA_SRC,
	AUDIO,
	ETHERNET

} GLCD_DISPLAY_OPTION_et;




/*******************************************************************************
*                              Functions Declaration                          *
*******************************************************************************/

void APP_GLCD_SelectPage(uint16_t ui16X, uint16_t ui16Y, uint16_t ui16W, uint16_t ui16H, GLCD_COLOR_et etColor);

void APP_GLCD_DisplayStringOnScreen(uint16_t ui16X, uint16_t ui16Y,uint8_t* pData);

void APP_GLCD_updateKeyValue(uint8_t ui8X,uint8_t ui8Y,int8_t digit);

void APP_GLCDHelper_Display(GLCD_DISPLAY_OPTION_et etDisplay , uint8_t ui8X, uint8_t ui8Y,uint8_t* pData,int8_t KeyValue);







#endif /* MENU_GLCD_APP_APP_GLCDHELPER_INC_APP_GLCDHELPER_H_ */
