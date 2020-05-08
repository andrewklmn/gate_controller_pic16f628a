/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include <pic16f628a.h>

#include "system.h"
#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */
extern char movement_direction;

void InitApp(void)
{
    /* Disable interrupts */
    INTCON = 0b00000000;
    
    /* TODO Initialize User Ports/Peripherals/Project here */
    CMCON = 0b00000111; //Disable PORTA Comparators  
    
    /* Setup analog functionality and port direction */
    TRISA = 0b00000000;
    PORTA = 0b00000000;

    TRISB = 0b11110001;    
    nRBPU = 0;    
    
    // disable motor power
    MOTOR_POWER_SWITCH = TURN_OFF;
    // disable movement before motor start
    MOVE_FORWARD_SIGNAL = TURN_OFF;
    MOVE_BACKWARD_SIGNAL = TURN_OFF;   
    
    RED_LIGHT = TURN_ON;
    __delay_ms(500);
    YELLOW_LIGHT = TURN_ON;
    __delay_ms(500);
    RED_LIGHT = TURN_OFF;
    YELLOW_LIGHT = TURN_OFF;
    GREEN_LIGHT = TURN_ON;
    __delay_ms(500);
    GREEN_LIGHT = TURN_OFF;

    
    if (GATE_CLOSED_SENSOR==0) {
        movement_direction = BACK;
    } else if (GATE_OPENED_SENSOR==0) {
        movement_direction = FORWARD;
    } else {
        movement_direction = BACK;
    };

    // disable movement before motor start
    MOVE_FORWARD_SIGNAL = TURN_OFF;
    MOVE_BACKWARD_SIGNAL = TURN_OFF;    
    
    __delay_ms(100);
    // enable motor equipment
    MOTOR_POWER_SWITCH = TURN_ON;

        
    __delay_ms(100);
    /* Enable interrupts */
    INTCON = 0b10011000;
    INTEDG = 0; 
    
};

