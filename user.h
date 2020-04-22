/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/
// BUTTONS definition
#define CHANGE_STATE_BUTTON RB0


// SENSORS definition
#define GATE_CLOSED_SENSOR         RB4
#define GATE_OPENED_SENSOR         RB5
#define OVERTORQUE_DETECTED_SENSOR RB6
#define GATE_IS_RUNNING_SENSOR     RB7

// outputs for motor control
#define MOVE_FORWARD_SIGNAL        RA0
#define MOVE_BACKWARD_SIGNAL       RA1

// signal lights pin
#define RED_LIGHT           RA2
#define YELLOW_LIGHT        RA3
#define GREEN_LIGHT         RA4

// direction of movement 
#define FORWARD 1
#define BACK    0

// button and signal definition (inverted for open drain connection)
#define ON  0
#define OFF 1

// Time for rollback action in the overtorque event.
#define ROLL_BACK_TIME  1500
#define SLEEP_DELAY     20

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */
