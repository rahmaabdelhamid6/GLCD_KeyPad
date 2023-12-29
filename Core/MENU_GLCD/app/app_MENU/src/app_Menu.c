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

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/

#include "stm32l0xx_hal.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "hal_GLCD.h"
#include "hal_KeyPad.h"
#include "app_GLCDHelper.h"
#include "app_Menu.h"

/*******************************************************************************
 *                               Global Variables                             *
 *******************************************************************************/

SCREEN_NAME_et etScrNameHelper= MAIN_SCREEN;
SCREEN_NAME_et etScreenName= MAIN_SCREEN;
char g_ui8KeyValue='0';
uint8_t g_aData[20][16]= {"MAIN","GPS","100%",{'5','2','6'} ,"HDS","PLAIN ","TX", "SET KEY", "SET MODE", "PLAIN ","CIPHER ", "SET SOURCE", "AUDIO" , "ETHERNET" , "APPLIED" , "DONE" , "       ","HDS", "ETH", " * "};
uint8_t g_aKeyValue [3]={'5','2','6'};
uint8_t g_ui8CountScrName =1;
KEYPAD_BUTTON_DIRECTION_et g_etBtnDirection = KEYPAD_BUTTON_NO_ONE;   //right or left
KEYPAD_BUTTON_DIRECTION_et g_etBtnDirHelper = KEYPAD_BUTTON_NO_ONE;  //up or down

/*******************************************************************************
 *                              Function Definition                            *
 *******************************************************************************/
/**
 * \brief   This function is used to display main screen if user didn't press any button after specified period
 *
 *\param	etBtnDirHelper		  to store the direction of pressed button
 *\param	ui32Time		      used to get the period from the systick timer to be compared with Timeout period
 *\return	void
 **/

void APP_MENU_Screen_TimeOut( KEYPAD_BUTTON_DIRECTION_et etBtnDirection, uint32_t* ui32Time)
{
	etBtnDirection = HAL_KEYPAD_getPressedKey();
	if (*ui32Time >= TIMEOUT_DURATION)
	{
		if (etBtnDirection == KEYPAD_BUTTON_NO_ONE)
		{
			*ui32Time = 0; // Reset screen timeout counter
			g_ui8CountScrName = 1;  //3chan myghyrsh etScreenName based 3la right or left f yba'a ta'seer el up w el down mch mtshaf
			HAL_GLCD_ClearScreen();

			while (etBtnDirection == KEYPAD_BUTTON_NO_ONE)
			{
				APP_MENU_MainScreen_Display();
				etBtnDirection = HAL_KEYPAD_getPressedKey();
			}
		}
	}
}

/**
 * \brief   This function is used to draw or remove rectangle on current screen area based color of line
 *
 *\param	etBtnDirection		  to store the direction of pressed button
 *\return  void
 **/
void APP_MENU_RightLeftButton_ChangeDirection(KEYPAD_BUTTON_DIRECTION_et etBtnDirection)
{
	if (etBtnDirection == KEYPAD_BUTTON_RIGHT)
	{
		while (etBtnDirection == KEYPAD_BUTTON_RIGHT)
		{
			etBtnDirection=HAL_KEYPAD_getPressedKey();
		}
	}
	else if (etBtnDirection == KEYPAD_BUTTON_LEFT)
	{
		while (etBtnDirection == KEYPAD_BUTTON_LEFT)
		{
			etBtnDirection=HAL_KEYPAD_getPressedKey();
		}
	}
}

/**
 * \brief   This function is used to draw or remove rectangle on current screen area based color of line
 *
 *\param	ui8BtnDirection		  to store the direction of pressed button
 *\return	void
 **/
void APP_MENU_UpDownOkButton_ChangeDirection(KEYPAD_BUTTON_DIRECTION_et ui8BtnDirection)
{
	if (ui8BtnDirection == KEYPAD_BUTTON_DOWN)
	{
		while (ui8BtnDirection == KEYPAD_BUTTON_DOWN)
		{
			ui8BtnDirection=HAL_KEYPAD_getPressedKey();
		}
	}
	else if (ui8BtnDirection == KEYPAD_BUTTON_UP)
	{
		while (ui8BtnDirection == KEYPAD_BUTTON_UP)
		{
			ui8BtnDirection=HAL_KEYPAD_getPressedKey();
		}
	}
	else if (ui8BtnDirection == KEYPAD_BUTTON_OK)
	{
		while (ui8BtnDirection == KEYPAD_BUTTON_OK)
		{
			ui8BtnDirection=HAL_KEYPAD_getPressedKey();
		}
	}
}

/**
 * \brief   This function is used to Display Main Screen
 *
 *\param	void
 *\return	void
 **/
void APP_MENU_MainScreen_Display(void)
{

	APP_GLCDHelper_Display(TITLE, GLCD_TITLE_X , GLCD_TITLE_Y, g_aData[0], 0 );
	APP_GLCDHelper_Display(GPS , GLCD_GPS_X , GLCD_GPS_Y ,g_aData[1] , 0);
	APP_GLCDHelper_Display(BATTERY_PERCENTAGE, GLCD_BAT_PERC_X, GLCD_BAT_PERC_Y ,  g_aData[2], 0 );
	APP_GLCDHelper_Display(KEY_INDEX , GLCD_KEY_INDEX_X , GLCD_KEY_INDEX_Y ,g_aData[3], 0 );
	APP_GLCDHelper_Display(DATA_SRC , GLCD_DATA_SRC_X , GLCD_DATA_SRC_Y , g_aData[4], 0 );
	APP_GLCDHelper_Display(OPERATION_MODE , GLCD_OP_MODE_X , GLCD_OP_MODE_Y ,g_aData[5], 0 );
	APP_GLCDHelper_Display(STATE , GLCD_STATE_X , GLCD_STATE_Y , g_aData[6], 0);
}

/**
 * \brief   This function is used to get the screen name based on the right or left click
 *
 *\param	etBtnDirection	 	  to store the direction of pressed button based on it decide which screen to display
 *\return	SCREEN_NAME_et        the screen name
 **/
SCREEN_NAME_et APP_MENU_GetScreenName(KEYPAD_BUTTON_DIRECTION_et etBtnDirection)
{
	//	static uint8_t g_ui8CountScrName =1;

	etBtnDirection = HAL_KEYPAD_getPressedKey();

	if (etBtnDirection == KEYPAD_BUTTON_RIGHT )
	{
		uwTick = 0; //start timer from 0 every right or left click
		g_ui8CountScrName++;
		if( g_ui8CountScrName > 4)
		{
			g_ui8CountScrName = 1;
		}
	}
	else if (etBtnDirection == KEYPAD_BUTTON_LEFT )
	{
		uwTick = 0;
		g_ui8CountScrName--;
		if (g_ui8CountScrName < 1)
		{
			g_ui8CountScrName = 4;
		}
	}

	APP_MENU_Screen_TimeOut(etBtnDirection,(uint32_t*) &uwTick);

	switch (g_ui8CountScrName)
	{
	// Display screen 1
	case MAIN_SCREEN:

		etScreenName=MAIN_SCREEN;
		break;
		// Display screen 2
	case SET_KEY_SCREEN:
		etScreenName=SET_KEY_SCREEN;
		break;

		// Display screen 3
	case SET_MODE_SCREEN:
		etScreenName=SET_MODE_SCREEN;
		break;
		// Display screen 4
	case SET_SOURCE_SCREEN:
		etScreenName = SET_SOURCE_SCREEN;
		break;
	default:

		break;
	}
	APP_MENU_RightLeftButton_ChangeDirection(etBtnDirection);
	return etScreenName;

}

/**
 * \brief   This function is used to take an action based on screen name and direction of pressed button
 *
 *\param	void
 *\return	void
 **/
void APP_MENU_Action(void)
{

	static uint8_t ui8KeyIndex =0;
	static uint8_t ui8CountHelperMode =1;
	static uint8_t ui8CountHelperSrc =1;
	static uint8_t ui8CountHelperKeyvalue =0;
	static uint8_t  bool = FALSE;

	etScrNameHelper = APP_MENU_GetScreenName(g_etBtnDirection);

	switch (etScrNameHelper)
	{
	case MAIN_SCREEN:
		//display content of main screen 1
		if (bool == TRUE)
		{
			HAL_GLCD_DrawLine(GLCD_KEY_VALUE_X1, GLCD_KEY_VALUE_Y_LINE, GLCD_KEY_VALUE_X1+20, GLCD_KEY_VALUE_Y_LINE, GLCD_COLOR_BLACK);
			HAL_GLCD_UpdateScreen(GLCD_KEY_VALUE_X1, GLCD_KEY_VALUE_Y_LINE, GLCD_KEY_VALUE_X1+20, GLCD_KEY_VALUE_Y_LINE);
			ui8CountHelperKeyvalue=0;
			ui8KeyIndex=0;
			HAL_GLCD_ClearScreen();
			bool= FALSE;
		}
		if (bool == FALSE)
		{
			APP_MENU_MainScreen_Display();
		}

		break;

	case SET_KEY_SCREEN:
		if (bool == FALSE)
		{
			HAL_GLCD_ClearScreen();
			APP_GLCDHelper_Display( SET_KEY, GLCD_SET_KEY_X , GLCD_SET_KEY_Y , g_aData[7], 0 );
			APP_GLCDHelper_Display( KEY_VALUE, GLCD_KEY_VALUE_X1 , GLCD_KEY_VALUE_Y , g_aData[3], g_aData[3][0] );
			APP_GLCDHelper_Display( KEY_VALUE, GLCD_KEY_VALUE_X2 , GLCD_KEY_VALUE_Y ,g_aData[3],  g_aData[3][1] );
			APP_GLCDHelper_Display( KEY_VALUE, GLCD_KEY_VALUE_X3 , GLCD_KEY_VALUE_Y , g_aData[3],g_aData[3][2] );

			HAL_GLCD_DrawLine(GLCD_KEY_VALUE_X1+ui8KeyIndex, GLCD_KEY_VALUE_Y_LINE, GLCD_KEY_VALUE_X1+ui8KeyIndex+5, GLCD_KEY_VALUE_Y_LINE, GLCD_COLOR_WHITE);
			HAL_GLCD_UpdateScreen(GLCD_KEY_VALUE_X1+ui8KeyIndex, GLCD_KEY_VALUE_Y_LINE, GLCD_KEY_VALUE_X1+ui8KeyIndex+5, GLCD_KEY_VALUE_Y_LINE);
			HAL_GLCD_DrawLine(GLCD_KEY_VALUE_X2+ui8KeyIndex, GLCD_KEY_VALUE_Y_LINE, GLCD_KEY_VALUE_X2+ui8KeyIndex+5, GLCD_KEY_VALUE_Y_LINE, GLCD_COLOR_WHITE);
			HAL_GLCD_UpdateScreen(GLCD_KEY_VALUE_X2+ui8KeyIndex,GLCD_KEY_VALUE_Y_LINE,GLCD_KEY_VALUE_X2+ui8KeyIndex+5,GLCD_KEY_VALUE_Y_LINE);
			HAL_GLCD_DrawLine(GLCD_KEY_VALUE_X3+ui8KeyIndex, GLCD_KEY_VALUE_Y_LINE, GLCD_KEY_VALUE_X3+ui8KeyIndex+5, GLCD_KEY_VALUE_Y_LINE, GLCD_COLOR_WHITE);
			HAL_GLCD_UpdateScreen(GLCD_KEY_VALUE_X3+ui8KeyIndex,GLCD_KEY_VALUE_Y_LINE,GLCD_KEY_VALUE_X3+ui8KeyIndex+5,GLCD_KEY_VALUE_Y_LINE);
			g_ui8KeyValue=g_aKeyValue[ui8CountHelperKeyvalue];
			bool= TRUE;
		}
		if (bool == TRUE)
		{
			g_etBtnDirHelper=HAL_KEYPAD_getPressedKey();
			if (g_etBtnDirHelper == KEYPAD_BUTTON_UP)
			{
				g_ui8KeyValue++;
				if( g_ui8KeyValue > '9')// Wrap around if the number exceeds 9
				{
					g_ui8KeyValue = '0';
				}
				APP_GLCDHelper_Display( KEY_VALUE, GLCD_KEY_VALUE_X1+ui8KeyIndex,GLCD_KEY_VALUE_Y,g_aData[3],g_ui8KeyValue);
			}
			else if (g_etBtnDirHelper == KEYPAD_BUTTON_DOWN)
			{
				g_ui8KeyValue--;
				if (g_ui8KeyValue < '0') // Wrap around if the number exceeds 0
				{
					g_ui8KeyValue = '9';
				}
				APP_GLCDHelper_Display( KEY_VALUE, GLCD_KEY_VALUE_X1+ui8KeyIndex,GLCD_KEY_VALUE_Y,g_aData[3],g_ui8KeyValue);
			}
			else if (g_etBtnDirHelper == KEYPAD_BUTTON_OK)
			{
				g_aKeyValue[ui8CountHelperKeyvalue] = g_ui8KeyValue;
				HAL_GLCD_DrawLine(GLCD_KEY_VALUE_X1+ui8KeyIndex, GLCD_KEY_VALUE_Y_LINE, GLCD_KEY_VALUE_X1+ui8KeyIndex+5, GLCD_KEY_VALUE_Y_LINE, GLCD_COLOR_BLACK);
				HAL_GLCD_UpdateScreen(GLCD_KEY_VALUE_X1+ui8KeyIndex, GLCD_KEY_VALUE_Y_LINE, GLCD_KEY_VALUE_X1+ui8KeyIndex+5, GLCD_KEY_VALUE_Y_LINE);
				ui8KeyIndex+=7;
				if(ui8KeyIndex > 14)
				{
					ui8KeyIndex = 0 ;
				}
				//
				memcpy(g_aData[3],g_aKeyValue,3);

				//write done
				APP_GLCD_DisplayStringOnScreen(54, 3, g_aData[15]);
				HAL_Delay(300);
				//write space fadya
				APP_GLCD_DisplayStringOnScreen(54, 3, g_aData[16]);
				HAL_GLCD_DrawLine(GLCD_KEY_VALUE_X1+ui8KeyIndex, GLCD_KEY_VALUE_Y_LINE, GLCD_KEY_VALUE_X1+ui8KeyIndex+5, GLCD_KEY_VALUE_Y_LINE, GLCD_COLOR_WHITE);
				HAL_GLCD_UpdateScreen(GLCD_KEY_VALUE_X1+ui8KeyIndex, GLCD_KEY_VALUE_Y_LINE, GLCD_KEY_VALUE_X1+ui8KeyIndex+5, GLCD_KEY_VALUE_Y_LINE);
				ui8CountHelperKeyvalue++;
				g_ui8KeyValue=g_aKeyValue[ui8CountHelperKeyvalue];

				if (ui8CountHelperKeyvalue>2)
				{
					ui8CountHelperKeyvalue=0;
					//ui8KeyIndex=0;
				}
			}
			APP_MENU_UpDownOkButton_ChangeDirection(g_etBtnDirHelper);
		}
		break;

	case SET_MODE_SCREEN:
		if (bool == TRUE)
		{
			HAL_GLCD_DrawLine(GLCD_KEY_VALUE_X1, GLCD_KEY_VALUE_Y_LINE, GLCD_KEY_VALUE_X1+20, GLCD_KEY_VALUE_Y_LINE, GLCD_COLOR_BLACK);
			HAL_GLCD_UpdateScreen(GLCD_KEY_VALUE_X1, GLCD_KEY_VALUE_Y_LINE, GLCD_KEY_VALUE_X1+20, GLCD_KEY_VALUE_Y_LINE);
			HAL_GLCD_ClearScreen();
			ui8KeyIndex=0;  //3chan under line yfdl ybtdi mn el awl lw ruht right aw left abl m yzhr done
			ui8CountHelperKeyvalue=0; // 3chan myzhrsh el done ghir lma el tlata yt3mlhum set
			APP_GLCDHelper_Display(SET_MODE,GLCD_SET_MODE_X,GLCD_SET_MODE_Y,g_aData[8],0);
			APP_GLCDHelper_Display(PLAIN,GLCD_PLAIN_MODE_X,GLCD_PLAIN_MODE_Y,g_aData[9] ,0);
			APP_GLCDHelper_Display(CIPHER,GLCD_CIPHER_MODE_X, GLCD_CIPHER_MODE_Y,g_aData[10], 0);
			bool = FALSE ;
		}
		if (bool == FALSE)
		{
			g_etBtnDirHelper=HAL_KEYPAD_getPressedKey();
			if (g_etBtnDirHelper == KEYPAD_BUTTON_DOWN)
			{
				ui8CountHelperMode++;
				if( ui8CountHelperMode > 3)
				{
					ui8CountHelperMode = 1;
				}
			}
			else if (g_etBtnDirHelper == KEYPAD_BUTTON_UP)
			{
				ui8CountHelperMode--;
				if (ui8CountHelperMode < 1)
				{
					ui8CountHelperMode = 3;
				}
			}

			switch (ui8CountHelperMode )
			{
			case 1:
				HAL_Delay(10);
				APP_GLCD_DisplayStringOnScreen(GLCD_STAR_X, GLCD_SET_MODE_Y, g_aData[19]);
				APP_GLCD_DisplayStringOnScreen(GLCD_STAR_X, GLCD_PLAIN_MODE_Y, g_aData[16]);
				APP_GLCD_DisplayStringOnScreen(GLCD_STAR_X, GLCD_CIPHER_MODE_Y, g_aData[16]);
				break;
			case 2:
				HAL_Delay(10);
				APP_GLCD_DisplayStringOnScreen(GLCD_STAR_X,GLCD_PLAIN_MODE_Y , g_aData[19]);
				APP_GLCD_DisplayStringOnScreen(GLCD_STAR_X, GLCD_SET_MODE_Y, g_aData[16]);
				APP_GLCD_DisplayStringOnScreen(GLCD_STAR_X, GLCD_CIPHER_MODE_Y, g_aData[16]);
				if (g_etBtnDirHelper==KEYPAD_BUTTON_OK)
				{
					//APPLIED
					APP_GLCD_DisplayStringOnScreen(GLCD_APPLIED_MODE_X, GLCD_APPLIED_MODE_Y, g_aData[14]);
					HAL_Delay(300);
					memcpy(g_aData[5],g_aData[9],6);
					//SPACE FADYA
					APP_GLCD_DisplayStringOnScreen(GLCD_APPLIED_MODE_X, GLCD_APPLIED_MODE_Y, g_aData[16]);
				}
				break;
			case 3:
				HAL_Delay(10);
				APP_GLCD_DisplayStringOnScreen(GLCD_STAR_X,  GLCD_CIPHER_MODE_Y , g_aData[19]);
				APP_GLCD_DisplayStringOnScreen(GLCD_STAR_X, GLCD_PLAIN_MODE_Y, g_aData[16]);
				APP_GLCD_DisplayStringOnScreen(GLCD_STAR_X, GLCD_SET_MODE_Y, g_aData[16]);
				if (g_etBtnDirHelper==KEYPAD_BUTTON_OK)
				{
					APP_GLCD_DisplayStringOnScreen(GLCD_APPLIED_MODE_X, GLCD_APPLIED_MODE_Y, g_aData[14]);
					HAL_Delay(300);
					memcpy(g_aData[5],g_aData[10],6);
					APP_GLCD_DisplayStringOnScreen(GLCD_APPLIED_MODE_X, GLCD_APPLIED_MODE_Y, g_aData[16]);
				}
				APP_MENU_UpDownOkButton_ChangeDirection(g_etBtnDirHelper);
				break;
			}
		}
		break;

	case SET_SOURCE_SCREEN:

		if (bool == FALSE)
		{
			HAL_GLCD_ClearScreen();

			APP_GLCDHelper_Display(SET_DATA_SRC, GLCD_SET_DATA_SRC_X , GLCD_SET_DATA_SRC_Y ,g_aData[11], 0 );
			APP_GLCDHelper_Display(AUDIO , GLCD_AUDIO_X , GLCD_AUDIO_Y ,g_aData[12], 0 );
			APP_GLCDHelper_Display(ETHERNET , GLCD_ETHERNET_X , GLCD_ETHERNET_Y , g_aData[13] , 0 );
			bool =TRUE;
		}
		if (bool == TRUE)
		{
			g_etBtnDirHelper=HAL_KEYPAD_getPressedKey();
			if (g_etBtnDirHelper == KEYPAD_BUTTON_DOWN)
			{
				ui8CountHelperSrc++;
				if( ui8CountHelperSrc > 3)
				{
					ui8CountHelperSrc = 1;
				}
			}
			else if (g_etBtnDirHelper == KEYPAD_BUTTON_UP)
			{
				ui8CountHelperSrc--;
				if (ui8CountHelperSrc < 1)
				{
					ui8CountHelperSrc = 3;
				}
			}

			switch (ui8CountHelperSrc )
			{
			//display set data source line
			case 1:
				//			default:
				HAL_Delay(10);
				APP_GLCD_DisplayStringOnScreen(GLCD_STAR_X, GLCD_SET_DATA_SRC_Y, g_aData[19]);
				APP_GLCD_DisplayStringOnScreen(GLCD_STAR_X, GLCD_AUDIO_Y, g_aData[16]);
				APP_GLCD_DisplayStringOnScreen(GLCD_STAR_X, GLCD_ETHERNET_Y, g_aData[16]);
				break;
				//display audio line
			case 2:
				HAL_Delay(10);
				APP_GLCD_DisplayStringOnScreen(GLCD_STAR_X,GLCD_AUDIO_Y , g_aData[19]);
				APP_GLCD_DisplayStringOnScreen(GLCD_STAR_X, GLCD_SET_DATA_SRC_Y, g_aData[16]);
				APP_GLCD_DisplayStringOnScreen(GLCD_STAR_X, GLCD_ETHERNET_Y, g_aData[16]);
				if (g_etBtnDirHelper==KEYPAD_BUTTON_OK)
				{
					APP_GLCD_DisplayStringOnScreen(GLCD_APPLIED_MODE_X, GLCD_APPLIED_MODE_Y, g_aData[14]);
					HAL_Delay(300);
					memcpy(g_aData[4],g_aData[17],3);
					APP_GLCD_DisplayStringOnScreen(GLCD_APPLIED_MODE_X, GLCD_APPLIED_MODE_Y, g_aData[16]);
				}
				break;
				//display Ethernet line
			case 3:
				HAL_Delay(10);
				APP_GLCD_DisplayStringOnScreen(GLCD_STAR_X, GLCD_ETHERNET_Y , g_aData[19]);
				APP_GLCD_DisplayStringOnScreen(GLCD_STAR_X, GLCD_AUDIO_Y, g_aData[16]);
				APP_GLCD_DisplayStringOnScreen(GLCD_STAR_X, GLCD_SET_DATA_SRC_Y, g_aData[16]);				if (g_etBtnDirHelper==KEYPAD_BUTTON_OK)
				{
					APP_GLCD_DisplayStringOnScreen(GLCD_APPLIED_MODE_X, GLCD_APPLIED_MODE_Y, g_aData[14]);
					HAL_Delay(300);
					memcpy(g_aData[4],g_aData[18],3);
					APP_GLCD_DisplayStringOnScreen(GLCD_APPLIED_MODE_X, GLCD_APPLIED_MODE_Y, g_aData[16]);
				}
				APP_MENU_UpDownOkButton_ChangeDirection(g_etBtnDirHelper);

				break;
			}
		}
		break;
	default:
		APP_MENU_MainScreen_Display();
		break;
	}
}
