/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/
// BUTTONS definition
#define CHANGE_STATE_BUTTON RB0


// SENSORS definition
#define GATE_CLOSED_SENSOR         RB4
#define GATE_OPENED_SENSOR         RB5
#define OVERTORQUE_DETECTED_SENSOR RB6
#define GATE_IS_RUNNING_SENSOR     RA5
#define IR_SENSOR                  RB7

// output for motor control
#define MOVE_FORWARD_SIGNAL        RA0
#define MOVE_BACKWARD_SIGNAL       RA1

// output for motor and remote power control
#define MOTOR_POWER_SWITCH         RA6

// output signal lights pin
#define RED_LIGHT           RA2
#define YELLOW_LIGHT        RA3
#define GREEN_LIGHT         RA7

// direction of movement 
#define FORWARD 1
#define BACK    0

// button state definition (inverted for normaly opened relay)
#define ON  0
#define OFF 1

// signal  definition for motor and lights control
#define TURN_ON  1
#define TURN_OFF 0

// Time for rollback action in the overtorque event.
#define ROLL_BACK_TIME  500
#define SLEEP_DELAY     20

/* TODO Application specific user parameters used in user.c may go here */
volatile unsigned char temp;

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */
