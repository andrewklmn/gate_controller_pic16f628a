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
extern int counter;

extern char must_be_closed;

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
        if (GATE_CLOSED_SENSOR==ON && GATE_OPENED_SENSOR==ON ) {
            //gate position sensors error
            MOVE_FORWARD_SIGNAL = TURN_OFF; 
            MOVE_BACKWARD_SIGNAL = TURN_OFF;
            
        } else if (MOVE_FORWARD_SIGNAL==TURN_ON || MOVE_BACKWARD_SIGNAL==TURN_ON ) {
            //gate is moving
            MOVE_FORWARD_SIGNAL = TURN_OFF; 
            MOVE_BACKWARD_SIGNAL = TURN_OFF;
            movement_direction = (movement_direction==BACK)?FORWARD:BACK;
            
        } else {
            // gate is stopped
            
            if(movement_direction==FORWARD) {
                // it is going to close gate
                if (GATE_CLOSED_SENSOR==OFF) {
                    //gate is not closed yet
                    MOVE_BACKWARD_SIGNAL = TURN_OFF;
                    // check if the IR sensor is clear
                    if (IR_SENSOR==OFF) {
                        movement_direction = FORWARD;
                        MOVE_FORWARD_SIGNAL  = TURN_ON;
                    };
                } else {
                    //gate is closed. start opening
                    MOVE_FORWARD_SIGNAL  = TURN_OFF;
                    movement_direction = BACK;
                    MOVE_BACKWARD_SIGNAL = TURN_ON;
                    
                };
            } else {
                //it is going to open gate
                if (GATE_OPENED_SENSOR==OFF) {
                    //gate is not opened yet
                    MOVE_FORWARD_SIGNAL  = TURN_OFF;                
                    movement_direction = BACK;
                    MOVE_BACKWARD_SIGNAL = TURN_ON;
                } else {
                    //gate is opened already. start closing
                    MOVE_BACKWARD_SIGNAL = TURN_OFF;
                    if (IR_SENSOR==OFF) {
                        movement_direction = FORWARD;
                        MOVE_FORWARD_SIGNAL  = TURN_ON;
                    } else {
                        MOVE_FORWARD_SIGNAL  = TURN_OFF;
                    };
                };
            };
        };
        
        overtorgue_flag = OFF;
        must_be_closed = OFF;
        MOTOR_POWER_SWITCH = TURN_ON;
        counter=SLEEP_DELAY;
        
        PORTB; //read port before INTF reset 
        INTF=0;
    } else if (RBIF){
        // state of gates was changed
        
        if (IR_SENSOR==ON
            && MOVE_FORWARD_SIGNAL==TURN_ON
            && must_be_closed == OFF ){
                MOVE_FORWARD_SIGNAL = TURN_OFF;
                movement_direction = BACK;
                MOVE_BACKWARD_SIGNAL = TURN_ON;         
        };
        
        if (OVERTORQUE_DETECTED_SENSOR==ON) {
            //action for rollback
            must_be_closed = OFF;
            if (movement_direction==FORWARD) {
                if (GATE_OPENED_SENSOR==ON) {
                    MOVE_FORWARD_SIGNAL  = TURN_OFF;
                    MOVE_BACKWARD_SIGNAL = TURN_OFF;
                } else {
                    if(GATE_IS_RUNNING_SENSOR==ON) {
                        MOVE_FORWARD_SIGNAL  = TURN_OFF;
                        MOVE_BACKWARD_SIGNAL = TURN_ON;
                        __delay_ms(ROLL_BACK_TIME);
                        MOVE_BACKWARD_SIGNAL = TURN_OFF;
                        movement_direction = BACK;
                    };
                };
                overtorgue_flag=ON;
            } else {
                MOVE_BACKWARD_SIGNAL = TURN_OFF;
                MOVE_FORWARD_SIGNAL  = TURN_OFF;
                overtorgue_flag=ON;
                movement_direction = FORWARD;
            }; 
                    
        };
        
        if (GATE_CLOSED_SENSOR==ON && GATE_OPENED_SENSOR==ON) {
            //gate closed
            MOVE_FORWARD_SIGNAL  = TURN_OFF;
            MOVE_BACKWARD_SIGNAL = TURN_OFF;
            
        } else if (GATE_CLOSED_SENSOR==ON) {
            //gate closed
            MOVE_FORWARD_SIGNAL  = TURN_OFF;
            movement_direction = BACK;
            must_be_closed = ON;
            counter=SLEEP_DELAY;
            
        } else if (GATE_OPENED_SENSOR==ON) {
            //stop the movement
            MOVE_BACKWARD_SIGNAL = TURN_OFF;
            movement_direction = FORWARD;      
            
        } else if (GATE_CLOSED_SENSOR==OFF 
                        && movement_direction== BACK
                        && must_be_closed == ON
                        && MOVE_BACKWARD_SIGNAL==TURN_OFF) {
            // someone is trying to open gate by hand... 
            MOTOR_POWER_SWITCH = TURN_ON;
            MOVE_FORWARD_SIGNAL = TURN_ON;
            movement_direction = FORWARD;
        };
        PORTB;  //read port before RBIF reset 
        RBIF=0;
    };
}
#endif


