#include "b2b.h"
#include <main.h>

float voltage;

struct ProcParamStruct readParameters(uint16_t rawTemp, uint16_t rawCurrent, uint16_t rawVoltage) {
	struct ProcParamStruct procParam;
	procParam.procTemp = readTemperature(rawTemp);
	procParam.procCurrent = readCurrent(rawCurrent);
	procParam.procVoltage = readVoltage(rawVoltage);
}

uint16_t readTemperature(uint16_t rawTemp) {
	uint16_t processedV = 0;
	uint16_t processedT = 0;
	processedV = rawTemp*3300/4096;
	processedT = (processedV - 500)/10;
	return processedT;
}

int16_t readCurrent(uint16_t rawCurrent) {
    uint16_t processedV = 0;
    uint16_t processedC = 0;
    processedV = rawCurrent*3300/4096;
    processedC = (processedV - 1650)*10/33;
    return processedC;
}

uint16_t readVoltage(uint16_t rawVoltage) {
	uint16_t processedV = 0;
	processedV = rawVoltage*4400/4096;
	return processedV;
}

void controlB2B(uint32_t raw, float thresh_low, float thresh_high) {
	float voltage;
	voltage = (raw/4096)*4.4;
	if(voltage > thresh_high+0.1) {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);    //shut off both transistors
	}
	else if(voltage > thresh_high) {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);   //shut off charging transistor
	}
	else if(voltage < thresh_low-0.5) {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);   //shut off both transistors
	}
	else if(voltage < thresh_low) {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);    //shut off discharging transistor
	}
	else {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);     //both transistors on
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
	}

}

void batteryCutoff(uint32_t raw) {

	voltage = ((float)raw/4096.0f)*4.4f;
	if(voltage > MAX_V_CUTOFF + V_THRESH) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
	}
	else if(voltage < MIN_V_CUTOFF - V_THRESH) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
	}
	else if(voltage < MAX_V_CUTOFF && voltage > MIN_V_CUTOFF) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
	}
}
