/*
 * laptime.c
 *
 *  Created on: May 14, 2021
 *      Author: Alicja Miekina
 */

/* stan przycisku speedReset resetuje czas okrazenia i srednia przedkosc
 * gdy predkosc pojazdu wyniesie wiecej niz 0 oraz zostanie wcisniety
 * przycisk powerSupply zostanie uruchomione zliczanie czasu
 * zmiana stanu na speedReset zatrzymuje czas i resetuje srednia i predkosc
 * czas okrazenia przeliczany jest na minuty, sekundy, milisekundy i wysylany do kierownicy
*/

#include "rs485EF.h"
#include "rs485SW.h"
#include "measurements.h"
#include "hydrogensensor.h"
#include "gpio.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

	// liczenie predkosci chwilowej i sredniej

		if(GPIO_Pin == GPIO_PIN_3){

			speedPulses++;

		}

		// czujnik wodoru pomiar
		if( GPIO_Pin == H2_Digital_Pin ){
			RS485_TX_DATA_SW.h2SensorDigitalPin = 1;
			RS485_TX_DATA_EF.emergencyScenario = 1;
		}
}
