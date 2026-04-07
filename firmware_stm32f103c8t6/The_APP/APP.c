/*******************************************************************************
  * Name    : APP.c
  * Author  : KitaOvO
  * Function: Quadruped Robot Movement Control Algorithms
  * Version : V1.0.0
  * Date    : 2025.3.15
*******************************************************************************/

/*==================== INCLUDE FILES ====================*/
#include "app.h"

/*==================== CONSTANT DEFINITIONS ====================*/

/*******************************************************************************
  * LEG IDENTIFICATION DIAGRAM
  * 
  * Physical layout of the quadruped robot legs:
  * 
  *      LEFT FRONT (0)          RIGHT FRONT (1)
  * 
  * 
  *      LEFT BACK (2)           RIGHT BACK (3)
  * 
  * Note: Leg IDs correspond to the position in the movement direction arrays.
  ******************************************************************************/

// Leg identification constants
const int Left_Front = 0;      // Left front leg identifier
const int Right_Front = 1;     // Right front leg identifier
const int Left_Back = 2;       // Left back leg identifier
const int Right_Back = 3;      // Right back leg identifier

// Movement direction multipliers for angle calculations
// Indexed by leg ID: [Left_Front, Right_Front, Left_Back, Right_Back]
// Vertical direction: -1 = decrease angle (lift), +1 = increase angle (lower)
// Horizontal direction: +1 = forward swing, -1 = backward swing
const int vertical_move_direction[4] = {-1, 1, 1, -1};
const int horizontal_move_direction[4] = {1, -1, 1, -1};

// Initial state angles for all legs (degrees)
// These angles position the robot in a stable standing configuration
const int Left_Front_Init_Vertical_Angle = 150;    // Left front vertical initial angle
const int Left_Front_Init_Horizontal_Angle = 110;  // Left front horizontal initial angle
const int Right_Front_Init_Vertical_Angle = 30;    // Right front vertical initial angle
const int Right_Front_Init_Horizontal_Angle = 80;  // Right front horizontal initial angle
const int Left_Back_Init_Vertical_Angle = 30;      // Left back vertical initial angle
const int Left_Back_Init_Horizontal_Angle = 50;    // Left back horizontal initial angle
const int Right_Back_Init_Vertical_Angle = 160;    // Right back vertical initial angle
const int Right_Back_Init_Horizontal_Angle = 120;  // Right back horizontal initial angle

// Movement parameters (degrees)
const int Lift_Angle = 30;     // Vertical lift angle for stepping
const int Step_Angle = 30;     // Horizontal swing angle for movement

/*==================== FUNCTION DEFINITIONS ====================*/

/*******************************************************************************
  * Function Name: Init_State
  * Description  : Initialize the robot to its default standing position.
  *                Positions all legs at their pre-defined initial angles.
  * Parameters   : None
  * Returns      : None
  ******************************************************************************/
void Init_State(void)
{
    Left_Front_leg(Left_Front_Init_Vertical_Angle, Left_Front_Init_Horizontal_Angle);
    Right_Front_leg(Right_Front_Init_Vertical_Angle, Right_Front_Init_Horizontal_Angle);
    Left_Back_leg(Left_Back_Init_Vertical_Angle, Left_Back_Init_Horizontal_Angle);
    Right_Back_leg(Right_Back_Init_Vertical_Angle, Right_Back_Init_Horizontal_Angle);
}

/*******************************************************************************
  * LEG GROUPING STRATEGY
  * 
  * For stability during movement, the four legs are divided into two balanced
  * groups that alternate during locomotion:
  * 
  *   Group 1: Left Front (ID 0) and Right Back (ID 3)
  *   Group 2: Right Front (ID 1) and Left Back (ID 2)
  * 
  * This grouping ensures the robot maintains balance on the supporting group
  * while the other group executes movement.
  ******************************************************************************/

/*******************************************************************************
  * Function Name: Reset_Group1
  * Description  : Reset Group 1 legs to their initial positions.
  *                Used during movement sequences to return legs to neutral state.
  * Parameters   : None
  * Returns      : None
  ******************************************************************************/
void Reset_Group1(void)
{
    Left_Front_leg(Left_Front_Init_Vertical_Angle, Left_Front_Init_Horizontal_Angle);
    Right_Back_leg(Right_Back_Init_Vertical_Angle, Right_Back_Init_Horizontal_Angle);
}

/*******************************************************************************
  * Function Name: Reset_Group2
  * Description  : Reset Group 2 legs to their initial positions.
  *                Used during movement sequences to return legs to neutral state.
  * Parameters   : None
  * Returns      : None
  ******************************************************************************/
void Reset_Group2(void)
{
    Right_Front_leg(Right_Front_Init_Vertical_Angle, Right_Front_Init_Horizontal_Angle);
    Left_Back_leg(Left_Back_Init_Vertical_Angle, Left_Back_Init_Horizontal_Angle);
}

/*******************************************************************************
  * Function Name: Try_Move_Forward
  * Description  : Execute forward locomotion sequence using alternating tripod gait.
  *                The algorithm lifts, swings, and lowers leg groups in sequence
  *                to achieve forward movement while maintaining balance.
  * Parameters   : None
  * Returns      : None
  ******************************************************************************/
void Try_Move_Forward(void)
{
    // Step 1: Lift Group 1 and swing forward
    Left_Front_leg(Left_Front_Init_Vertical_Angle + vertical_move_direction[Left_Front] * Lift_Angle,
                   Left_Front_Init_Horizontal_Angle + horizontal_move_direction[Left_Front] * Step_Angle);
    delay_ms(400);
    Right_Back_leg(Right_Back_Init_Vertical_Angle + vertical_move_direction[Right_Back] * Lift_Angle,
                   Right_Back_Init_Horizontal_Angle + horizontal_move_direction[Right_Back] * Step_Angle);
    delay_ms(400);
    
    // Step 2: Reset Group 2 to prepare for weight transfer
    Reset_Group2();
    delay_ms(400);
    
    // Step 3: Lower Group 1 while maintaining forward swing
    Left_Front_leg(Left_Front_Init_Vertical_Angle,
                   Left_Front_Init_Horizontal_Angle + horizontal_move_direction[Left_Front] * Step_Angle);
    delay_ms(400);
    Right_Back_leg(Right_Back_Init_Vertical_Angle,
                   Right_Back_Init_Horizontal_Angle + horizontal_move_direction[Right_Back] * Step_Angle);
    delay_ms(400);
    
    // Step 4: Lift Group 2 and swing forward
    Right_Front_leg(Right_Front_Init_Vertical_Angle + vertical_move_direction[Right_Front] * Lift_Angle,
                    Right_Front_Init_Horizontal_Angle + horizontal_move_direction[Right_Front] * Step_Angle);
    delay_ms(400);
    Left_Back_leg(Left_Back_Init_Vertical_Angle + vertical_move_direction[Left_Back] * Lift_Angle,
                  Left_Back_Init_Horizontal_Angle + horizontal_move_direction[Left_Back] * Step_Angle);
    delay_ms(400);
    
    // Step 5: Reset Group 1 to prepare for next cycle
    Reset_Group1();
    delay_ms(400);
    
    // Step 6: Lower Group 2 while maintaining forward swing
    Right_Front_leg(Right_Front_Init_Vertical_Angle,
                    Right_Front_Init_Horizontal_Angle + horizontal_move_direction[Right_Front] * Step_Angle);
    delay_ms(400);
    Left_Back_leg(Left_Back_Init_Vertical_Angle,
                  Left_Back_Init_Horizontal_Angle + horizontal_move_direction[Left_Back] * Step_Angle);
    delay_ms(400);
}

/*******************************************************************************
  * Function Name: Try_Move_Backward
  * Description  : Execute backward locomotion sequence using alternating tripod gait.
  *                Similar to forward movement but with reversed swing direction.
  * Parameters   : None
  * Returns      : None
  ******************************************************************************/
void Try_Move_Backward(void)
{
    // Step 1: Lift Group 1 and swing backward
    Left_Front_leg(Left_Front_Init_Vertical_Angle + vertical_move_direction[Left_Front] * Lift_Angle,
                   Left_Front_Init_Horizontal_Angle - horizontal_move_direction[Left_Front] * Step_Angle);
    Right_Back_leg(Right_Back_Init_Vertical_Angle + vertical_move_direction[Right_Back] * Lift_Angle,
                   Right_Back_Init_Horizontal_Angle - horizontal_move_direction[Right_Back] * Step_Angle);
    delay_ms(100);
    
    // Step 2: Reset Group 2 to prepare for weight transfer
    Reset_Group2();
    delay_ms(100);
    
    // Step 3: Lower Group 1 while maintaining backward swing
    Left_Front_leg(Left_Front_Init_Vertical_Angle,
                   Left_Front_Init_Horizontal_Angle - horizontal_move_direction[Left_Front] * Step_Angle);
    Right_Back_leg(Right_Back_Init_Vertical_Angle,
                   Right_Back_Init_Horizontal_Angle - horizontal_move_direction[Right_Back] * Step_Angle);
    delay_ms(100);
    
    // Step 4: Lift Group 2 and swing backward
    Right_Front_leg(Right_Front_Init_Vertical_Angle + vertical_move_direction[Right_Front] * Lift_Angle,
                    Right_Front_Init_Horizontal_Angle - horizontal_move_direction[Right_Front] * Step_Angle);
    Left_Back_leg(Left_Back_Init_Vertical_Angle + vertical_move_direction[Left_Back] * Lift_Angle,
                  Left_Back_Init_Horizontal_Angle - horizontal_move_direction[Left_Back] * Step_Angle);
    delay_ms(100);
    
    // Step 5: Reset Group 1 to prepare for next cycle
    Reset_Group1();
    delay_ms(100);
    
    // Step 6: Lower Group 2 while maintaining backward swing
    Right_Front_leg(Right_Front_Init_Vertical_Angle,
                    Right_Front_Init_Horizontal_Angle - horizontal_move_direction[Right_Front] * Step_Angle);
    Left_Back_leg(Left_Back_Init_Vertical_Angle,
                  Left_Back_Init_Horizontal_Angle - horizontal_move_direction[Left_Back] * Step_Angle);
    delay_ms(100);
}

/*******************************************************************************
  * Function Name: Try_Turn_Right
  * Description  : Execute right turning sequence using differential leg movement.
  *                Creates rotational motion by swinging legs in opposite directions.
  * Parameters   : None
  * Returns      : None
  ******************************************************************************/
void Try_Turn_Right(void)
{
    // Step 1: Lift Group 1 with differential swing
    // Left front swings forward while right back swings backward
    Left_Front_leg(Left_Front_Init_Vertical_Angle + vertical_move_direction[Left_Front] * Lift_Angle,
                   Left_Front_Init_Horizontal_Angle + horizontal_move_direction[Left_Front] * Step_Angle);
    Right_Back_leg(Right_Back_Init_Vertical_Angle + vertical_move_direction[Right_Back] * Lift_Angle,
                   Right_Back_Init_Horizontal_Angle - horizontal_move_direction[Right_Back] * Step_Angle);
    delay_ms(100);
    
    // Step 2: Reset Group 2 to prepare for weight transfer
    Reset_Group2();
    delay_ms(100);
    
    // Step 3: Lower Group 1 maintaining differential swing
    Left_Front_leg(Left_Front_Init_Vertical_Angle,
                   Left_Front_Init_Horizontal_Angle + horizontal_move_direction[Left_Front] * Step_Angle);
    Right_Back_leg(Right_Back_Init_Vertical_Angle,
                   Right_Back_Init_Horizontal_Angle - horizontal_move_direction[Right_Back] * Step_Angle);
    delay_ms(100);
    
    // Step 4: Lift Group 2 with differential swing
    // Right front swings backward while left back swings forward
    Right_Front_leg(Right_Front_Init_Vertical_Angle + vertical_move_direction[Right_Front] * Lift_Angle,
                    Right_Front_Init_Horizontal_Angle - horizontal_move_direction[Right_Front] * Step_Angle);
    Left_Back_leg(Left_Back_Init_Vertical_Angle + vertical_move_direction[Left_Back] * Lift_Angle,
                  Left_Back_Init_Horizontal_Angle + horizontal_move_direction[Left_Back] * Step_Angle);
    delay_ms(100);
    
    // Step 5: Reset Group 1 to prepare for next cycle
    Reset_Group1();
    delay_ms(100);
    
    // Step 6: Lower Group 2 maintaining differential swing
    Right_Front_leg(Right_Front_Init_Vertical_Angle,
                    Right_Front_Init_Horizontal_Angle - horizontal_move_direction[Right_Front] * Step_Angle);
    Left_Back_leg(Left_Back_Init_Vertical_Angle,
                  Left_Back_Init_Horizontal_Angle + horizontal_move_direction[Left_Back] * Step_Angle);
    delay_ms(100);
}

/*******************************************************************************
  * Function Name: Try_Turn_Left
  * Description  : Execute left turning sequence using differential leg movement.
  *                Creates rotational motion by swinging legs in opposite directions.
  * Parameters   : None
  * Returns      : None
  ******************************************************************************/
void Try_Turn_Left(void)
{
    // Step 1: Lift Group 2 with differential swing
    // Right front swings forward while left back swings backward
    Right_Front_leg(Right_Front_Init_Vertical_Angle + vertical_move_direction[Right_Front] * Lift_Angle,
                    Right_Front_Init_Horizontal_Angle + horizontal_move_direction[Right_Front] * Step_Angle);
    Left_Back_leg(Left_Back_Init_Vertical_Angle + vertical_move_direction[Left_Back] * Lift_Angle,
                  Left_Back_Init_Horizontal_Angle - horizontal_move_direction[Left_Back] * Step_Angle);
    delay_ms(100);
    
    // Step 2: Reset Group 1 to prepare for weight transfer
    Reset_Group1();
    delay_ms(100);
    
    // Step 3: Lower Group 2 maintaining differential swing
    Right_Front_leg(Right_Front_Init_Vertical_Angle,
                    Right_Front_Init_Horizontal_Angle + horizontal_move_direction[Right_Front] * Step_Angle);
    Left_Back_leg(Left_Back_Init_Vertical_Angle,
                  Left_Back_Init_Horizontal_Angle - horizontal_move_direction[Left_Back] * Step_Angle);
    delay_ms(100);
    
    // Step 4: Lift Group 1 with differential swing
    // Left front swings backward while right back swings forward
    Left_Front_leg(Left_Front_Init_Vertical_Angle + vertical_move_direction[Left_Front] * Lift_Angle,
                   Left_Front_Init_Horizontal_Angle - horizontal_move_direction[Left_Front] * Step_Angle);
    Right_Back_leg(Right_Back_Init_Vertical_Angle + vertical_move_direction[Right_Back] * Lift_Angle,
                   Right_Back_Init_Horizontal_Angle + horizontal_move_direction[Right_Back] * Step_Angle);
    delay_ms(100);
    
    // Step 5: Reset Group 2 to prepare for next cycle
    Reset_Group2();
    delay_ms(100);
    
    // Step 6: Lower Group 1 maintaining differential swing
    Left_Front_leg(Left_Front_Init_Vertical_Angle,
                   Left_Front_Init_Horizontal_Angle - horizontal_move_direction[Left_Front] * Step_Angle);
    Right_Back_leg(Right_Back_Init_Vertical_Angle,
                   Right_Back_Init_Horizontal_Angle + horizontal_move_direction[Right_Back] * Step_Angle);
    delay_ms(100);
}