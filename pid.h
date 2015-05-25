
#ifndef __PID__
#define __PID__
/*PID = Uk + KP*[E(k)-E(k-1)]+KI*E(k)+KD*[E(k)-2E(k-1)+E(k-2)];(������PID��ʽ)
�������: RK(�趨ֵ),CK(ʵ��ֵ),KP,KI,KD
��������: U(K)*/
#include "stm32f10x.h"

#define KP_1 50
#define KI_1 0
#define KD_1 5

//PIDValueStr  PID;
double PID_Control_1(double current_position_201,double target_position_201);

#endif
 
