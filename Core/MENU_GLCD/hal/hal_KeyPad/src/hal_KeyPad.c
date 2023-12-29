/******************************************************************************
 * Module: KeyPad
 *
 * File Name: hal_KeyPad.c
 *
 * Description: Source file for the KeyPad
 *
 * Author: Rahma Abdelhamid
 *
 * Created on: Nov 2, 2023
 *******************************************************************************/

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "stm32l0xx_hal.h"
#include "stdlib.h"
#include "hal_KeyPad.h"

/*******************************************************************************
 *                               Global Variables                             *
 *******************************************************************************/
KEYPAD_BUTTON_DIRECTION_et etBtnDir =KEYPAD_BUTTON_NO_ONE;
KEYPAD_BUTTON_STATE_et  etBtnState=KEYPAD_BUTTON_RELEASED;

/*******************************************************************************
 *                              Function Definition                            *
 *******************************************************************************/
/**
 * \brief   This function is used to Get the state of the button if pressed or released
 *
 *\param	GPIOx         port number
 *\param	GPIO_Pin      pin number
 *\return	KEYPAD_BUTTON_DIRECTION_et  return the button state
 **/
KEYPAD_BUTTON_STATE_et HAL_KEYBAD_BtnState(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)==GPIO_PIN_RESET )
	{
		etBtnState= KEYPAD_BUTTON_PRESSED;
	}
	else
	{
		etBtnState= KEYPAD_BUTTON_RELEASED;
	}
	return etBtnState;
}

/**
 * \brief   This function is used to Get the Keypad pressed button
 *
 *\param	void
 *\return	KEYPAD_BUTTON_DIRECTION_et  return the pressed button state
 **/
KEYPAD_BUTTON_DIRECTION_et HAL_KEYPAD_getPressedKey(void)
{
	if (HAL_KEYBAD_BtnState(KEYPAD_PORT_ID, KEYPAD_PIN_UP)==KEYPAD_BUTTON_PRESSED )
	{
		HAL_Delay(30);
		if (HAL_KEYBAD_BtnState(KEYPAD_PORT_ID, KEYPAD_PIN_UP)==KEYPAD_BUTTON_PRESSED )
		{
			etBtnDir= KEYPAD_BUTTON_UP;
		}
	}
	else if (HAL_KEYBAD_BtnState(KEYPAD_PORT_ID, KEYPAD_PIN_DOWN)==KEYPAD_BUTTON_PRESSED )
	{
		HAL_Delay(30);
		if (HAL_KEYBAD_BtnState(KEYPAD_PORT_ID, KEYPAD_PIN_DOWN)==KEYPAD_BUTTON_PRESSED )
		{
			etBtnDir= KEYPAD_BUTTON_DOWN;
		}
	}
	else if (HAL_KEYBAD_BtnState(KEYPAD_PORT_ID, KEYPAD_PIN_RIGHT)==KEYPAD_BUTTON_PRESSED )
	{
		HAL_Delay(30);
		if (HAL_KEYBAD_BtnState(KEYPAD_PORT_ID, KEYPAD_PIN_RIGHT)==KEYPAD_BUTTON_PRESSED )
		{
			etBtnDir= KEYPAD_BUTTON_RIGHT;
		}
	}
	else if (HAL_KEYBAD_BtnState(KEYPAD_PORT_ID, KEYPAD_PIN_LEFT)==KEYPAD_BUTTON_PRESSED )
	{
		HAL_Delay(30);
		if (HAL_KEYBAD_BtnState(KEYPAD_PORT_ID, KEYPAD_PIN_LEFT)==KEYPAD_BUTTON_PRESSED )
		{
			etBtnDir= KEYPAD_BUTTON_LEFT;
		}
	}
	else if (HAL_KEYBAD_BtnState(KEYPAD_PORT_ID, KEYPAD_PIN_OK)==KEYPAD_BUTTON_PRESSED )
	{
		HAL_Delay(30);
		if (HAL_KEYBAD_BtnState(KEYPAD_PORT_ID, KEYPAD_PIN_OK)==KEYPAD_BUTTON_PRESSED )
		{
			etBtnDir= KEYPAD_BUTTON_OK;
		}
	}
	else
	{
		etBtnDir= KEYPAD_BUTTON_NO_ONE;
	}
	return etBtnDir;
}
