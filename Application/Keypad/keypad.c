/*
 * keypad.c
 *
 *  Created on: Mar 12, 2024
 *      Author: phamh
 */
#include "keypad.h"

//Keypad code
const uint8_t KEYPAD_CODE[KEYPAD_ROW][KEYPAD_COL] =
{
		{'1', '2', '3', '+'},
		{'4', '5', '6', '-'},
		{'7', '8', '9', '*'},
		{'C', '0', '=', '/'},
};

//Keypad pin & port
static GPIO_TypeDef *keypad_row_gpio_port[KEYPAD_ROW] = {GPIOA,GPIOA,GPIOA,GPIOA};
static uint16_t keypad_row_gpio_pin[KEYPAD_ROW] = {GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_3};
static GPIO_TypeDef *keypad_col_gpio_port[KEYPAD_COL] = {GPIOA,GPIOA,GPIOA,GPIOA};
static uint16_t keypad_col_gpio_pin[KEYPAD_COL] = {GPIO_PIN_4,GPIO_PIN_5,GPIO_PIN_6,GPIO_PIN_7};
static uint8_t key_current;
static uint8_t key_last;

static void keypad_row_select(uint8_t row)
{
	HAL_GPIO_WritePin(keypad_row_gpio_port[row], keypad_row_gpio_pin[row], GPIO_PIN_RESET);
}

static void keypad_row_unselect()
{
	for(uint8_t r=0; r<KEYPAD_ROW; r++)
	{
		HAL_GPIO_WritePin(keypad_row_gpio_port[r], keypad_row_gpio_pin[r], GPIO_PIN_SET);
	}
}

static uint8_t keypad_getkey()
{
	for(uint8_t r=0; r<KEYPAD_ROW; r++)
	{
		keypad_row_unselect();
		keypad_row_select(r);
		for(uint8_t c=0; c<KEYPAD_COL; c++)
		{
			if(HAL_GPIO_ReadPin(keypad_col_gpio_port[c], keypad_col_gpio_pin[c]) == 0)
			{
				return KEYPAD_CODE[r][c];
			}
		}
	}
	return 0;
}


static void keypad_filter()
{
	 static uint8_t key_debounce = 0;
	 static uint8_t is_debouncing = 0;
	 static uint32_t t_debounce = 0;

	uint8_t key = keypad_getkey();

//Trang thai dang nhieu
	if(key != key_debounce)
	{
		key_debounce = key;
		is_debouncing = 1;
		t_debounce = HAL_GetTick();
	}

//Khi da xac lap - het nhieu
	if(is_debouncing && (HAL_GetTick() - t_debounce >= 15))
	{
		is_debouncing = 0;
		key_current = key_debounce;
	}
}

//nhan phim
__weak void keypad_button_press_callback(uint8_t key)
{

}

//nha phim
__weak void keypad_button_release_callback(uint8_t key)
{

}

//nhan giu
__weak void keypad_button_press_timeout_callback(uint8_t key)
{

}

//nhan nha nhanh
__weak void keypad_short_press_callback(uint8_t key)
{

}

void keypad_handle()
{
	static uint8_t is_pressing = 0;
	static uint32_t t_press;
	keypad_filter();
	if(key_current != key_last)
	{
		if(key_current != 0)
		{
			t_press = HAL_GetTick();
			is_pressing = 1;
			keypad_button_press_callback(key_current);

		}
		else
		{
			is_pressing = 0;
			if(HAL_GetTick() - t_press <= 1000)
			{
				keypad_short_press_callback(key_last);
			}
			keypad_button_release_callback(key_last);
		}
		key_last = key_current;

	}
	if(is_pressing && (HAL_GetTick() - t_press >= 2000))
	{
		is_pressing = 0;
		keypad_button_press_timeout_callback(key_current);
	}

}

void keypad_init()
{
	keypad_row_unselect();
}


