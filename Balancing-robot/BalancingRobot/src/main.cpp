#include <Arduino.h>
#include "mpu6050.h"

# define Enable       8            //D8                 //PORTB 0                    
# define Step_3       7            //D7                 //PORTD 7                    
# define Step_2       6            //D6                 //PORTD 6                                      
# define Dir_3        4            //D4                 //PORTD 4                    
# define Dir_2        3            //D3                 //PORTD 3                    

MPU6050         mpu6050;
int8_t           Dir_M1, Dir_M2, Dir_M3;                                              
volatile int     Count_timer1, Count_timer2, Count_timer3;                    
volatile int32_t Step1, Step2, Step3;
int16_t          Count_TOP1, Count_BOT1, Count_TOP2, Count_BOT2, Count_TOP3, Count_BOT3; 
float            Input_L, Input_R, Output, I_L, I_R, Input_lastL, Input_lastR, Output_L, Output_R, M_L, M_R, Motor_L, Motor_R;

float            Kp = 10;
float            Ki = 1;
float            Kd = 0.01;

float            Offset = 0.8;
float            Vgo = 0;
float            Vgo_L = 0;
float            Vgo_R = 0;
float            AngleY;
int              Limited = 400;

static char             Bluetooth = '@';
unsigned long    loop_timer;
bool             Start = false;

void GPIO_Config();
void Tim2InitStructure();
void Speed_L(int16_t x);
void Speed_R(int16_t x);
void Connected_Bluetooth(void);
void Control(void);
void RobotGo(int a);

void setup() {
//   mpu6050.init(0x68);
//   Serial.begin(9600);            
//   GPIO_Config();                       
//   Tim2InitStructure();                   
//   Connected_Bluetooth();
//   delay(500);
//   loop_timer = micros() + 4000;
// }

// void loop() {
//   AngleY = mpu6050.getYAngle();

//   //Dùng PID cho MOTOR_L
//   Input_L = AngleY + Offset - Vgo - Vgo_L;                             //Vgo<0  chạy lui,Vgo >0 chạy tới
//   I_L += Input_L * Ki;
//   I_L = constrain(I_L, -400, 400);

//   Output_L = Kp * Input_L + I_L + Kd * (Input_L - Input_lastL);
//   Input_lastL = Input_L;                                           //Lưu làm độ lệch trước cho vòng loop sau

//   //Khống chế OUTPUT theo sự phi tuyến MOTOR_L
//   if (Output_L > -5 && Output_L < 5)Output_L = 0;
//   Output_L = constrain(Output_L, -400, 400);


//   //Dùng PID cho MOTOR_R
//   Input_R = AngleY + Offset - Vgo - Vgo_R; //Vgo<0  chạy lui,Vgo >0 chạy tới
//   I_R += Input_R * Ki;
//   I_R = constrain(I_R, -400, 400);



//   Output_R = Kp * Input_R + I_R + Kd * (Input_R - Input_lastR);
//   Input_lastR = Input_R;

//   //Khống chế OUTPUT theo sự phi tuyến MOTOR_R
//   // if (Output_R > -5 && Output_R < 5)Output_R = 0;
//   Output_R = constrain(Output_R, -400, 400);

//   //Khắc phục sự phi tuyến của MOTOR_L
//   if (Output_L > 0)M_L = 405 - (1 / (Output_L + 9)) * 5500;
//   else if (Output_L < 0)  M_L = -405 - (1 / (Output_L - 9)) * 5500;
//   else M_L = 0;

//   //Khắc phục sự phi tuyến của MOTOR_R
//   if (Output_R > 0)M_R = 405 - (1 / (Output_R + 9)) * 5500; //Output_R = 1    ----> M_R = -145
//   //                                                        Output_R = 4.58 ----> M_R = 0
//   //                                                        Output_R = 10   ----> M_R = 115.52
//   //                                                        Output_R = 400  ----> M_R = 391.55
//   else if (Output_R < 0)M_R = -405 - (1 / (Output_R - 9)) * 5500;
//   else M_R = 0;

//   //Làm ngược giá trị truyền vào hàm Speed_L()
//   if (M_L > 0)Motor_L = 400 - M_L;
//   else if (M_L < 0)Motor_L = -400 - M_L;
//   else Motor_L = 0;

//   //Làm ngược giá trị truyền vào hàm Speed_R()
//   if (M_R > 0)Motor_R = 400 - M_R;
//   else if (M_R < 0)Motor_R = -400 - M_R;
//   else Motor_R = 0;

//   //cho 2 MOTOR chạy
  Speed_L(-50);
  Speed_R(-50);

//   while (loop_timer > micros());
//   loop_timer += 4000;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void  GPIO_Config() {
  pinMode(Enable, OUTPUT);
  pinMode(Step_2, OUTPUT);
  pinMode(Step_3, OUTPUT);
  pinMode(Dir_2, OUTPUT);
  pinMode(Dir_3, OUTPUT);
  digitalWrite(Enable, LOW);

}


void Tim2InitStructure() {
  TCCR2A  = 0;                                                               //Make sure that the TCCR2A register is set to zero
  TCCR2B  = 0;                                                               //Make sure that the TCCR2A register is set to zero
  TCCR2B  |= (1 << CS21);                                                    //Set the CS21 bit in the TCCRB register to set the prescaler to 8
  OCR2A   = 29;                                                               //The compare register is set to 39 => 20us / (1s / (16.000.000Hz / 8)) - 1
  TCCR2A  |= (1 << WGM21);                                                   //Set counter 2 to CTC (clear timer on compare) mode Chế độ CTC bộ đếm được xóa về 0 khi giá trị bộ đếm (TCNT0) khớp với OCR0A
  TIMSK2  |= (1 << OCIE2A);                                                  //Set the interupt enable bit OCIE2A in the TIMSK2 register
}

//....................................
ISR(TIMER2_COMPA_vect) {

  //tạo xung STEP cho MOTOR2
  if (Dir_M2 != 0) {
    Count_timer2++;
    if (Count_timer2 <= Count_TOP2)PORTD |= 0b00001000;
    else PORTD &= 0b11110111;
    if (Count_timer2 > Count_BOT2) {
      Count_timer2 = 0;
      if (Dir_M2 > 0)Step2++;
      else if (Dir_M2 < 0)Step2--;
    }
  }

  //tạo xung STEP cho MOTOR3
  if (Dir_M3 != 0) {
    Count_timer3++;
    if (Count_timer3 <= Count_TOP3)PORTD |= 0b00010000;
    else PORTD &= 0b11101111;
    if (Count_timer3 > Count_BOT3) {
      Count_timer3 = 0;
      if (Dir_M3 > 0)Step3++;
      else if (Dir_M3 < 0)Step3--;
    }
  }
}


void Speed_L(int16_t x) {
  if (x < 0) {
    Dir_M2 = -1;
    PORTD &= 0b10111111;
  }
  else if (x > 0) {
    Dir_M2 = 1;
    PORTD |= 0b01000000;
  }
  else Dir_M2 = 0;

  Count_BOT2 = abs(x);
  Count_TOP2 = Count_BOT2 / 2;
}

void Speed_R(int16_t x) {
  if (x < 0) {
    Dir_M3 = -1;
    PORTD &= 0b01111111;
  }
  else if (x > 0) {
    Dir_M3 = 1;
    PORTD |= 0b10000000;
  }
  else Dir_M3 = 0;

  Count_BOT3 = abs(x);
  Count_TOP3 = Count_BOT3 / 2;
}

void Connected_Bluetooth(void)
{
  Start = false;
  Serial.println("\nNhap 's' de bat dau");
  while (!Start)
  {
    if (Serial.available() > 0 && Serial.read() == 's')
      Start = true;
  }
  Serial.println("\nRobot bat dau khoi dong");
}

void Control(void)
{
  if (Serial.available() > 0) {
    Bluetooth = Serial.read();
  }

  if (Bluetooth == 'g')
  {
    if (Vgo < 7)Vgo += 0.05;
    if (AngleY > 10)Vgo -= 0.005;
    Vgo_L = Vgo_R = 0;    
    Serial.println("\nRobot tien");
  } else if (Bluetooth == 'b')
  {
    if (Vgo > - 2.5)Vgo -= 0.05;
    if (AngleY > -10)Vgo += 0.005;
    Vgo_L = Vgo_R = 0;
    Serial.println("\nRobot lui");
  } else if (Bluetooth == 'l')
  {
    if (Vgo_L > -0.3)Vgo_L -= 0.01;
    if (Vgo_R < 0.3)Vgo_R += 0.01;
    Serial.println("\nRobot quay trai");
  } else if (Bluetooth == 'r')
  {
    if (Vgo_L < 0.3)Vgo_L += 0.01;
    if (Vgo_R >- 0.3)Vgo_R -= 0.01;
    Serial.println("\nRobot quay phai");
  } else if (Bluetooth == 'a')
  {
    Vgo = 0;
    Vgo_L = 0;
    Vgo_R = 0;
    Serial.println("\nRobot dung");
  }else if(Bluetooth == 'E')
  {
    Speed_L(0);
    Speed_R(0);
    Serial.println("\nRobot dung khan cap");
    Connected_Bluetooth();
  }
}
void RobotGo(int a)
{
  Vgo = 6;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////