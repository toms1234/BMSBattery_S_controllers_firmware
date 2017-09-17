/*
 * EGG OpenSource EBike firmware
 *
 * Copyright (C) Casainho, 2015, 2106, 2017.
 *
 * Released under the GPL License, Version 3
 */

#include <stdint.h>
#include "stm8s.h"
#include "gpio.h"
#include "stm8s_adc1.h"

uint8_t adc_throttle_busy_flag = 0;
uint8_t ui8_BatteryVoltage = 0;
uint8_t ui8_BatteryCurrent = 0;

void adc_init (void)
{
  //init GPIO for the used ADC pins
  GPIO_Init(GPIOB,
	    (THROTTLE__PIN || CURRENT_PHASE_B__PIN || CURRENT_TOTAL__PIN),
	    GPIO_MODE_IN_FL_NO_IT);
  GPIO_Init(GPIOE,
	    (BATTERY_VOLTAGE__PIN),
	    GPIO_MODE_IN_FL_NO_IT);

  //de-Init ADC peripheral
  ADC1_DeInit();

  //init ADC1 peripheral
  ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS,
	    ADC1_CHANNEL_5,
	    ADC1_PRESSEL_FCPU_D2,
            ADC1_EXTTRIG_TIM,
	    DISABLE,
	    ADC1_ALIGN_LEFT,
	    (ADC1_SCHMITTTRIG_CHANNEL4 || ADC1_SCHMITTTRIG_CHANNEL5 || ADC1_SCHMITTTRIG_CHANNEL6 || ADC1_SCHMITTTRIG_CHANNEL9),
            DISABLE);
}

uint8_t adc_read_throttle (void)
{
  uint8_t ui8_temp;

  adc_throttle_busy_flag = 1;
//Read in throttle value (just upper 8bits for performance issues)
  ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,
	    ADC1_CHANNEL_4,
	    ADC1_PRESSEL_FCPU_D2,
            ADC1_EXTTRIG_TIM,
	    DISABLE,
	    ADC1_ALIGN_LEFT,
	    (ADC1_SCHMITTTRIG_CHANNEL4 || ADC1_SCHMITTTRIG_CHANNEL5 || ADC1_SCHMITTTRIG_CHANNEL6 || ADC1_SCHMITTTRIG_CHANNEL9),
            DISABLE);

  ADC1->CR1 |= ADC1_CR1_ADON;
  while (!(ADC1->CSR & ADC1_FLAG_EOC)) ;
  ui8_temp = ADC1->DRH;

//Read in battery current value (just upper 8bits for performance issues)
  ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,
	    ADC1_CHANNEL_6,
	    ADC1_PRESSEL_FCPU_D2,
            ADC1_EXTTRIG_TIM,
	    DISABLE,
	    ADC1_ALIGN_LEFT,
	    (ADC1_SCHMITTTRIG_CHANNEL4 || ADC1_SCHMITTTRIG_CHANNEL5 || ADC1_SCHMITTTRIG_CHANNEL6 || ADC1_SCHMITTTRIG_CHANNEL9),
            DISABLE);

  ADC1->CR1 |= ADC1_CR1_ADON;
  while (!(ADC1->CSR & ADC1_FLAG_EOC)) ;
  ui8_BatteryCurrent = ADC1->DRH;

 //Read in battery voltage value (just upper 8bits for performance issues)
    ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,
  	    ADC1_CHANNEL_9,
  	    ADC1_PRESSEL_FCPU_D2,
              ADC1_EXTTRIG_TIM,
  	    DISABLE,
  	    ADC1_ALIGN_LEFT,
  	    (ADC1_SCHMITTTRIG_CHANNEL4 || ADC1_SCHMITTTRIG_CHANNEL5 || ADC1_SCHMITTTRIG_CHANNEL6 || ADC1_SCHMITTTRIG_CHANNEL9),
              DISABLE);

    ADC1->CR1 |= ADC1_CR1_ADON;
    while (!(ADC1->CSR & ADC1_FLAG_EOC)) ;
    ui8_BatteryVoltage = ADC1->DRH;

// Restart continous reading of phaseB current
  ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS,
	    ADC1_CHANNEL_5,
	    ADC1_PRESSEL_FCPU_D2,
            ADC1_EXTTRIG_TIM,
	    DISABLE,
	    ADC1_ALIGN_RIGHT,
	    (ADC1_SCHMITTTRIG_CHANNEL4 || ADC1_SCHMITTTRIG_CHANNEL5 || ADC1_SCHMITTTRIG_CHANNEL6 || ADC1_SCHMITTTRIG_CHANNEL9),
            DISABLE);

  ADC1->CR1 |= ADC1_CR1_ADON;

  adc_throttle_busy_flag = 0;

  return ui8_temp;
}