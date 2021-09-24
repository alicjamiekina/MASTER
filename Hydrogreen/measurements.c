/*
 * laptime.c
 *
 *  Created on: May 14, 2021
 *      Author: Alicja Miekina
 *      soft start, pwm
 */

#include "rs485EF.h"
#include "rs485SW.h"
#include "hydrogreen.h"
#include "measurements.h"
#include "timers.h"
#include "tim.h"
#include "adc.h"
#include "interrupt.h"

void measurements_step(void);
void laptime(void);


volatile uint8_t laptime_seconds = 0;
volatile uint16_t laptime_minutes = 0;
volatile uint16_t laptime_miliseconds = 0;
uint8_t speedPulses = 0;

//wywolana w timers_step
void measurements_step(void)
{
	//czas okrazenia i predkosc
	if(speedPulses >= 1 )
	{

		laptime();
		calcSpeed();
	}
}

void laptime(void){

	if(laptime_flag){
	laptime_miliseconds++;

		 //Sekundy
		  if (laptime_miliseconds >= PERIOD_1S)
		 {
			  laptime_miliseconds = 0;
		      laptime_seconds++;
		 }

		//Minuty
		 if (laptime_seconds >= 60)
		 {
			 laptime_seconds = 0;
		     laptime_minutes++;
		 }
		 laptime_flag = 0;
	}
		 if(RS485_RX_VERIFIED_DATA_SW.speedReset == 1)
			  		{

			  			for(uint8_t k = 0; k < 2; k++){
			  			RS485_TX_DATA_SW.laptime_miliseconds.array[k] = laptime_miliseconds;
			  			}
			  			for(uint8_t k = 0; k < 2; k++){

			  			RS485_TX_DATA_SW.laptime_minutes.array[k] = laptime_minutes;
			  			}

			  			RS485_TX_DATA_SW.laptime_seconds = laptime_seconds;

			  			laptime_seconds = 0;
			  			laptime_minutes = 0;
			  			laptime_miliseconds = 0;
			  			}

}
void calcSpeed(void)
{

	//SPEED
	//chwilowa zliczenie impulsow np w ciagu sekundy
    //srednia w trakcie calego przejazdu z tablicy predkosci chwilowych
	//jak liczyc interim speed

    uint8_t calcInterimSpeed = 0, nrOfCalcSpeed = 0;
    uint8_t tableOfInterimSpeed[nrOfCalcSpeed];
    uint8_t SumOfInterimSpeed = 0;

    RS485_TX_DATA_SW.interimSpeed = calcInterimSpeed;

	 if(RS485_RX_VERIFIED_DATA_SW.speedReset == 1)
	  		{
		 	 uint8_t calcAverageSpeed = 0;

		 	 for(uint8_t n = 0;  n < nrOfCalcSpeed; n++){
		 		SumOfInterimSpeed = SumOfInterimSpeed + tableOfInterimSpeed[n];
		 	 }

		 	 calcAverageSpeed = SumOfInterimSpeed/nrOfCalcSpeed;
		      RS485_TX_DATA_SW.averageSpeed = calcAverageSpeed;
		      speedPulses = 0;
	  		}

}
//ten pwm w zależności od halfgas (0-50) i fullgas(0-100) tych przyciskow,
//oraz gdy powersupply jest
//stopniowe zwiekszanie sie
//w jaki czas moze sie rozpedzic do halfgas
//granice tych przedzialow
void pwmMotor(void)
{
	uint8_t pwmMotor = 0;

	if(RS485_RX_VERIFIED_DATA_SW.powerSupply = 1){
		if( RS485_RX_VERIFIED_DATA_SW.halfGas = 1 && RS485_RX_VERIFIED_DATA_SW.fullGas = 0 ){
			for (uint8_t i = 0; i <= 50; i++){ //inne wartosci
				pwmMotor ++;
				RS485_TX_DATA_EF.motorPWM = pwmMotor;
			}
		}else if(RS485_RX_VERIFIED_DATA_SW.fullGas = 1 && RS485_RX_VERIFIED_DATA_SW.halfGas = 0){
			for (uint8_t i = 0; i <= 100 ; i++){
				pwmMotor ++;
				RS485_TX_DATA_EF.motorPWM = pwmMotor;
			}
		}else if(RS485_RX_VERIFIED_DATA_SW.halfGas = 0 && RS485_RX_VERIFIED_DATA_SW.fullGas = 0){
			pwmMotor --;
			RS485_TX_DATA_EF.motorPWM = pwmMotor;
		} else if( RS485_RX_VERIFIED_DATA_SW.halfGas = 1 && pwmMotor > 50){
			RS485_TX_DATA_EF.motorPWM = 50;
		}
	}else{
		pwmMotor = 0;
	}
}
