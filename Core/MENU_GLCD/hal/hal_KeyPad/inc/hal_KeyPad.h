/******************************************************************************
 * Module: KeyPad
 *
 * File Name: hal_KeyPad.h
 *
 * Description: Header file for the KeyPad
 *
 * Author: Rahma Abdelhamid
 *
 * Created on: Nov 2, 2023
 *******************************************************************************/

#ifndef MENU_GLCD_HAL_HAL_KEYPAD_INC_HAL_KEYPAD_H_
#define MENU_GLCD_HAL_HAL_KEYPAD_INC_HAL_KEYPAD_H_

/*******************************************************************************
*                               includes                             *
*******************************************************************************/
#include "stdint.h"
/*******************************************************************************
*                                Definitions                                  *
*******************************************************************************/
#define KEYPAD_PORT_ID         GPIOB
#define KEYPAD_PIN_UP          GPIO_PIN_1
#define KEYPAD_PIN_DOWN        GPIO_PIN_4
#define KEYPAD_PIN_RIGHT       GPIO_PIN_5
#define KEYPAD_PIN_LEFT        GPIO_PIN_6
#define KEYPAD_PIN_OK          GPIO_PIN_7

/*******************************************************************************
*                               Types Declaration                             *
*******************************************************************************/

typedef enum {
	KEYPAD_BUTTON_PRESSED,
	KEYPAD_BUTTON_RELEASED
} KEYPAD_BUTTON_STATE_et;

typedef enum {
	KEYPAD_BUTTON_NO_ONE,
	KEYPAD_BUTTON_UP,
	KEYPAD_BUTTON_DOWN,
	KEYPAD_BUTTON_RIGHT,
	KEYPAD_BUTTON_LEFT,
	KEYPAD_BUTTON_OK
} KEYPAD_BUTTON_DIRECTION_et;


/*******************************************************************************
*                                Extern Variables                                 *
*******************************************************************************/

extern KEYPAD_BUTTON_DIRECTION_et etBtnDir;

/*******************************************************************************
 *                             Function Declaration                             *
 *******************************************************************************/

KEYPAD_BUTTON_STATE_et     HAL_KEYBAD_BtnState(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
KEYPAD_BUTTON_DIRECTION_et HAL_KEYPAD_getPressedKey(void);



#endif /* MENU_GLCD_HAL_HAL_KEYPAD_INC_HAL_KEYPAD_H_ */
