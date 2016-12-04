//================================================================================
//          Tbe      Tgo   Trel      Treh    Tlow  Th0  Tlow    Th1    Ten
// ___               ___           ________        ___        _______        ____
//    \____________ /   \________ /        \_____ /   \_____ /       \_____ /
//================================================================================
#include "dht22.h"
volatile uint64_t sensorRawData;
AosongStatus AosongReadSensor() 
{
	DHT_TIME_CRITICAL_START
	DHT_SET_SDA_PIN_AS_OUTPUT_LOW
	DHT_DELAY_US(Tbe);
	DHT_SET_SDA_PIN_AS_INPUT_PULL_UP
	DHT_DELAY_US(Tgo);
	
	if (DHT_ACTUAL_PIN_VALUE == 1)
	{
		DHT_TIME_CRITICAL_END
		return SensorNoResponse;
	}
	if (WaitForPinState(PinHigh) == AosongPinOK)
	{
		for (uint_fast8_t i = 0; i < 40; i++)
		{
			WaitForPinState(PinLow);
			WaitForPinState(PinHigh);
			DHT_DELAY_US(Th0);
			sensorRawData = sensorRawData << 1;
			if (DHT_ACTUAL_PIN_VALUE == 1)
				sensorRawData++;
		}
	}
	else
	{
		DHT_TIME_CRITICAL_END
		return SensorNoResponse;
	}
	DHT_TIME_CRITICAL_END
	uint8_t* ptr = (uint8_t*)&sensorRawData;
	if (*ptr != (uint8_t)(*(ptr + 1) + *(ptr + 2) + *(ptr + 3) + *(ptr + 4)))
		return SensorInvalidChecksum;
	return SensorOK;
}

PinStateStatus WaitForPinState(RequiredState state)
{
	uint_fast32_t timeoutCounter = 0;
	while (DHT_ACTUAL_PIN_VALUE == state)
	{
		timeoutCounter++;
		if (timeoutCounter > DHT_TIMEOUT)
			return AosongPinTimeout;
	}
	return AosongPinOK;
}

uint16_t AosongGetTemperature(void)
{
	uint8_t* ptr = (uint8_t*)&sensorRawData;
	return (*(ptr + 2) << 8) + *(ptr + 1);
}

uint16_t AosongGetHumidity(void)
{
	uint8_t* ptr = (uint8_t*)&sensorRawData;
	return (*(ptr + 4) << 8) + *(ptr + 3);
}