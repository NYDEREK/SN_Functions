/*
 * SN-functions.h
 *
 *  Created on: 12 lis 2023
 *      Author: Szymon
 */
/*PC localization of files - #include "D:\SN-USER\HAL-SN-Functions\SN-functions.h"*/

#ifndef INC_SN_FUNCTIONS_H_
#define INC_SN_FUNCTIONS_H_
/*---------------<includes>---------------*/

#define F411RE
#ifdef F411RE
#include "stm32f1xx_hal.h"
#endif
/*---------------<UART>---------------*/
void SN_UART_Send_char(UART_HandleTypeDef *huart, const char*msg, const char*print);
void SN_UART_Send(UART_HandleTypeDef *huart, const char *print, ...);
int SN_Find_first(const char*message, const char*token);
int SN_Find_last(const char*message, const char*token);
void SN_Value_In_Message(const char*message, int from, int to,char*Value);
void SN_Print_Table(UART_HandleTypeDef *huart, int w, int h);
/*-----------<Operations>-------------*/
void SN_Bubble_Sort(int*array, int size);


#endif /* INC_SN_FUNCTIONS_H_ */
