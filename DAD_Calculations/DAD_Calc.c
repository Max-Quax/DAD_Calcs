#include <DAD_Calc.h>

// Moving average
    // Takes newest reading, updates sensor's moving average
void DAD_Calc_MovingAvg(DAD_Data_Packet* newestReading, DAD_Sensor* sensor){
    // TODO conditioning
}

// Average Intensity
    // Takes reading, updates sensor's average intensity
void DAD_Calc_AvgIntensity(DAD_Data_Packet* newestReading, DAD_Sensor* sensor){
    // Calculate average intensity
    int i;
    int sum = 0;
    for(i = 0; i < ; i++){
        sum = sum + newestReading->data[i];
    }

    // Calculate average intensity
    // TODO convert Q15 to float
    sensor->averageIntensity = 20 * logf(sum / newestReading->dataSize);
}


// Clears moving average data. To be called on sensor disconnect
void DAD_Calc_Clear_History(DAD_Calc_Struct* calcStruct){

}

// TODO Condition Humidity data
float DAD_Calc_ConditionHum(uint8_t* packet){
    return packet[2]%100;
}

// TODO Condition Temperature Data
float DAD_Calc_ConditionTemp(uint8_t* packet){
    return packet[2]%120;
}

// TODO Condition Vib Data
float DAD_Calc_ConditionVib(uint8_t* packet){
    return packet[2];
}

// TODO Condition Vib Data
float DAD_Calc_ConditionMic(uint8_t* packet){
    return packet[2];
}
