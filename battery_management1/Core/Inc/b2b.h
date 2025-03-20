#include <stdint.h>

#define MAX_V_CUTOFF 3.5
#define MIN_V_CUTOFF 2.0
#define V_THRESH     0.05

struct RawParamStruct {
	uint16_t rawTemp;
	uint16_t rawCurrent;
	uint16_t rawVoltage;
};

struct ProcParamStruct {
	uint16_t procTemp;
	int16_t procCurrent;
	uint16_t procVoltage;
};

struct ProcParamStruct readParameters(uint16_t rawTemp, uint16_t rawCurrent, uint16_t rawVoltage);
uint16_t readTemperature(uint16_t rawTemp);
int16_t readCurrent(uint16_t rawCurrent);
uint16_t readVoltage(uint16_t rawVoltage);
void controlB2B(uint32_t raw, float thresh_low, float thresh_high);
void batteryCutoff(uint32_t raw);

extern float voltage;
