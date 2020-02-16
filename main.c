#include "device.h"
#include "driverlib.h"



uint32_t count;
uint8_t test;

#define button GPIO_readPin(32)

interrupt void XINT1_ISR(void);
void INTERRUPT_Init(void);

int main(void)
{
    Device_init();
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();


    Interrupt_register(INT_XINT1, &XINT1_ISR);
    Interrupt_enable(INT_XINT1);

    INTERRUPT_Init();

    EINT;                                       // Enable Global Interrupts


    while(1)
    {
    }
}

void INTERRUPT_Init(void)
{
    GPIO_setDirectionMode(32, GPIO_DIR_MODE_IN);
    GPIO_setQualificationMode(32, GPIO_QUAL_SYNC);
    GPIO_setPadConfig(32, GPIO_PIN_TYPE_PULLUP);
    GPIO_setInterruptPin(32, GPIO_INT_XINT1);
    GPIO_setInterruptType(GPIO_INT_XINT1, GPIO_INT_TYPE_FALLING_EDGE);
    GPIO_enableInterrupt(GPIO_INT_XINT1);
}

interrupt void XINT1_ISR(void)
{
    for(uint16_t i=0; i<1000; i++);
    count++;

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}
