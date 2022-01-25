#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/adc.h"
#include "driverlib/debug.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"

int main(void)
{
    int x = 9000;
    int y = 0;

    // reloj a 16MHz
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    // Dividir el reloj para el PWM en 1
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

    // Habilitamos el módulo 1 del PWM
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);

    // Habilitamos el Puerto F y el pin 1 con el Modulo 1 PWM 5
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinConfigure(GPIO_PF1_M1PWM5); // Led 1 PF1
    GPIOPinConfigure(GPIO_PF2_M1PWM6); // Led 2 PF2
    GPIOPinConfigure(GPIO_PF3_M1PWM7); // Led 3 PF3
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    // Configurar el generador del PWM
    PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    // Set the PWM period to 250Hz.  To calculate the appropriate parameter
    // use the following equation: N = (1 / f) * SysClk.  Where N is the
    // function parameter, f is the desired frequency, and SysClk is the
    // system clock frequency.
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, 320000);
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, 320000);

    // Periodo = 52ns - 52n(x)=2ms - x=320000
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, 9000);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, 9000);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, 9000);

    PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT , true);
    PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT , true);
    PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT , true);
    PWMGenEnable(PWM1_BASE, PWM_GEN_2);
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);

    /*while(1)
    {
        PWMOutputState(PWM1_BASE, (PWM_OUT_5_BIT), true);
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_4,9000);
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5,9000);
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6,9000);
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7,9000);
        SysCtlDelay(8000000);
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_4,35000);
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5,35000);
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6,35000);
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7,35000);
        SysCtlDelay(8000000);
    }*/

    while(1)
    {
        for(y=0;y<36;y++)
        {
           PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, x);
           SysCtlDelay(8000000);
           x+=1000;
        }
        x=9000;
    }
}
























