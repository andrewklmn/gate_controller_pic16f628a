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
int counter = SLEEP_DELAY;
char must_be_closed = OFF;


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

    if (GATE_CLOSED_SENSOR==ON) {
        movement_direction = BACK;
        must_be_closed = ON;
    };

    while(1)
    {
        if (overtorgue_flag==ON ) {
            
            GREEN_LIGHT = TURN_OFF;
            YELLOW_LIGHT= TURN_OFF;
            RED_LIGHT = !RED_LIGHT;
            
        } else if (GATE_CLOSED_SENSOR==ON  && GATE_OPENED_SENSOR==ON) {
            
            GREEN_LIGHT = TURN_OFF;
            YELLOW_LIGHT= TURN_OFF;
            RED_LIGHT = TURN_ON;
            __delay_ms(200);
            RED_LIGHT = TURN_OFF;
            __delay_ms(200);
            RED_LIGHT = TURN_ON;
            __delay_ms(200);
            RED_LIGHT = TURN_OFF;
            
        } else if(GATE_CLOSED_SENSOR==ON && GATE_OPENED_SENSOR==OFF) {
            
            GREEN_LIGHT  = TURN_OFF;
            YELLOW_LIGHT = TURN_OFF;
            if (counter>0) {
                RED_LIGHT = TURN_ON;
            } else {
                RED_LIGHT = TURN_OFF;
                MOTOR_POWER_SWITCH = TURN_OFF;
            };
        } else if(GATE_CLOSED_SENSOR==OFF && GATE_OPENED_SENSOR==ON) {
            
            GREEN_LIGHT=TURN_ON;
            YELLOW_LIGHT=TURN_OFF;
            RED_LIGHT=TURN_OFF;
            
        } else if(GATE_CLOSED_SENSOR==OFF 
                    && GATE_OPENED_SENSOR==OFF 
                    && GATE_IS_RUNNING_SENSOR==ON) {
            
            if (MOVE_BACKWARD_SIGNAL==TURN_ON) { 
                GREEN_LIGHT = TURN_ON;
            } else {
                GREEN_LIGHT = TURN_OFF;
            };
            YELLOW_LIGHT=!YELLOW_LIGHT;
            if (MOVE_FORWARD_SIGNAL==TURN_ON) { 
                RED_LIGHT = TURN_ON;
            } else {
                RED_LIGHT = TURN_OFF;
            };
        } else if(GATE_CLOSED_SENSOR==OFF 
                    && GATE_OPENED_SENSOR==OFF 
                    && GATE_IS_RUNNING_SENSOR==OFF) {
            
            GREEN_LIGHT = TURN_OFF;
            YELLOW_LIGHT=!YELLOW_LIGHT;
            //YELLOW_LIGHT=ON;
            RED_LIGHT = TURN_OFF;
            
        } else {
            GREEN_LIGHT = TURN_OFF;
            YELLOW_LIGHT= TURN_OFF;
            RED_LIGHT   = TURN_OFF;
        };
        
        counter--;
        if (counter<0) {
            counter = 0;
        };
        
        __delay_ms(500);
    }

}

