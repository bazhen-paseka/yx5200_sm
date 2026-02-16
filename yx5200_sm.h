/**
* \version 1.0
* \author Bazhen.Ele
* \date 16-II-2026
*************************************************************************************
* \copyright	Bazhen Levkovets
* \copyright	Brovary Kyiv Ukraine
* \copyright	bazhen.paseka@gmail.com
*************************************************************************************
*/

#ifndef YX5200_SM_H_INCLUDED
#define YX5200_SM_H_INCLUDED

/*
**************************************************************************
*								INCLUDE FILES
**************************************************************************
*/
	#include "main.h"
	#include "local_config.h"
/*
**************************************************************************
*								    DEFINES
**************************************************************************
*/

/*
**************************************************************************
*								   DATA TYPES
**************************************************************************
*/
	typedef struct {
		UART_HandleTypeDef	*uart;
		GPIO_TypeDef 		*busy_port;
		uint16_t 			busy_pin;
	} yx5200_struct;
/*
**************************************************************************
*								GLOBAL VARIABLES
**************************************************************************
*/

/*
**************************************************************************
*									 MACRO'S
**************************************************************************
*/

/*
**************************************************************************
*                              FUNCTION PROTOTYPES
**************************************************************************
*/
	void MP3_YX5200_Init 			(yx5200_struct *yx5200_handler);
	void MP3_YX5200_Play_with_index (yx5200_struct *yx5200_handler, uint16_t song_index_u16);
/*
**************************************************************************
*                              		END
**************************************************************************
*/
#endif // YX5200_SM_H_INCLUDED

//	USART 9600/8-N-1
// SD card: wav file must have format 000x.wav

// Example:
//	yx5200_struct 	h1_yx5200;
//	h1_yx5200.uart		= &MP3_UART;
//	h1_yx5200.busy_pin	= MP3_BUSY_Pin; // PULL_UP
//	h1_yx5200.busy_port	= MP3_BUSY_GPIO_Port;
//
//		MP3_YX5200_Init(&h1_yx5200);
//		MP3_YX5200_Play_with_index(&h1_yx5200, 0001);
//


// 7E FF 06 0F 00 01 01 xx xx EF
// 0	->	7E is start code
// 1	->	FF is version
// 2	->	06 is length
// 3	->	0F is command
// 4	->	00 is no receive
// 5~6	->	01 01 is argument
   // 7~8	->	checksum = 0 - ( FF+06+0F+00+01+01 )
// 9	->	EF is end code

//After power up, you should send the command [Select device] first. Serial MP3 Player
//only supports micro sd card, so you should send 7E FF 06 09 00 00 02 EF

//Then you can send the command [Play with index] to play some song
//7E FF 06 03 00 00 01 EF Play the first song

//	[Next Song] 7E FF 06 01 00 00 00 EF
