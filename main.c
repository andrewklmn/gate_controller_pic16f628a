/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <pic16f628a.h>

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
char overtorgue_flag = OFF;
char movement_direction;

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();


    while(1)
    {
        if (overtorgue_flag==ON || (GATE_CLOSED_SENSOR==ON  && GATE_OPENED_SENSOR==ON)) {
            GREEN_LIGHT = OFF;
            YELLOW_LIGHT= OFF;
            RED_LIGHT = !RED_LIGHT;
            
        } else if(GATE_CLOSED_SENSOR==ON && GATE_OPENED_SENSOR==OFF) {
            
            GREEN_LIGHT  = OFF;
            YELLOW_LIGHT = OFF;
            RED_LIGHT = ON;
            
        } else if(GATE_CLOSED_SENSOR==OFF && GATE_OPENED_SENSOR==ON) {
            
            GREEN_LIGHT=ON;
            YELLOW_LIGHT=OFF;
            RED_LIGHT=OFF;
            
        } else if(GATE_CLOSED_SENSOR==OFF 
                    && GATE_OPENED_SENSOR==OFF 
                    && GATE_IS_RUNNING_SENSOR==ON) {
            
            GREEN_LIGHT = OFF;
            YELLOW_LIGHT=!YELLOW_LIGHT;
            RED_LIGHT = OFF;
            
        } else {
            GREEN_LIGHT = OFF;
            YELLOW_LIGHT= OFF;
            RED_LIGHT   = OFF;
        };
        __delay_ms(500);
    }

}

