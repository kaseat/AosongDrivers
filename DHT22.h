#ifndef __DHT22__
#define __DHT22__


#include <stm32f103xb.h>
#include <../CMSIS_RTOS/cmsis_os.h>

typedef enum { SensorOK, SensorNoResponse, SensorInvalidChecksum  } AosongStatus;
typedef enum { AosongPinOK, AosongPinTimeout } PinStateStatus;
typedef enum { PinHigh=0, PinLow=1 } RequiredState;
PinStateStatus WaitForPinState(RequiredState state);
AosongStatus AosongReadSensor(void);
uint16_t AosongGetTemperature(void);
uint16_t AosongGetHumidity(void);

#define F_CPU 72
#define DHT_PORT GPIOA
#define DHT_PIN 11
#define DHT_START_PULSE_MS 2
#define DHT_TIMEOUT 85*F_CPU

#define DHT_TIME_CRITICAL_START vTaskSuspendAll();
#define DHT_TIME_CRITICAL_END xTaskResumeAll();
#define DHT_ACTUAL_PIN_VALUE (DHT_PORT->IDR >> DHT_PIN & 1)

#define Tbe 1000         // ������ ������ ������
#define Tgo 30+10        // ������ ������ �������
#define Trel 80          // ������ ����������� ������
#define Treh 80          // ������ ����������� �������
#define Tlow 50          // ����� �������� ����
#define Th0 26+10        // �������� ���� 0
#define Th1 70           // �������� ���� 1
#define Ten 50           // ������ ��������� ��������
#define DHT_DELAY_US(delay) for (uint32_t i = 0; i < delay*F_CPU; i++) {}


#define CLR_PIN_CFG(PORT, PIN, LH) PORT->CR##LH &= ~(3<<GPIO_CR##LH##_MODE##PIN##_Pos | 3<<GPIO_CR##LH##_CNF##PIN##_Pos);
#define HI_PIN_AS_INPUT_ANALOG(PORT, PIN) CLR_PIN_CFG(PORT, PIN, H) PORT->CRH |= 0 << GPIO_CRH_MODE##PIN##_Pos | 0<<GPIO_CRH_CNF##PIN##_Pos
#define HI_PIN_AS_INPUT_FLOATING(PORT, PIN) CLR_PIN_CFG(PORT, PIN, H) PORT->CRH |= 0 << GPIO_CRH_MODE##PIN##_Pos | 1<<GPIO_CRH_CNF##PIN##_Pos
#define HI_PIN_AS_INPUT_PULL_DOWN(PORT, PIN) CLR_PIN_CFG(PORT, PIN, H) PORT->CRH |= 0 << GPIO_CRH_MODE##PIN##_Pos | 2<<GPIO_CRH_CNF##PIN##_Pos; GPIO_SET_PIN_LO(PORT, PIN)
#define HI_PIN_AS_INPUT_PULL_UP(PORT, PIN) CLR_PIN_CFG(PORT, PIN, H) PORT->CRH |= 0 << GPIO_CRH_MODE##PIN##_Pos | 2<<GPIO_CRH_CNF##PIN##_Pos; GPIO_SET_PIN_HI(PORT, PIN)
#define HI_PIN_AS_GPIO_OUT_PP_LOW_SPEED(PORT, PIN) CLR_PIN_CFG(PORT, PIN, H) PORT->CRH |= 2 << GPIO_CRH_MODE##PIN##_Pos | 0<<GPIO_CRH_CNF##PIN##_Pos
#define LO_PIN_AS_INPUT_ANALOG(PORT, PIN) CLR_PIN_CFG(PORT, PIN, L) PORT->CRL |= 0 << GPIO_CRL_MODE##PIN##_Pos | 0<<GPIO_CRL_CNF##PIN##_Pos
#define LO_PIN_AS_INPUT_FLOATING(PORT, PIN) CLR_PIN_CFG(PORT, PIN, L) PORT->CRL |= 0 << GPIO_CRL_MODE##PIN##_Pos | 1<<GPIO_CRL_CNF##PIN##_Pos
#define LO_PIN_AS_INPUT_PULL_DOWN(PORT, PIN) CLR_PIN_CFG(PORT, PIN, L) PORT->CRL |= 0 << GPIO_CRL_MODE##PIN##_Pos | 2<<GPIO_CRL_CNF##PIN##_Pos; GPIO_SET_PIN_LO(PORT, PIN)
#define LO_PIN_AS_INPUT_PULL_UP(PORT, PIN) CLR_PIN_CFG(PORT, PIN, L) PORT->CRL |= 0 << GPIO_CRL_MODE##PIN##_Pos | 2<<GPIO_CRL_CNF##PIN##_Pos; GPIO_SET_PIN_HI(PORT, PIN)
#define LO_PIN_AS_GPIO_OUT_PP_LOW_SPEED(PORT, PIN) CLR_PIN_CFG(PORT, PIN, L) PORT->CRL |= 2 << GPIO_CRL_MODE##PIN##_Pos | 0<<GPIO_CRL_CNF##PIN##_Pos
#define GPIO_SET_PIN_HI(PORT, PIN) PORT->ODR |= 1 << GPIO_ODR_ODR##PIN##_Pos
#define GPIO_SET_PIN_LO(PORT, PIN) PORT->ODR &= ~(1 << GPIO_ODR_ODR##PIN##_Pos)

#if DHT_PIN == 0
#define DHT_SET_SDA_PIN_AS_OUTPUT_HIGH LO_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 0); GPIO_SET_PIN_HI(DHT_PORT, 0);
#define DHT_SET_SDA_PIN_AS_OUTPUT_LOW LO_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 0); GPIO_SET_PIN_LO(DHT_PORT, 0);
#define DHT_SET_SDA_PIN_AS_INPUT_FLOATING  LO_PIN_AS_INPUT_FLOATING(DHT_PORT, 0);
#define DHT_SET_SDA_PIN_AS_INPUT_PULL_UP  LO_PIN_AS_INPUT_PULL_UP(DHT_PORT, 0);
#elif DHT_PIN == 1
#define DHT_SET_SDA_PIN_AS_OUTPUT_HIGH LO_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 1); GPIO_SET_PIN_HI(DHT_PORT, 1);
#define DHT_SET_SDA_PIN_AS_OUTPUT_LOW LO_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 1); GPIO_SET_PIN_LO(DHT_PORT, 1);
#define DHT_SET_SDA_PIN_AS_INPUT_FLOATING  LO_PIN_AS_INPUT_FLOATING(DHT_PORT, 1);
#define DHT_SET_SDA_PIN_AS_INPUT_PULL_UP  LO_PIN_AS_INPUT_PULL_UP(DHT_PORT, 1);
#elif DHT_PIN == 2
#define DHT_SET_SDA_PIN_AS_OUTPUT_HIGH LO_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 2); GPIO_SET_PIN_HI(DHT_PORT, 2);
#define DHT_SET_SDA_PIN_AS_OUTPUT_LOW LO_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 2); GPIO_SET_PIN_LO(DHT_PORT, 2);
#define DHT_SET_SDA_PIN_AS_INPUT_FLOATING  LO_PIN_AS_INPUT_FLOATING(DHT_PORT, 2);
#define DHT_SET_SDA_PIN_AS_INPUT_PULL_UP  LO_PIN_AS_INPUT_PULL_UP(DHT_PORT, 2);
#elif DHT_PIN == 3
#define DHT_SET_SDA_PIN_AS_OUTPUT_HIGH LO_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 3); GPIO_SET_PIN_HI(DHT_PORT, 3);
#define DHT_SET_SDA_PIN_AS_OUTPUT_LOW LO_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 3); GPIO_SET_PIN_LO(DHT_PORT, 3);
#define DHT_SET_SDA_PIN_AS_INPUT_FLOATING  LO_PIN_AS_INPUT_FLOATING(DHT_PORT, 3);
#define DHT_SET_SDA_PIN_AS_INPUT_PULL_UP  LO_PIN_AS_INPUT_PULL_UP(DHT_PORT, 3);
#elif DHT_PIN == 4
#define DHT_SET_SDA_PIN_AS_OUTPUT_HIGH LO_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 4); GPIO_SET_PIN_HI(DHT_PORT, 4);
#define DHT_SET_SDA_PIN_AS_OUTPUT_LOW LO_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 4); GPIO_SET_PIN_LO(DHT_PORT, 4);
#define DHT_SET_SDA_PIN_AS_INPUT_FLOATING  LO_PIN_AS_INPUT_FLOATING(DHT_PORT, 4);
#define DHT_SET_SDA_PIN_AS_INPUT_PULL_UP  LO_PIN_AS_INPUT_PULL_UP(DHT_PORT, 4);
#elif DHT_PIN == 5
#define DHT_SET_SDA_PIN_AS_OUTPUT_HIGH LO_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 5); GPIO_SET_PIN_HI(DHT_PORT, 5);
#define DHT_SET_SDA_PIN_AS_OUTPUT_LOW LO_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 5); GPIO_SET_PIN_LO(DHT_PORT, 5);
#define DHT_SET_SDA_PIN_AS_INPUT_FLOATING  LO_PIN_AS_INPUT_FLOATING(DHT_PORT, 5);
#define DHT_SET_SDA_PIN_AS_INPUT_PULL_UP  LO_PIN_AS_INPUT_PULL_UP(DHT_PORT, 5);
#elif DHT_PIN == 6
#define DHT_SET_SDA_PIN_AS_OUTPUT_HIGH LO_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 6); GPIO_SET_PIN_HI(DHT_PORT, 6);
#define DHT_SET_SDA_PIN_AS_OUTPUT_LOW LO_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 6); GPIO_SET_PIN_LO(DHT_PORT, 6);
#define DHT_SET_SDA_PIN_AS_INPUT_FLOATING  LO_PIN_AS_INPUT_FLOATING(DHT_PORT, 6);
#define DHT_SET_SDA_PIN_AS_INPUT_PULL_UP  LO_PIN_AS_INPUT_PULL_UP(DHT_PORT, 6);
#elif DHT_PIN == 7
#define DHT_SET_SDA_PIN_AS_OUTPUT_HIGH LO_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 7); GPIO_SET_PIN_HI(DHT_PORT, 7);
#define DHT_SET_SDA_PIN_AS_OUTPUT_LOW LO_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 7); GPIO_SET_PIN_LO(DHT_PORT, 7);
#define DHT_SET_SDA_PIN_AS_INPUT_FLOATING  LO_PIN_AS_INPUT_FLOATING(DHT_PORT, 7);
#define DHT_SET_SDA_PIN_AS_INPUT_PULL_UP  LO_PIN_AS_INPUT_PULL_UP(DHT_PORT, 7);
#elif DHT_PIN == 8
#define DHT_SET_SDA_PIN_AS_OUTPUT_HIGH HI_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 8); GPIO_SET_PIN_HI(DHT_PORT, 8);
#define DHT_SET_SDA_PIN_AS_OUTPUT_LOW HI_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 8); GPIO_SET_PIN_LO(DHT_PORT, 8);
#define DHT_SET_SDA_PIN_AS_INPUT_FLOATING  HI_PIN_AS_INPUT_FLOATING(DHT_PORT, 8);
#define DHT_SET_SDA_PIN_AS_INPUT_PULL_UP  HI_PIN_AS_INPUT_PULL_UP(DHT_PORT, 8);
#elif DHT_PIN == 9
#define DHT_SET_SDA_PIN_AS_OUTPUT_HIGH HI_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 9); GPIO_SET_PIN_HI(DHT_PORT, 9);
#define DHT_SET_SDA_PIN_AS_OUTPUT_LOW HI_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 9); GPIO_SET_PIN_LO(DHT_PORT, 9);
#define DHT_SET_SDA_PIN_AS_INPUT_FLOATING  HI_PIN_AS_INPUT_FLOATING(DHT_PORT, 9);
#define DHT_SET_SDA_PIN_AS_INPUT_PULL_UP  HI_PIN_AS_INPUT_PULL_UP(DHT_PORT, 9);
#elif DHT_PIN == 10
#define DHT_SET_SDA_PIN_AS_OUTPUT_HIGH HI_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 10); GPIO_SET_PIN_HI(DHT_PORT, 10);
#define DHT_SET_SDA_PIN_AS_OUTPUT_LOW HI_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 10); GPIO_SET_PIN_LO(DHT_PORT, 10);
#define DHT_SET_SDA_PIN_AS_INPUT_FLOATING  HI_PIN_AS_INPUT_FLOATING(DHT_PORT, 10);
#define DHT_SET_SDA_PIN_AS_INPUT_PULL_UP  HI_PIN_AS_INPUT_PULL_UP(DHT_PORT, 10);
#elif DHT_PIN == 11
#define DHT_SET_SDA_PIN_AS_OUTPUT_HIGH HI_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 11); GPIO_SET_PIN_HI(DHT_PORT, 11);
#define DHT_SET_SDA_PIN_AS_OUTPUT_LOW HI_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 11); GPIO_SET_PIN_LO(DHT_PORT, 11);
#define DHT_SET_SDA_PIN_AS_INPUT_FLOATING  HI_PIN_AS_INPUT_FLOATING(DHT_PORT, 11);
#define DHT_SET_SDA_PIN_AS_INPUT_PULL_UP  HI_PIN_AS_INPUT_PULL_UP(DHT_PORT, 11);
#elif DHT_PIN == 12
#define DHT_SET_SDA_PIN_AS_OUTPUT_HIGH HI_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 12); GPIO_SET_PIN_HI(DHT_PORT, 12);
#define DHT_SET_SDA_PIN_AS_OUTPUT_LOW HI_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 12); GPIO_SET_PIN_LO(DHT_PORT, 12);
#define DHT_SET_SDA_PIN_AS_INPUT_FLOATING  HI_PIN_AS_INPUT_FLOATING(DHT_PORT, 12);
#define DHT_SET_SDA_PIN_AS_INPUT_PULL_UP  HI_PIN_AS_INPUT_PULL_UP(DHT_PORT, 12);
#elif DHT_PIN == 13
#define DHT_SET_SDA_PIN_AS_OUTPUT_HIGH HI_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 13); GPIO_SET_PIN_HI(DHT_PORT, 13);
#define DHT_SET_SDA_PIN_AS_OUTPUT_LOW HI_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 13); GPIO_SET_PIN_LO(DHT_PORT, 13);
#define DHT_SET_SDA_PIN_AS_INPUT_FLOATING  HI_PIN_AS_INPUT_FLOATING(DHT_PORT, 13);
#define DHT_SET_SDA_PIN_AS_INPUT_PULL_UP  HI_PIN_AS_INPUT_PULL_UP(DHT_PORT, 13);
#elif DHT_PIN == 14
#define DHT_SET_SDA_PIN_AS_OUTPUT_HIGH HI_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 14); GPIO_SET_PIN_HI(DHT_PORT, 14);
#define DHT_SET_SDA_PIN_AS_OUTPUT_LOW HI_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 14); GPIO_SET_PIN_LO(DHT_PORT, 14);
#define DHT_SET_SDA_PIN_AS_INPUT_FLOATING  HI_PIN_AS_INPUT_FLOATING(DHT_PORT, 14);
#define DHT_SET_SDA_PIN_AS_INPUT_PULL_UP  HI_PIN_AS_INPUT_PULL_UP(DHT_PORT, 14);
#elif DHT_PIN == 15
#define DHT_SET_SDA_PIN_AS_OUTPUT_HIGH HI_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 15); GPIO_SET_PIN_HI(DHT_PORT, 15);
#define DHT_SET_SDA_PIN_AS_OUTPUT_LOW HI_PIN_AS_GPIO_OUT_PP_LOW_SPEED(DHT_PORT, 15); GPIO_SET_PIN_LO(DHT_PORT, 15);
#define DHT_SET_SDA_PIN_AS_INPUT_FLOATING  HI_PIN_AS_INPUT_FLOATING(DHT_PORT, 15);
#define DHT_SET_SDA_PIN_AS_INPUT_PULL_UP  HI_PIN_AS_INPUT_PULL_UP(DHT_PORT, 15);
#else#error "Invalid DHT_PIN value (should be in range 0-15)!"
#endif

#endif
