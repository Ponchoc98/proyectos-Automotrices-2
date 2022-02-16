
// Práctica 4 - Timers
// Práctica Independiente 1 - Stepper

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/pin_map.h"

int vel_motor = 0x5FFF;
int state = 0;
int direction = 0;

void Timer0BIntHandler(void)
{
    if(direction==0)
    {
        if(state==0)
        {
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0x00);
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4);
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5);
            state++;
        }
        else if(state==1)
        {
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0x00);
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5);
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6);
            state++;
        }
        else if(state==2)
        {
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0x00);
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6);
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7);
            state++;
        }
        else if(state==3)
        {
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0x00);
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7);
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4);
            state++;
        }
        if(state>=4)
        {
            state=0;
        }
    }
    else if(direction==1)
    {
        if(state==0)
        {
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0x00);
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7);
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4);
            state++;
        }
        else if(state==1)
        {
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0x00);
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6);
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7);
            state++;
        }
        else if(state==2)
        {
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0x00);
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5);
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6);
            state++;
        }
        else if(state==3)
        {
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0x00);
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4);
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5);
            state++;
        }
        if(state>=4)
        {
            state=0;
        }
    }
    TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
}

/*void paso_motor_Izquierda() // Funcion para la secuencia del motor pa la izquierda (Toda la función es 1 paso)
{
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0x00);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5); //0011 0000 = 48 = 0x30
    //delay();
    Timer0BIntHandler();
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0x00);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6); //0110 0000  = 96 = 0x60
    //delay();
    Timer0BIntHandler();
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0x00);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7); //1100 0000 = 192 = 0xC0
    //delay();
    Timer0BIntHandler();
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0x00);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4); //1001 0000 = 144 = 0x90
    //delay();
    Timer0BIntHandler();
}*/

/*void paso_motor_Derecha() // Funcion para la secuencia del motor pa la derecha (Toda la función es 1 paso)
{
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0x00);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4); //1001 0000 = 144 = 0x90
    //delay();
    Timer0BIntHandler();
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0x00);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7); //1100 0000 = 192 = 0xC0
    //delay();
    Timer0BIntHandler();
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0x00);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6); //0110 0000  = 96 = 0x60
    //delay();
    Timer0BIntHandler();
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0x00);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5); //0011 0000 = 48 = 0x30
    //delay();
    Timer0BIntHandler();
}*/

void GPIOF_Handler_mifuncion()
{
    direction++;
    if(direction>=2)
    {
        direction=0;
    }
    GPIOIntStatus(GPIO_PORTF_BASE, true);
    GPIOIntClear(GPIO_PORTF_BASE, GPIO_INT_PIN_4);
}

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC));

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0));

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_RISING_EDGE);
    GPIOIntRegister(GPIO_PORTF_BASE, GPIOF_Handler_mifuncion);
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_4);
    IntMasterEnable();

    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4); // Pines para la entrada al motor
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_7);

    TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_B, 24000);
    IntMasterEnable();
    TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
    IntEnable(INT_TIMER0B);
    TimerEnable(TIMER0_BASE, TIMER_B);

    while(1)
    {
        //paso_motor_Izquierda();
        //paso_motor_Derecha();
    }
}
