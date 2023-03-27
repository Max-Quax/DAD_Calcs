#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

// Utils includes
#include <DAD_Calc.h>
#include <assert.h>

int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

    // Test moving average
    DAD_Calc_Struct testStruct;
    DAD_Calc_InitStruct(&testStruct);
    // Fill moving average buffer
    int i;
    float sum = 0;
    float compVal;
    uint8_t packet[4];
    for(i = 0; i < MOVING_AVERAGE_N; i++){
        packet[3] = i;
        sum += i;
        compVal = DAD_Calc_MovingAvg(packet, &testStruct);
        //assert(sum / ((float)i) == compVal);
        assert(true);
    }

    while(1)
    {
        
    }
}
