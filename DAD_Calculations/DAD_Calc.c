#include <DAD_Calc.h>

// Initializes struct's values
void DAD_Calc_InitStruct(DAD_Calc_Struct* calcStruct){
    // TODO Clear list
    calcStruct->numSamplesCollected = 0;
    calcStruct->type = START;
}

// Moving average
    // Takes newest reading, updates sensor's moving average
float DAD_Calc_MovingAvg(uint8_t* packet, DAD_Calc_Struct* calcStruct){
    // Check packet type
    packetType type = (packetType)(packet[0] & PACKET_TYPE_MASK);
    float data = conditionPacket(packet);

    if(type != calcStruct->type){
        // Restart
        calcStruct->numSamplesCollected = 0;
        calcStruct->type = type;

        // Add Datum to list
        return data; // TODO return value;
    }

    // Add sample to linked list
    calcStruct->list[calcStruct->numSamplesCollected%MOVING_AVERAGE_N];
    calcStruct->numSamplesCollected++;

    // Calc avg Intensity
    double sum = 0;
    int i;

    for (i = 0; i < calcStruct->numSamplesCollected; i++) {
        sum += calcStruct->list[calcStruct->numSamplesCollected%MOVING_AVERAGE_N];
    }
    return sum * MOVING_AVERAGE_N_INVERSE;   // return sum/N
}

// Average Intensity
    // Takes reading, updates sensor's average intensity
float DAD_Calc_AvgIntensity(uint8_t* packet, packetType type){
    // Calculate average intensity
//    int i;
//    int sum = 0;
//    for(i = 0; i < ; i++){
//        sum = sum + newestReading->data[i];
//    }

    // Calculate average intensity
    // TODO convert Q15 to float
    //sensor->averageIntensity = 20 * logf(sum / newestReading->dataSize);
    return 0;
}


// Clears moving average data. To be called on sensor disconnect
void DAD_Calc_Clear_History(DAD_Calc_Struct* calcStruct){
    List_clearList(&calcStruct->list);  // Boy oh boy, I sure hope this doesn't cause memory leakage
}

// Condition any packet
float conditionPacket(uint8_t* packet){
    return packet[2];
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
