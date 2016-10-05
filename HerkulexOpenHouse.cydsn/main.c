/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "herkulex2.h"

int main()
{
    CyGlobalIntEnable;
    
    Servo_initialize();
    
    Servo_moveSpeedOne(1,500,500,LED_BLUE);
    
    CyDelay(1000);
    
    Servo_moveSpeedOne(1,-500,500,LED_RED);
    

    for(;;)
    {
        
    }
}

/* [] END OF FILE */
