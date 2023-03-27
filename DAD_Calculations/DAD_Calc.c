#include <DAD_Calc.h>

// Initializes struct's values
void DAD_Calc_InitStruct(DAD_Calc_Struct* calcStruct){
    List_clearList(&calcStruct->list);      // Init linkedlist
    calcStruct->numSamplesCollected = 0;
    calcStruct->type = START;
}

// Moving average
    // Takes newest reading, updates sensor's moving average
float DAD_Calc_MovingAvg(uint8_t* packet, DAD_Calc_Struct* calcStruct){
    List_Elem newElement;
    newElement.val = conditionPacket(packet);
    newElement.prev = NULL;
    newElement.next = NULL;

    // Check packet type
    packetType type = (packetType)(packet[0] & PACKET_TYPE_MASK);
    if(type != calcStruct->type){
        // Clear moving avg info, start from scratch
        List_clearList(&calcStruct->list);  // Boy oh boy, I sure hope this doesn't cause memory leakage
        calcStruct->numSamplesCollected = 1;
        calcStruct->type = type;
        // Add Datum to linked list
        List_put(&calcStruct->list, &newElement);
        return newElement.val;
    }

    // Add sample to linked list
    if(calcStruct->numSamplesCollected < MOVING_AVERAGE_N){
        List_put(&calcStruct->list, &newElement);
        calcStruct->numSamplesCollected++;
    }
    else{
        // Add one, remove one
        List_put(&calcStruct->list, &newElement);
        List_get(&calcStruct->list);
    }

    // Calc avg Intensity
    double sum = 0;
    List_Elem *temp;

    for (temp = calcStruct->list.head; temp != NULL; temp = List_next(temp)) {
        sum += temp->val;
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
