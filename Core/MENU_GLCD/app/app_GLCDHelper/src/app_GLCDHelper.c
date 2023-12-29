/******************************************************************************
 * Module: GLCD Helper
 *
 * File Name: app_GLCDHelper.c
 *
 * Description: Source file for the helper GLCD
 *
 * Author: Rahma Abdelhamid
 *
 * Created on: Nov 19, 2023
 *******************************************************************************/
/*******************************************************************************
 *                                   Includes
 *******************************************************************************/

#include "stm32l0xx_hal.h"
#include "hal_GLCD.h"
#include "app_GLCDHelper.h"



/*******************************************************************************
 *                                   Global Variables
 *******************************************************************************/
//uint8_t g_aData[7][9]= {"MAIN","GPS","100%",{'5','2','6'} ,"HDS","PLAIN","TX"};
//
//
//int8_t g_aKeyValue [3]={'5','2','6'};


/*******************************************************************************
 *                              Functions Definition                            *
 *******************************************************************************/
/**
 * \brief   This function is used to draw or remove rectangle on current screen area based color of line
 *
 *\param	ui16X		  start X of the rectangle
 *\param	ui16Y		  start Y of the rectangle
 *\param	ui16W         width of the rectangle
 *\param	ui16H         Height of the rectangle
 *\return	void
 **/
void APP_GLCD_SelectPage(uint16_t ui16X, uint16_t ui16Y, uint16_t ui16W, uint16_t ui16H, GLCD_COLOR_et etColor )
{
	HAL_GLCD_DrawRectangle(ui16X,ui16Y,ui16W,ui16H,etColor);
//	HAL_GLCD_UpdateScreen(ui16X, ui16Y, ui16X+122, ui16Y+10);
}

/**
 * \brief   This function is used to Display string on specific area on the screen
 *
 *\param	ui16X		  X position
 *\param	ui16Y		  Y position
 *\param	pData	   	  pointer to data to be displayed
 *\return	void
 **/
void APP_GLCD_DisplayStringOnScreen(uint16_t ui16X, uint16_t ui16Y,uint8_t* pData)
{
	HAL_GLCD_goTo (ui16X,ui16Y);
	HAL_GLCD_writeString (pData);
}

/**
 * \brief   This function is used to Display key value on specific area on the screen
 *
 *\param	ui16X		  X position
 *\param	ui16Y		  Y position
 *\param	digit	   	  digit of key value to  display
 *\return	void
 **/
void APP_GLCD_updateKeyValue(uint8_t ui8X,uint8_t ui8Y,int8_t digit)
{
	HAL_GLCD_goTo(ui8X, ui8Y);
	HAL_GLCD_writeChar(digit);
}

/**
 * \brief   This function is used to take the data and Display it on the screen
 *\param	etDisplay		display options
 *\param	ui8X            start point on X axis
 *\param	ui8Y            start point on Y axis
 *\param	pData           pointer to data to display
 *\param	KeyValue        value of each digit in key value to display
 *\return	void
 **/
void APP_GLCDHelper_Display(GLCD_DISPLAY_OPTION_et etDisplay ,uint8_t ui8X,uint8_t ui8Y,uint8_t* pData,int8_t KeyValue)
{
	switch(etDisplay)
	{
	//start of screen 1
	case TITLE:
		// mhtaga a call clear line
		APP_GLCD_DisplayStringOnScreen(ui8X,ui8Y,pData);
		break;
	case GPS:
		APP_GLCD_DisplayStringOnScreen(ui8X,ui8Y,pData);
		break;
	case BATTERY_PERCENTAGE:
		APP_GLCD_DisplayStringOnScreen(ui8X,ui8Y,pData);
		break;
	case KEY_INDEX:
		APP_GLCD_DisplayStringOnScreen(ui8X,ui8Y,pData);
		break;
	case DATA_SRC:
		APP_GLCD_DisplayStringOnScreen(ui8X,ui8Y,pData);
		break;
	case OPERATION_MODE:
		APP_GLCD_DisplayStringOnScreen(ui8X,ui8Y,pData);
		break;
	case STATE:
		APP_GLCD_DisplayStringOnScreen(ui8X,ui8Y,pData);
		break;  //end of screen 1
		//start of screen 2
	case SET_KEY:
		APP_GLCD_DisplayStringOnScreen(ui8X,ui8Y,pData);
		break;
	case KEY_VALUE:
		APP_GLCD_updateKeyValue(ui8X,ui8Y,KeyValue);
		break;     //end of screen 2
		//start of screen 3
	case SET_MODE:
		APP_GLCD_DisplayStringOnScreen(ui8X,ui8Y,pData);
		break;
	case PLAIN:
		APP_GLCD_DisplayStringOnScreen(ui8X,ui8Y,pData);
		break;
	case CIPHER:
		APP_GLCD_DisplayStringOnScreen(ui8X,ui8Y,pData);
		break;   //end of screen 3
		//start of screen 4
	case SET_DATA_SRC:
		APP_GLCD_DisplayStringOnScreen(ui8X,ui8Y,pData);
		break;
	case AUDIO:
		APP_GLCD_DisplayStringOnScreen(ui8X,ui8Y,pData);
		break;
	case ETHERNET:
		APP_GLCD_DisplayStringOnScreen(ui8X,ui8Y,pData);
		break;  //end of screen 4
	default:
		//nothing
		break;
	}
}

