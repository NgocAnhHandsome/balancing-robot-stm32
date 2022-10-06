#include "system.h"
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

double AngleY;

float  Input_L, Input_R, Output, I_L, I_R, Input_lastL, Input_lastR, Output_L, Output_R, M_L, M_R, Motor_L, Motor_R;

float  		Kp = 10;
float  		Ki = 1;
float  		Kd = 0.01;

float  		Offset = 0.8;
float  		Vgo = 0;
float  		Vgo_L = 0;
float  		Vgo_R = 0;
int    		Limited = 400;
uint32_t  loop_timer;

void System_Init(void)
{
//	MotorInit();
//	TimeSystickInit();
	UsartLib_Init(9600);
	MPU_init(0x68 << 1);
//	delay(1000);
//	loop_timer = SystickMillis() + 4000;
}
void System_Run(void)
{
//	AngleY = getYAngle();
//	printf("%lf\n", AngleY);
//	delay(10);
// //Dùng PID cho MOTOR_L
//  Input_L = AngleY + Offset - Vgo - Vgo_L;                             
//  I_L += Input_L * Ki;
//  I_L = constrain(I_L, -400, 400);

//  Output_L = Kp * Input_L + I_L + Kd * (Input_L - Input_lastL);
//  Input_lastL = Input_L;                                           

//  if (Output_L > -5 && Output_L < 5)Output_L = 0;
//  Output_L = constrain(Output_L, -400, 400);


//  Input_R = AngleY + Offset - Vgo - Vgo_R; 
//  I_R += Input_R * Ki;
//  I_R = constrain(I_R, -400, 400);



//  Output_R = Kp * Input_R + I_R + Kd * (Input_R - Input_lastR);
//  Input_lastR = Input_R;

//  if (Output_R > -5 && Output_R < 5)Output_R = 0;
//  Output_R = constrain(Output_R, -400, 400);

//  if (Output_L > 0)M_L = 405 - (1 / (Output_L + 9)) * 5500;
//  else if (Output_L < 0)  M_L = -405 - (1 / (Output_L - 9)) * 5500;
//  else M_L = 0;

//  if (Output_R > 0)M_R = 405 - (1 / (Output_R + 9)) * 5500;                                                     
//  else if (Output_R < 0)M_R = -405 - (1 / (Output_R - 9)) * 5500;
//  else M_R = 0;

//  if (M_L > 0)Motor_L = 400 - M_L;
//  else if (M_L < 0)Motor_L = -400 - M_L;
//  else Motor_L = 0;

//  if (M_R > 0)Motor_R = 400 - M_R;
//  else if (M_R < 0)Motor_R = -400 - M_R;
//  else Motor_R = 0;

  Speed_L(50);
  Speed_R(50);

//  while (loop_timer > SystickMillis());
//  loop_timer += 4000;	
}