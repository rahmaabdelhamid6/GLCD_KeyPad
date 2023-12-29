/******************************************************************************
 * Module: GLCD
 *
 * File Name: hal_GLCD.c
 *
 * Description: Source file for the GLCD
 *
 * Author: Rahma Abdelhamid
 *
 * Created on: Nov 20, 2023
 *******************************************************************************/


/*******************************************************************************
 *                               includes                             *
 *******************************************************************************/



#include "stm32l0xx_hal.h"
#include "stdlib.h"
#include "stdint.h"
#include "main.h"
#include "hal_GLCD.h"


/*******************************************************************************
 *                             Global Variable                                 *
 *******************************************************************************/

uint8_t g_aui8TxSpi[4];

//static GLCD_st stGLCD;

//static uint8_t g_aui8GLCD_Buffer[SCREEN_WIDTH * SCREEN_HEIGHT / 8];
uint8_t g_aui8GLCD_Buffer[SCREEN_HEIGHT / 8][SCREEN_WIDTH];

//uint8_t g_aData[19][16]= {"MAIN","GPS","100%",{'5','2','6'} ,"HDS","PLAIN","TX", "SET KEY", "SET MODE", "PLAIN","CIPHER ", "SET SOURCE", "AUDIO" , "ETHERNET" , "APPLIED" , "DONE" , "       ","HDS", "ETH"};
//uint8_t g_aKeyValue [3]={'5','2','6'};

const char font5x8[] = {
		0x00, 0x00, 0x00, 0x00, 0x00,// (spacja)
		0x00, 0x00, 0x5F, 0x00, 0x00,// !
		0x00, 0x07, 0x00, 0x07, 0x00,// "
		0x14, 0x7F, 0x14, 0x7F, 0x14,// #
		0x24, 0x2A, 0x7F, 0x2A, 0x12,// $
		0x23, 0x13, 0x08, 0x64, 0x62,// %
		0x36, 0x49, 0x55, 0x22, 0x50,// &
		0x00, 0x05, 0x03, 0x00, 0x00,// '
		0x00, 0x1C, 0x22, 0x41, 0x00,// (
		0x00, 0x41, 0x22, 0x1C, 0x00,// )
		0x08, 0x2A, 0x1C, 0x2A, 0x08,// *
		0x08, 0x08, 0x3E, 0x08, 0x08,// +
		0x00, 0x50, 0x30, 0x00, 0x00,// ,
		0x08, 0x08, 0x08, 0x08, 0x08,// -
		0x00, 0x30, 0x30, 0x00, 0x00,// .
		0x20, 0x10, 0x08, 0x04, 0x02,// /
		0x3E, 0x51, 0x49, 0x45, 0x3E,// 0
		0x00, 0x42, 0x7F, 0x40, 0x00,// 1
		0x42, 0x61, 0x51, 0x49, 0x46,// 2
		0x21, 0x41, 0x45, 0x4B, 0x31,// 3
		0x18, 0x14, 0x12, 0x7F, 0x10,// 4
		0x27, 0x45, 0x45, 0x45, 0x39,// 5
		0x3C, 0x4A, 0x49, 0x49, 0x30,// 6
		0x01, 0x71, 0x09, 0x05, 0x03,// 7
		0x36, 0x49, 0x49, 0x49, 0x36,// 8
		0x06, 0x49, 0x49, 0x29, 0x1E,// 9
		0x00, 0x36, 0x36, 0x00, 0x00,// :
		0x00, 0x56, 0x36, 0x00, 0x00,// ;
		0x00, 0x08, 0x14, 0x22, 0x41,// <
		0x14, 0x14, 0x14, 0x14, 0x14,// =
		0x41, 0x22, 0x14, 0x08, 0x00,// >
		0x02, 0x01, 0x51, 0x09, 0x06,// ?
		0x32, 0x49, 0x79, 0x41, 0x3E,// @
		0x7E, 0x11, 0x11, 0x11, 0x7E,// A
		0x7F, 0x49, 0x49, 0x49, 0x36,// B
		0x3E, 0x41, 0x41, 0x41, 0x22,// C
		0x7F, 0x41, 0x41, 0x22, 0x1C,// D
		0x7F, 0x49, 0x49, 0x49, 0x41,// E
		0x7F, 0x09, 0x09, 0x01, 0x01,// F
		0x3E, 0x41, 0x41, 0x51, 0x32,// G
		0x7F, 0x08, 0x08, 0x08, 0x7F,// H
		0x00, 0x41, 0x7F, 0x41, 0x00,// I
		0x20, 0x40, 0x41, 0x3F, 0x01,// J
		0x7F, 0x08, 0x14, 0x22, 0x41,// K
		0x7F, 0x40, 0x40, 0x40, 0x40,// L
		0x7F, 0x02, 0x04, 0x02, 0x7F,// M
		0x7F, 0x04, 0x08, 0x10, 0x7F,// N
		0x3E, 0x41, 0x41, 0x41, 0x3E,// O
		0x7F, 0x09, 0x09, 0x09, 0x06,// P
		0x3E, 0x41, 0x51, 0x21, 0x5E,// Q
		0x7F, 0x09, 0x19, 0x29, 0x46,// R
		0x46, 0x49, 0x49, 0x49, 0x31,// S
		0x01, 0x01, 0x7F, 0x01, 0x01,// T
		0x3F, 0x40, 0x40, 0x40, 0x3F,// U
		0x1F, 0x20, 0x40, 0x20, 0x1F,// V
		0x7F, 0x20, 0x18, 0x20, 0x7F,// W
		0x63, 0x14, 0x08, 0x14, 0x63,// X
		0x03, 0x04, 0x78, 0x04, 0x03,// Y
		0x61, 0x51, 0x49, 0x45, 0x43,// Z
		0x00, 0x00, 0x7F, 0x41, 0x41,// [
		0x02, 0x04, 0x08, 0x10, 0x20,// "\"
		0x41, 0x41, 0x7F, 0x00, 0x00,// ]
		0x04, 0x02, 0x01, 0x02, 0x04,// ^
		0x40, 0x40, 0x40, 0x40, 0x40,// _
		0x00, 0x01, 0x02, 0x04, 0x00,// `
		0x20, 0x54, 0x54, 0x54, 0x78,// a
		0x7F, 0x48, 0x44, 0x44, 0x38,// b
		0x38, 0x44, 0x44, 0x44, 0x20,// c
		0x38, 0x44, 0x44, 0x48, 0x7F,// d
		0x38, 0x54, 0x54, 0x54, 0x18,// e
		0x08, 0x7E, 0x09, 0x01, 0x02,// f
		0x08, 0x14, 0x54, 0x54, 0x3C,// g
		0x7F, 0x08, 0x04, 0x04, 0x78,// h
		0x00, 0x44, 0x7D, 0x40, 0x00,// i
		0x20, 0x40, 0x44, 0x3D, 0x00,// j
		0x00, 0x7F, 0x10, 0x28, 0x44,// k
		0x00, 0x41, 0x7F, 0x40, 0x00,// l
		0x7C, 0x04, 0x18, 0x04, 0x78,// m
		0x7C, 0x08, 0x04, 0x04, 0x78,// n
		0x38, 0x44, 0x44, 0x44, 0x38,// o
		0x7C, 0x14, 0x14, 0x14, 0x08,// p
		0x08, 0x14, 0x14, 0x18, 0x7C,// q
		0x7C, 0x08, 0x04, 0x04, 0x08,// r
		0x48, 0x54, 0x54, 0x54, 0x20,// s
		0x04, 0x3F, 0x44, 0x40, 0x20,// t
		0x3C, 0x40, 0x40, 0x20, 0x7C,// u
		0x1C, 0x20, 0x40, 0x20, 0x1C,// v
		0x3C, 0x40, 0x30, 0x40, 0x3C,// w
		0x44, 0x28, 0x10, 0x28, 0x44,// x
		0x0C, 0x50, 0x50, 0x50, 0x3C,// y
		0x44, 0x64, 0x54, 0x4C, 0x44,// z
		0x00, 0x08, 0x36, 0x41, 0x00,// {
		0x00, 0x00, 0x7F, 0x00, 0x00,// |
		0x00, 0x41, 0x36, 0x08, 0x00,// }
		0x08, 0x08, 0x2A, 0x1C, 0x08,// ->
		0x08, 0x1C, 0x2A, 0x08, 0x08 // <-
};

extern SPI_HandleTypeDef hspi1;

/*******************************************************************************
 *                              Function Definition                            *
 *******************************************************************************/

void HAL_GLCD_setDelay(void)
{
	uint8_t ui8count = 0;
	for (ui8count = 0; ui8count < 5; ui8count++)
	{
	}
}

void HAL_GLCD_writeCommand(uint8_t ui8commandToWrite)
{
	g_aui8TxSpi [0]= ui8commandToWrite;
	HAL_GPIO_WritePin(LCD_A0_GPIO_Port, LCD_A0_Pin, GPIO_PIN_RESET);
//	HAL_GLCD_setDelay();
	HAL_GPIO_WritePin(LCD_NCS_GPIO_Port, LCD_NCS_Pin, GPIO_PIN_RESET);
//	HAL_GLCD_setDelay();
	HAL_SPI_Transmit(&hspi1, g_aui8TxSpi, 1, HAL_MAX_DELAY);
//	HAL_GLCD_setDelay();
	HAL_GPIO_WritePin(LCD_NCS_GPIO_Port, LCD_NCS_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
}

void HAL_GLCD_writeData(uint8_t ui8dataToWrite)
{
	g_aui8TxSpi[0] = ui8dataToWrite;
	HAL_GPIO_WritePin(LCD_A0_GPIO_Port, LCD_A0_Pin, GPIO_PIN_SET);
//	HAL_GLCD_setDelay();
	HAL_GPIO_WritePin(LCD_NCS_GPIO_Port, LCD_NCS_Pin, GPIO_PIN_RESET);
//	HAL_GLCD_setDelay();
	HAL_SPI_Transmit(&hspi1, g_aui8TxSpi, 1, HAL_MAX_DELAY);
//	HAL_GLCD_setDelay();
	HAL_GPIO_WritePin(LCD_NCS_GPIO_Port, LCD_NCS_Pin, GPIO_PIN_SET);
//	HAL_Delay(1);
}

void HAL_GLCD_InitalizePorts(void)
{
	/* Set CS to High */
	HAL_GPIO_WritePin(LCD_NCS_GPIO_Port, LCD_NCS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_NRESET_GPIO_Port, LCD_NRESET_Pin, GPIO_PIN_RESET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(LCD_NRESET_GPIO_Port, LCD_NRESET_Pin, GPIO_PIN_SET);
	HAL_Delay(50);

	/* Turn off  */
	g_aui8TxSpi[0] = 0xAE;
	HAL_GLCD_writeCommand(g_aui8TxSpi[0]);

	/* 1/9 bias */
	g_aui8TxSpi[0] = 0xA2;
	HAL_GLCD_writeCommand(g_aui8TxSpi[0]);

	/* ADC Normal  */
	g_aui8TxSpi[0] = 0xA0;
	HAL_GLCD_writeCommand(g_aui8TxSpi[0]);

	/* COM Normal  */
	g_aui8TxSpi[0] = 0xC8;
	HAL_GLCD_writeCommand(g_aui8TxSpi[0]);

	/* Initial display line   */
	g_aui8TxSpi[0] = 0x40;    //Operating Mode
	HAL_GLCD_writeCommand(g_aui8TxSpi[0]);

	/* Power control Set  */
	g_aui8TxSpi[0] = 0x2F;
	HAL_GLCD_writeCommand(g_aui8TxSpi[0]);

	/* resistor ratio */
//	g_aui8TxSpi[0] = 0x25;    //128*64
	g_aui8TxSpi[0] = 0x21;    //128*32
	HAL_GLCD_writeCommand(g_aui8TxSpi[0]);

	/* contrast  */
	g_aui8TxSpi[0] = 0x81;   //electronic volume mode set
	HAL_GLCD_writeCommand(g_aui8TxSpi[0]);

	/* contrast  */
//	g_aui8TxSpi[0] = 0x10;  //electronic volume register set  //128*64
	g_aui8TxSpi[0] = 0x20;   //128*32
	HAL_GLCD_writeCommand(g_aui8TxSpi[0]);

	/* Display on   */
	g_aui8TxSpi[0] = 0xAF;
	HAL_GLCD_writeCommand(g_aui8TxSpi[0]);

	/* Page address B0   */
	g_aui8TxSpi[0] = 0xB0;
	HAL_GLCD_writeCommand(g_aui8TxSpi[0]);
}

void HAL_GLCD_Init(void)
{
	uint8_t ui8count = 0;
	HAL_GLCD_InitalizePorts();
	for (ui8count = 0; ui8count < 3; ui8count++)
	{
		HAL_GLCD_writeCommand((DISPLAY_ON_CMD | ON));
	}
}


void HAL_GLCD_goTo(uint8_t ui8Xaxis, uint8_t ui8Yaxis)
{
	HAL_GLCD_setYaddress(ui8Yaxis);
	HAL_GLCD_setXaddress(ui8Xaxis);
}


void HAL_GLCD_ClearScreen(void)
{
	uint8_t ui8count1 = 0, ui8count2 = 0;
	for (ui8count2 = 0; ui8count2 < ( SCREEN_HEIGHT / 8); ui8count2++)
	{
		HAL_GLCD_goTo(0, ui8count2);
		for (ui8count1 = 0; ui8count1 < SCREEN_WIDTH; ui8count1++)
		{
			HAL_GLCD_writeData(0x00);
		}
	}
}

void HAL_clearLineGLCD(void)
{
	uint8_t ui8count1 = 0;
	for (ui8count1 = 0; ui8count1 < SCREEN_WIDTH; ui8count1++)
	{
		HAL_GLCD_writeData(0x00);
	}
}


void HAL_GLCD_writeChar(int8_t i8charToWrite)
{
	uint8_t ui8count = 0;
	i8charToWrite -= 32;
	for (ui8count = 0; ui8count < 5; ui8count++)
	{
		HAL_GLCD_writeData(
				HAL_GLCD_readByteFromROMMemory(
						(int8_t *) ((int32_t) font5x8 + (5 * i8charToWrite) + ui8count)));
	}

	HAL_GLCD_writeData(0x00);
}


void HAL_GLCD_writeString(uint8_t *pui8stringToWrite)
{
	while (*pui8stringToWrite != '\0')
	{
		HAL_GLCD_writeChar(*pui8stringToWrite);
		pui8stringToWrite++;
	}
}

uint8_t* INT_To_String(uint32_t ui32value)
{
	uint8_t str[6] = {0};
	uint8_t *ptr=&str[5];
	*ptr='\0';
	while (ui32value!='\0')
	{
		ptr--;
		*ptr=(ui32value%10)+48;
		ui32value=ui32value/10;
	}
	return ptr;
}



uint8_t HAL_GLCD_readByteFromROMMemory(int8_t * ptr)
{
	return *ptr;
}

void HAL_GLCD_setYaddress(uint8_t ui8Yaxis)
{
	HAL_GLCD_writeCommand(ST7565R_PAGE_1_ADDRESS_SET | (0b00001111 & ui8Yaxis));
}

void HAL_GLCD_setXaddress(uint8_t ui8Xaxis)
{
	HAL_GLCD_setColumnUpper(ui8Xaxis);
	HAL_GLCD_setColumnLower(ui8Xaxis);
}

void HAL_GLCD_setColumnUpper(uint8_t ui8Addr)
{
	HAL_GLCD_writeCommand(ST7565R_COLUMN_ADDRESS_SET_UPPER | (ui8Addr >> 4));
}

void HAL_GLCD_setColumnLower(uint8_t ui8Addr)
{
	HAL_GLCD_writeCommand(ST7565R_COLUMN_ADDRESS_SET_LOWER | (0x0f & ui8Addr));
}

void HAL_GLCD_setStartLine(uint8_t ui8Addr)
{
	HAL_GLCD_writeCommand( ST7565R_SET_START_LINE | (0b00111111 & ui8Addr));
}


void HAL_GLCD_UpdateScreen(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY) //for the key value
{
	uint8_t startPage = startY / 8;
	uint8_t endPage = endY / 8;
	uint8_t page;
	uint8_t col;

	// Select the LCD by pulling its chip select pin low
	HAL_GPIO_WritePin(LCD_NCS_GPIO_Port, LCD_NCS_Pin, GPIO_PIN_RESET);

	// Iterate through the specified pages
	for (page = startPage; page <= endPage; page++) {
		// Set the page command for the current page
		HAL_GLCD_writeCommand(0xB0 | page);
		// Set the column command to start from the specified start column
		HAL_GLCD_writeCommand(0x10 | (startX >> 4)); // Most significant 4 bits of startX
		HAL_GLCD_writeCommand(startX & 0x0F); // Least significant 4 bits of startX

		// Send the column data for the current page and within the specified X range
		for (col = startX; col <= endX; col++) {
			uint16_t x = col - startX;
			uint16_t y = page * 8;
			uint8_t data = g_aui8GLCD_Buffer[page][col];

			// Calculate the pixel value based on the (x, y) coordinates
			if (x >= startX && x <= endX && y >= startY && y <= endY) {
				// Set the corresponding bit in the data byte
				data |= (1 << (y % 8));
			}

			HAL_GLCD_writeData(data);
		}
	}

	// Deselect the LCD by pulling its chip select pin high
	HAL_GPIO_WritePin(LCD_NCS_GPIO_Port, LCD_NCS_Pin, GPIO_PIN_SET);
}

void HAL_GLCD_DrawPixel(uint16_t ui16X, uint16_t ui16Y, GLCD_COLOR_et etcolor)
{
	uint8_t page = 0;
	uint8_t column = 0 ;

	if (ui16X < SCREEN_WIDTH && ui16Y < SCREEN_HEIGHT)
	{
		// Calculate the page and column for the pixel
		page = ui16Y / 8;
		column = ui16X;

		if (etcolor == GLCD_COLOR_WHITE)
		{
			g_aui8GLCD_Buffer[page][column] |= (1 << (ui16Y % 8));
		} else {
			g_aui8GLCD_Buffer[page][column] &= ~(1 << (ui16Y % 8));
		}
	}
}

void HAL_GLCD_DrawLine(uint16_t ui16X0, uint16_t ui16Y0, uint16_t ui16X1, uint16_t ui16Y1, GLCD_COLOR_et etColor)
{
	int16_t dx = abs(ui16X1 - ui16X0);
	int16_t dy = abs(ui16Y1 - ui16Y0);
	int16_t sx = ui16X0 < ui16X1 ? 1 : -1;
	int16_t sy = ui16Y0 < ui16Y1 ? 1 : -1;
	int16_t err = dx - dy;
//	int16_t e2 = 2 * err;
	int16_t e2 ;
	while (1) {
		HAL_GLCD_DrawPixel(ui16X0, ui16Y0, etColor);

		if (ui16X0 == ui16X1 && ui16Y0 == ui16Y1) {
			break;
		}
		e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			ui16X0 += sx;
		}

		if (e2 < dx) {
			err += dx;
			ui16Y0 += sy;
		}
	}
}







void HAL_GLCD_DrawRectangle(uint16_t ui16X, uint16_t ui16Y, uint16_t ui16W, uint16_t ui16H, GLCD_COLOR_et etColor)
{
	/* Check input parameters */
	if (
			ui16X >= SCREEN_WIDTH ||
			ui16Y >= SCREEN_HEIGHT
	) {
		/* Return error */
		return;
	}

	/* Check width and height */
	if ((ui16X + ui16W) >= SCREEN_WIDTH) {
		ui16W = SCREEN_WIDTH - ui16X;
	}
	if ((ui16Y + ui16H) >= SCREEN_HEIGHT) {
		ui16H = SCREEN_HEIGHT - ui16Y;
	}
	HAL_GLCD_DrawLine(ui16X, ui16Y, ui16X + ui16W - 1, ui16Y, etColor);
	HAL_GLCD_DrawLine(ui16X, ui16Y + ui16H - 1, ui16X + ui16W - 1, ui16Y + ui16H - 1, etColor);
	HAL_GLCD_DrawLine(ui16X, ui16Y, ui16X, ui16Y + ui16H - 1, etColor);
	HAL_GLCD_DrawLine(ui16X + ui16W - 1, ui16Y, ui16X + ui16W - 1, ui16Y + ui16H - 1, etColor);


}
