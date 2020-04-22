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
    /* TODO Initialize User Ports/Peripherals/Project here */
    CMCON = 0b111; //Disable PORTA Comparators  
    
    /* Setup analog functionality and port direction */
    TRISA = 0b00000000;
    TRISB = 0b11110001;

    /* Initialize peripherals */
    PORTA = 0b11111111;
    
    /* Enable interrupts */
    INTCON = 0b10011000;
    INTEDG = 0;
    
    
    RED_LIGHT = ON;
    __delay_ms(500);
    YELLOW_LIGHT = ON;
    __delay_ms(500);
    RED_LIGHT = OFF;
    YELLOW_LIGHT = OFF;
    GREEN_LIGHT = ON;
    __delay_ms(500);
    GREEN_LIGHT = 1;
    
    if (GATE_CLOSED_SENSOR==0) {
        movement_direction = BACK;
    } else if (GATE_OPENED_SENSOR==0) {
        movement_direction = FORWARD;
    } else {
        movement_direction = BACK;
    };
    
    
}

