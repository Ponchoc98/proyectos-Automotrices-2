#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/adc.h"
#include "driverlib/pin_map.h"

#define P 1.1839
#define CF 2.61
#define S 0.019
#define BRAKESOPENED 0
#define BRAKESCLOSED 1
#define WINGUP 0
#define WINGDOWN 1
#define WINGREADY 2
#define WINGPENDING 3
#define TILTED 0
#define FLAT 1
#define DIFFUP 0
#define DIFFDOWN 1

void openBrakes(void);
void closeBrakes(void);
void raiseWing(void);
void retractWing(void);
void tiltUp(void);
void tiltDown(void);
void raiseDiff(void);
void retractDiff(void);

char brakeStatus = BRAKESCLOSED, wingStatus = WINGPENDING, tiltStatus = FLAT, diffStatus = DIFFUP;

void main(void)
{
    uint32_t valorADC0;
    uint32_t valorADC1;
    uint32_t valorADC2;
    uint32_t valorADC3;
    int Vehicle_speed;
    int Air_speed;
    int Brake_pad_temp;
    int Abs_vehicle_speed;
    int Lift;

    SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ); // Pal ADC

    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    //GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_5 | GPIO_PIN_2 | GPIO_PIN_1);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_2 | GPIO_PIN_1);
    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_2);
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceConfigure(ADC0_BASE, 2, ADC_TRIGGER_PROCESSOR, 0);
    //ADCSequenceConfigure(ADC1_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceConfigure(ADC1_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH1 | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceStepConfigure(ADC0_BASE, 2, 0, ADC_CTL_CH2 | ADC_CTL_IE | ADC_CTL_END);
    //ADCSequenceStepConfigure(ADC1_BASE, 1, 0, ADC_CTL_CH8 | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceStepConfigure(ADC1_BASE, 0, 0, ADC_CTL_CH5 | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 3);
    ADCSequenceEnable(ADC0_BASE, 2);
    //ADCSequenceEnable(ADC1_BASE, 1);
    ADCSequenceEnable(ADC1_BASE, 0);
    ADCIntClear(ADC0_BASE, 3);
    ADCIntClear(ADC0_BASE, 2);
    //ADCIntClear(ADC1_BASE, 1);
    ADCIntClear(ADC1_BASE, 0);

    while(1)
        {
            ADCProcessorTrigger(ADC0_BASE, 3);
            while(!ADCIntStatus(ADC0_BASE, 3, false));
            ADCIntClear(ADC0_BASE, 3);
            ADCSequenceDataGet(ADC0_BASE, 3, &valorADC3);
            SysCtlDelay(SysCtlClockGet() / 100);

            ADCProcessorTrigger(ADC0_BASE, 2);
            while(!ADCIntStatus(ADC0_BASE, 2, false));
            ADCIntClear(ADC0_BASE, 2);
            ADCSequenceDataGet(ADC0_BASE, 2, &valorADC2);
            SysCtlDelay(SysCtlClockGet() / 100);

            /*ADCProcessorTrigger(ADC1_BASE, 1);
            while(!ADCIntStatus(ADC1_BASE, 1, false));
            ADCIntClear(ADC1_BASE, 1);
            ADCSequenceDataGet(ADC1_BASE, 1, &valorADC1);
            SysCtlDelay(SysCtlClockGet() / 100);*/

            ADCProcessorTrigger(ADC1_BASE, 0);
            while(!ADCIntStatus(ADC1_BASE, 0, false));
            ADCIntClear(ADC1_BASE, 0);
            ADCSequenceDataGet(ADC1_BASE, 0, &valorADC0);
            SysCtlDelay(SysCtlClockGet() / 100);

            Vehicle_speed = (valorADC3 * 250) / 4095;
            Air_speed = 0.02 * valorADC2 - 50;
            Brake_pad_temp = 0.11 * valorADC0 + 150;
            Abs_vehicle_speed = Vehicle_speed - Air_speed; // Velocidad absoluta del vehiculo
            Lift = P * Abs_vehicle_speed * Abs_vehicle_speed * S * CF; // Sustentacion
        }

}

