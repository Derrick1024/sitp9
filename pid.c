//pid.c
/*PID = PID->UK_REAL + PID->KP*[E(k)-E(k-1)]+PID->KI*E(k)+PID->KD*[E(k)-2E(k-1)+E(k-2)];(增量型PID算式)
函数入口: PID->RK(设定值),PID->CK(实际值),PID->KP,PID->KI,PID->KD
函数出口: U(K)*/

#include "pid.h"
#define MAXOUT 999

 
double PID_Control_1(double current_position_201,double target_position_201)
{
    static double error_l[2] = {0.0,0.0};
    static double output = 0;
    static double inte = 0;
    
    error_l[0] = error_l[1];
    error_l[1] = target_position_201 - current_position_201;
    inte += error_l[1]; 
    
    output = error_l[1] * KP_1 
            + inte * KI_1 
            + (error_l[1] - error_l[0]) * KD_1;
    
    if(output > MAXOUT)
    {
        output = MAXOUT;
    }
    
    if(output < -MAXOUT)
    {
        output = -MAXOUT;
    }
    		
    return output;
}







