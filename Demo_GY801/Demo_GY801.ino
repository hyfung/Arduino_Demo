#include <Wire.h>
#include <math.h>
#include <L3G4200D.h>
L3G4200D gyro;

#define Register_ID 0
#define Register_2D 0x2D
#define Register_X0 0x32
#define Register_X1 0x33
#define Register_Y0 0x34
#define Register_Y1 0x35
#define Register_Z0 0x36
#define Register_Z1 0x37

#define PI 3.14159265358979f

#define maxdiff  1000
#define maxaccu  1000
#define offset 0        //more +ve, more directed to Arduino side
#define resolution  1000
#define minangle  0.2
#define maxangle  15

char firstSample;   //marks first sample

int ADXAddress = 0xA7 >> 1;  // the default 7-bit slave address
int reading = 0;
int val = 0;
int X0, X1, X_out;
int Y0, Y1, Y_out;
int Z1, Z0, Z_out;
double Axz, Ayz;
double Angx, Angy;
double delta, diff, last, diff2, last2, accu;
double kang;

unsigned long lastMilli;
unsigned long interval; //interval since previous analog samples

float RwAcc[3];         //projection of normalized gravitation force vector on x/y/z axis, as measured by accelerometer
float GyroIN[3];        //gyro value from sensor

void setup()
{
  Wire.begin();
  Serial.begin(9600);

  delay(100);
  // enable to measure g data
  Wire.beginTransmission(ADXAddress);
  Wire.write(Register_2D);
  Wire.write(8);                //measuring enable
  Wire.endTransmission();     // stop transmitting

  // enable gyro
  Wire.begin();
  gyro.enableDefault();

  accu = 0;
  last = 0;
  last2 = 0;
  firstSample = 1;
}

void loop() {
  static unsigned long newMilli; //new timestamp
  newMilli = millis();        //save the time when sample is taken
  Read_acc();
  Read_gyro();
  //compute interval since last sampling time in millisecond
  interval = newMilli - lastMilli;
  lastMilli = newMilli;               //save for next loop, please note interval will be invalid in first sample but we don't use it

  Ayz = atan2(RwAcc[1], RwAcc[2]) * 180 / PI; //angle measured by accelerometer
  Ayz -= offset;                        //adjust to correct balance point

}


void Read_acc() {
  //--------------X
  int i;

  X_out = 0;
  for (i = 0; i < 10; i++) {
    Wire.beginTransmission(ADXAddress); // transmit to device
    Wire.write(Register_X0);
    Wire.write(Register_X1);
    Wire.endTransmission();
    Wire.requestFrom(ADXAddress, 2);
    if (Wire.available() <= 2)
    {
      X0 = Wire.read();
      X1 = Wire.read();
      X1 = X1 << 8;
      X_out += (X0 + X1);
    }
  }
  X_out /= 10;

  //------------------Y
  Wire.beginTransmission(ADXAddress); // transmit to device
  Wire.write(Register_Y0);
  Wire.write(Register_Y1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress, 2);
  if (Wire.available() <= 2)
  {
    Y0 = Wire.read();
    Y1 = Wire.read();
    Y1 = Y1 << 8;
    Y_out = Y0 + Y1;
  }
  //------------------Z
  Wire.beginTransmission(ADXAddress); // transmit to device
  Wire.write(Register_Z0);
  Wire.write(Register_Z1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress, 2);
  if (Wire.available() <= 2)
  {
    Z0 = Wire.read();
    Z1 = Wire.read();
    Z1 = Z1 << 8;
    Z_out = Z0 + Z1;
  }
  RwAcc[0] = X_out / 256.0;
  RwAcc[1] = Y_out / 256.0;
  RwAcc[2] = Z_out / 256.0;
}

void Read_gyro() {
  gyro.read();
  GyroIN[0] = gyro.g.x / 256.0;
  GyroIN[1] = gyro.g.y / 256.0;
  GyroIN[2] = gyro.g.z / 256.0;
}

// Kalman filter module

float Q_angle  =  0.001;
float Q_gyro   =  0.003;
float R_angle  =  0.03;

float x_angle = 0;
float x_bias = 0;
float P_00 = 0, P_01 = 0, P_10 = 0, P_11 = 0;
float dt, y, S;
float K_0, K_1;


float kalmanCalculate(float newAngle, float newRate, int looptime) {
  dt = float(looptime) / 1000;
  x_angle += dt * (newRate - x_bias);
  P_00 +=  - dt * (P_10 + P_01) + Q_angle * dt;
  P_01 +=  - dt * P_11;
  P_10 +=  - dt * P_11;
  P_11 +=  + Q_gyro * dt;

  y = newAngle - x_angle;
  S = P_00 + R_angle;
  K_0 = P_00 / S;
  K_1 = P_10 / S;

  x_angle +=  K_0 * y;
  x_bias  +=  K_1 * y;
  P_00 -= K_0 * P_00;
  P_01 -= K_0 * P_01;
  P_10 -= K_1 * P_00;
  P_11 -= K_1 * P_01;

  return x_angle;
}

