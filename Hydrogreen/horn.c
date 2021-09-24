/*
 * horn.c
 *
 *  Created on: May 14, 2021
 *      Author: Alicja Miekina
 */

#include "rs485SW.h"
#include "rs485EF.h"
#include "horn.h"
#include "gpio.h"


void horn_step(void){
	//if(RS485_RX_VERIFIED_DATA_SW.horn == 1){
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9, GPIO_PIN_SET); //zawor
	//}
	//if(RS485_RX_VERIFIED_DATA_SW.horn == 0){
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET); //kierownica
   // }
}

void emergencyButton_step(void){
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == 0)
	{
		RS485_TX_DATA_SW.emergencyButton = 1;
		RS485_TX_DATA_EF.emergencyScenario = 1;
		HAL_GPIO_WritePin(GPIOC, Solenoid_Valve_GPIO_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, Emergency_Relay_GPIO_Pin, GPIO_PIN_RESET);
	}
}
