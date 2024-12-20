#include "mex.h"
#include "algo.h"

// Using static the variable is stored from one call of the mex function to the other one
// 

enum {STOP, FORWARD, LEFT, RIGHT}; 
static int state = FORWARD;

int sen_diff;

void cc_algorithm(int *perc_steer, int *perc_throttle, unsigned int front_sensor, unsigned int left_sensor, unsigned int right_sensor, int ticks, unsigned int simFrequ) 
{        
    /* INPUTS:
     * ========
     * SENSORS:     The sensor values are simulated in [mm] --> max values: Front (1500mm), Left (900mm), Right (900mm)
     * TICKS:       Should give you an impression of the rpm sensor and the velocity respectively; one tick equals 5mm
     * SIMFREQU:    Update rate of the simulation (this could be varying if changes to simulation settings occur)
     * 
     * OUTPUTS:
     * ========
     * PERC_STEER and PERC_THROTTLE should range between -100 and 100 respectively (any outliers will be thresholded by the simulation)
     * 
    */
    // ===================================== PLACE YOUR ALGORITHM HERE ===============
    sen_diff = left_sensor - right_sensor;
    *perc_throttle = 40;
    
    switch(state)
    {
        case FORWARD:
               *perc_steer = sen_diff/10;                
               if(left_sensor > front_sensor)
               {
                  state = LEFT; 
               }
               else if(right_sensor > front_sensor)
               {
                  state = RIGHT;     
               }                      
            break;
        case LEFT:
               *perc_steer = 100;  
               if(front_sensor > left_sensor)
               {
                  state = FORWARD; 
               }
            break;
        case RIGHT:
               *perc_steer = -100;  
               if(front_sensor > right_sensor)
               {
                  state = FORWARD; 
               }
            break; 
        default:
            
            break;
    }           
    
    // ================================================================================
    //*perc_steer = 0;
    //*perc_throttle = 0;
}
            