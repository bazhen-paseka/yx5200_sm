#include "stm32f1xx_hal.h"
#include "yx5200_sm.h"

#define UART_BUFFER_SIZE 8

uint8_t _yx5200_free (yx5200_struct yx5200_handler);

void yx5200_init(yx5200_struct *yx5200_handler)
{
	if (yx5200_handler == NULL)
	{
		return;
	}

	HAL_GPIO_WritePin(yx5200_handler->busy_port, yx5200_handler->busy_pin, GPIO_PIN_RESET);

	GPIO_InitTypeDef yx5200_gpio = {0};
	yx5200_gpio.Pull = GPIO_PULLUP;
	yx5200_gpio.Mode = GPIO_MODE_INPUT;
	yx5200_gpio.Speed = GPIO_SPEED_FREQ_LOW;

	yx5200_gpio.Pin = yx5200_handler->busy_pin;
	HAL_GPIO_Init(yx5200_handler->busy_port, &yx5200_gpio);

	uint8_t UART_buffer[UART_BUFFER_SIZE] = {0x7E, 0xFF, 0x06, 0x09, 0x00, 0x00, 0x02, 0xEF};
	HAL_UART_Transmit(yx5200_handler->uart, (uint8_t *)UART_buffer, UART_BUFFER_SIZE, 100);
}

void yx5200_play_with_index(yx5200_struct *yx5200_handler, uint16_t song_index_u16)
{
	HAL_Delay(200);
	do
	{
		HAL_Delay(100);
	}
	while (_yx5200_free(*yx5200_handler) == 0);

	uint8_t UART_buffer[UART_BUFFER_SIZE] = {0x7E, 0xFF, 0x06, 0x03, 0x00, 0x00, 0x00, 0xEF};

	UART_buffer[5] = (uint8_t)(song_index_u16>>8);
	UART_buffer[6] = (uint8_t)(song_index_u16 & 0xFF);
	HAL_UART_Transmit(yx5200_handler->uart, (uint8_t *)UART_buffer, UART_BUFFER_SIZE, 100);
}

uint8_t _yx5200_free (yx5200_struct yx5200_handler)
{
	return HAL_GPIO_ReadPin(yx5200_handler.busy_port, yx5200_handler.busy_pin);
}
