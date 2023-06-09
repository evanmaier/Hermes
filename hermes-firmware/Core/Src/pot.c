#include "pot.h"

uint16_t Poll_ADC(ADC_HandleTypeDef hadc){
	uint16_t ADC_RES = 0;
	// Start ADC Conversion
	HAL_ADC_Start(&hadc);
	// Poll ADC1 Peripheral & TimeOut = 1mSec
	HAL_ADC_PollForConversion(&hadc, 1);
	// Read The ADC Conversion Result
	ADC_RES = HAL_ADC_GetValue(&hadc);
	// Return result
	return ADC_RES;
}
