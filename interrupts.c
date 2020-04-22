/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>
#include <pic16f628a.h>        /* For true/false definition */
#include "system.h"
#include "user.h"

extern char overtorgue_flag;
extern char movement_direction;

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* Baseline devices don't have interrupts. Note that some PIC16's 
 * are baseline devices.  Unfortunately the baseline detection macro is 
 * _PIC12 */
#ifndef _PIC12

void __interrupt () my_isr_routine (void) {

    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 seperate if blocks.
    Do not use a seperate if block for each interrupt flag to avoid run
    time errors. */
    
    if(INTF){
       // CHANGE_STATE_BUTTON was pressed by user
        overtorgue_flag = OFF;
        if (GATE_CLOSED_SENSOR==ON && GATE_OPENED_SENSOR==ON ) {
            MOVE_FORWARD_SIGNAL = OFF; 
            MOVE_BACKWARD_SIGNAL = OFF;
        } else if (MOVE_FORWARD_SIGNAL==ON || MOVE_BACKWARD_SIGNAL==ON ) {
            MOVE_FORWARD_SIGNAL = OFF; 
            MOVE_BACKWARD_SIGNAL = OFF;
            movement_direction = (movement_direction==BACK)?FORWARD:BACK;
        } else {
            if(movement_direction==FORWARD) {
                MOVE_BACKWARD_SIGNAL = OFF;
                MOVE_FORWARD_SIGNAL  = ON;
            } else {
                MOVE_BACKWARD_SIGNAL = ON;
                MOVE_FORWARD_SIGNAL  = OFF;
            };
        };
        INTF=0;
    } else if (RBIF){
        // state of gates was changed
        if (OVERTORQUE_DETECTED_SENSOR==ON) {
            //action for rollback
            if (movement_direction==FORWARD) {
                MOVE_FORWARD_SIGNAL  = OFF;
                MOVE_BACKWARD_SIGNAL = ON;
                __delay_ms(ROLL_BACK_TIME);
                MOVE_BACKWARD_SIGNAL = OFF;
                overtorgue_flag=ON;
                movement_direction = BACK;
            } else {
                MOVE_BACKWARD_SIGNAL = OFF;
                overtorgue_flag=ON;
                movement_direction = BACK;
            }; 
                    
        } else if (GATE_CLOSED_SENSOR==ON && GATE_OPENED_SENSOR==ON) {
            //gate closed
            MOVE_FORWARD_SIGNAL  = OFF;
            MOVE_BACKWARD_SIGNAL = OFF;
            overtorgue_flag=ON;

        } else if (GATE_CLOSED_SENSOR==ON) {
            //gate closed
            MOVE_FORWARD_SIGNAL  = OFF;
            movement_direction = BACK;
            
        } else if (GATE_OPENED_SENSOR==ON) {
            //stop the movement
            MOVE_BACKWARD_SIGNAL = OFF;
            movement_direction = FORWARD;            
        };
        RBIF=0;
    };
}
#endif


