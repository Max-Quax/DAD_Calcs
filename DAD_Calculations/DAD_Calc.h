/*
 * DAD_Calc.h
 *
 *  Created on: Feb 8, 2023
 *      Author: Max
 */

#ifndef DAD_CALC_H_
#define DAD_CALC_H_

// Standard includes
#include <stdlib.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

// Utils
#include <math.h>
#include <arm_math.h>
#include <stdint.h>

#define MOVING_AVERAGE_N 128;    // Calculate the moving averages based on the past N data packets

// TODO remove on integration
typedef enum {TEMP = 0b000, HUM = 0b001, VIB = 0b010, MIC = 0b011, LOWBAT = 0b100, ERR = 0b101, STOP = 0b110, START = 0b111} packetType;

typedef struct DAD_Calc_Struct_{
    packetType  type;
    uint16_t    numSamplesCollected;
    float       movAvgSamples[MOVING_AVERAGE_NUM];
} DAD_Calc_Struct;

// Initializes struct's values
void DAD_Calc_InitStruct(DAD_Calc_Struct* calcStruct);

// Moving average
    // Takes newest reading, updates sensor's moving average
void DAD_Calc_MovingAvg(uint8_t* packet, DAD_Calc_Struct* calcStruct);

// Average intensity
    // Takes reading, updates sensor's average intensity
void DAD_Calc_AvgIntensity(DAD_Data_Packet* newestReading, DAD_Sensor* sensor);

// Clears moving average data. To be called on sensor disconnect
void DAD_Calc_Clear_History(DAD_Calc_Struct* calcStruct);

// TODO Condition Humidity data
float DAD_Calc_ConditionHum(uint8_t* packet);

// TODO Condition Temperature Data
float DAD_Calc_ConditionTemp(uint8_t* packet);

// TODO Condition Vib Data
float DAD_Calc_ConditionVib(uint8_t* packet);

// TODO Condition Vib Data
float DAD_Calc_ConditionMic(uint8_t* packet);
#endif /* DAD_CALC_H_ */
