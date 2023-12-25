/*
 * SN-functions.c
 *
 *  Created on: 12 lis 2023
 *      Author: Szymon
 */
/*---------------<includes>---------------*/
#include "stdio.h"
#include "string.h"
#include <stdarg.h>
#include <stdbool.h>

/*---<MCU>---*/
#define F411RE

#ifdef F411RE
#include "stm32f1xx_hal.h"
#endif
/*------------------<UART>------------------*/
/*----send----*/
/*If you use other type u can use (char*)msg*/
void SN_UART_Send_char(UART_HandleTypeDef *huart, const char*msg, const char*print)
{
	int len= 0;
	int timeout = 100;
	uint8_t Buffer[len + 1];

	len = sprintf((char*)Buffer,print,msg);
	HAL_UART_Transmit(huart, Buffer, len, timeout);
}

/*Example usage of this function looks like that*/
// Uart_send(&huart2, "data:%d %s %d\r\n",cokolwiek, cos, itd);
void SN_UART_Send(UART_HandleTypeDef *huart, const char *print, ...)
{
    int timeout = 100;

    // Determine the length of the formatted string
    va_list args;
    va_start(args, print);
    int len = vsnprintf(NULL, 0, print, args);
    va_end(args);

    // Allocate the buffer with the correct length
    char Buffer[len];

    // Format the string into the buffer
    va_start(args, print);
    vsnprintf(Buffer, len, print, args);
    va_end(args);

    // Transmit the formatted string through UART
    HAL_UART_Transmit(huart, (uint8_t *)Buffer, len, timeout);
}
/*decode received message*/
int SN_Find_first(const char*message, const char*token)
{
	char buff[128];
	int token_len = sprintf(buff,token);
	int msg_size = sprintf(buff,message);
	int token_place;
	int true_tokens = 0;


	for(int i = 0; i <= (msg_size - 1); i++)
	{
		if(message[i] == token[0])
		{
			true_tokens = 1;
			for(int j = 1; j <= (token_len - 1); j++)
			{
				if(message[i + j] == token[j])
				{
					true_tokens++;
				}
			}

			if(true_tokens == token_len)
			{
				token_place = i;
				break;
			}
			else
			{
				true_tokens = 0;
			}
		}
 }
 return token_place;
}
int SN_Find_last(const char*message, const char*token)
{
	char buff[128];
	int token_len = sprintf(buff,token);
	int msg_size = sprintf(buff,message);
	int token_place;
	int true_tokens = 0;


	for(int i = 0; i <= (msg_size - 1); i++)
	{
		if(message[i] == token[0])
		{
			true_tokens = 1;
			for(int j = 1; j <= (token_len - 1); j++)
			{
				if(message[i + j] == token[j])
				{
					true_tokens++;
				}
			}
			if(true_tokens == token_len)
			{
				token_place = i;
			}
			else
			{
				true_tokens = 0;
			}
		}
 }
 return token_place;
}
void SN_Value_In_Message(const char*message, int from, int to, char*Value)
{
	int j = 0;
	for(int i = from; i <= (to - 1); i++)
	{
		Value[j] = message[i];
		j++;
	}
}
/*Tables*/
void SN_Print_Table(UART_HandleTypeDef *huart, int w, int h)
{
	int width = w + 2;
	int height = h + 2;
	char rows[width][height];
	char px_row[width];

	char buffer[width];
	int len;

	/*Paste corners*/
	rows[0][0] = 201;
	rows[width - 1][0] = 187;
	rows[width -1][height -1] = 188;
	rows[0][height -1] = 200;

	/*Fill the frame*/
    for(int i = 1; i <= (width - 2); i++)
	{
		rows[i][0] = 205;
		rows[i][height - 1] = 205;
	}

    for(int i = 1; i <= (height -2); i++)
    {
    	rows[0][i] = 186;
    	rows[width - 1][i] = 186;
    }


    int px = 0;
    for(int i = 0; i <= (width - 1); i++)
    {
    	px_row[px] = rows[i][0];
        px++;
    }

    len = sprintf(buffer,"%s \r\n",px_row);
    HAL_UART_Transmit(huart, (uint8_t*)buffer, len, 100);

    px = 0;
    for(int i = 0; i <= (width - 1); i++)
    {
    	px_row[px] = rows[i][height - 1];
        px++;
    }

    len = sprintf(buffer,"%s \r\n",px_row);
    HAL_UART_Transmit(huart, (uint8_t*)buffer, len, 100);
}
//TODO dokończyc funkcje rysującą ramki nie działa cos w niej trzeba sprawdzic czy wszystko siedzi

void SN_Bubble_Sort(int*array, int size)
{

	int accumulator;

	/*Do one loop for every bubble*/
	for(int i = 1; i <= (size - 1); i++)
	{
		int change = 0;
		/*Test if numbers are rising ,if not change them*/
		for(int j = 1; j <= (size - 1); j++)
		{
			if(array[j - 1] > array[j])
			{
				accumulator = array[j];
				array[j] = array[j - 1];
				array[j - 1] = accumulator;
				change = 1;
			}
		}
		/*If didn't change any number array is sorted*/
		if(change == 0)
		{
			break;
		}
	}
}














