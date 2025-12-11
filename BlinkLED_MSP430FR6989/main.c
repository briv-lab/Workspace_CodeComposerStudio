#include <msp430.h> 
#include <driverlib.h>

int main(void) {
    WDT_A_hold(WDT_A_BASE);

    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P9, GPIO_PIN7);

    PMM_unlockLPM5();

    while(1) 
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);

        volatile int j;
        for(j=0; j<200; j++) 
        {
            GPIO_setOutputHighOnPin(GPIO_PORT_P9, GPIO_PIN7);
            __delay_cycles(20);

            GPIO_setOutputLowOnPin(GPIO_PORT_P9, GPIO_PIN7);
            __delay_cycles(2000);
        }

        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
        GPIO_setOutputLowOnPin(GPIO_PORT_P9, GPIO_PIN7);
        
        __delay_cycles(400000);
    }
}