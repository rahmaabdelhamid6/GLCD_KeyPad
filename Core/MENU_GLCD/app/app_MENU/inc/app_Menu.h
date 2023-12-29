/******************************************************************************
 * Module: Menu App
 *
 * File Name: app_Menu.c
 *
 * Description: Source file for the Menu APP
 *
 * Author: Rahma Abdelhamid
 *
 * Created on: Nov 20, 2023
 *******************************************************************************/

#ifndef MENU_GLCD_APP_APP_MENU_INC_APP_MENU_H_
#define MENU_GLCD_APP_APP_MENU_INC_APP_MENU_H_

/*******************************************************************************
 *                               includes                             *
 *******************************************************************************/
#include "stdint.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define TRUE    1
#define FALSE   0
#define TIMEOUT_DURATION    10000

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum {
	MAIN_SCREEN = 1,
	SET_KEY_SCREEN,
	SET_MODE_SCREEN,
	SET_SOURCE_SCREEN
}SCREEN_NAME_et;

/*******************************************************************************
 *                                Extern Variables                                 *
 *******************************************************************************/
extern KEYPAD_BUTTON_DIRECTION_et g_etBtnDirection;
extern SCREEN_NAME_et etScreenName;
extern SCREEN_NAME_et etScrName;
extern uint8_t g_aData[20][16];
extern uint8_t g_aKeyValue [3];

/*******************************************************************************
 *                             Function Declaration                             *
 ********************************************************************************/

void APP_MENU_Screen_TimeOut( KEYPAD_BUTTON_DIRECTION_et etBtnDirection, uint32_t* ui32Time);

void APP_MENU_RightLeftButton_ChangeDirection(KEYPAD_BUTTON_DIRECTION_et etBtnDirection);

void APP_MENU_UpDownOkButton_ChangeDirection(KEYPAD_BUTTON_DIRECTION_et etBtnDirection);

void APP_MENU_MainScreen_Display(void);

SCREEN_NAME_et APP_MENU_GetScreenName(KEYPAD_BUTTON_DIRECTION_et etBtnDirection);

void APP_MENU_Action(void );





#endif /* MENU_GLCD_APP_APP_MENU_INC_APP_MENU_H_ */
